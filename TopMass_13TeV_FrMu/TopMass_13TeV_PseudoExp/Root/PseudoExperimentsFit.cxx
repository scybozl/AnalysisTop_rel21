#include "TString.h"
#include "TMinuitMinimizer.h"
#include "TMatrixD.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <omp.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "Math/Functor.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLatex.h"
#include "TGaxis.h"

#include "TopMass_13TeV_PseudoExp/AtlasStyle.h"
#include "TopMass_13TeV_PseudoExp/PseudoExperimentsFit.h"

#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions

using namespace std;

/*
Double_t Gauss(Double_t *x, Double_t *par_values) {
  //  return par_values[0]*exp(-0.5*pow((x[0]-par_values[1])/par_values[2],2));
  return (par_values[0]/sqrt(2*PI*pow(par_values[2],2)))*TMath::Gaus( x[0], par_values[1], par_values[2] );
}
//Landau                                                                                                                                                                               
Double_t Landau(Double_t *x,  Double_t *par_values) { // 3 par_values                                                                                                                 \
                                                                                                                                                                                       
  return par_values[0]*(TMath::Landau(x[0], par_values[1], par_values[2])/par_values[2]);
}
//Landau_n                                                                                                                                                                            \
                                                                                                                                                                                       
Double_t Landau_n(Double_t *x,  Double_t *par_values) { // 3 par_values                                                      
                                                                                                                                                                                       
  return par_values[0]*(TMath::Landau(2*par_values[1]-x[0], par_values[1], par_values[2])/par_values[2]);
}

Double_t Mtop_function(Double_t *x,  Double_t *par) {

  int npar = npars_sep_mtop;

  // gauss + inv.landau + landau  
                                                                                                                                                     
  Double_t mtop = par[npar*4+0]-172.5;
  Double_t JSF  = par[npar*4+1]-1.0;
  Double_t bJSF = par[npar*4+2]-1.0;

  Double_t par_values[npar];

  for (int k = 0; k < npar; k++)
    par_values[k] = par[k+0]+par[k+npar]*mtop+par[k+2*npar]*JSF+par[k+3*npar]*bJSF;

  Double_t value = par[npar*4+3]*(Gauss(x, par_values) + Landau_n(x, &par_values[3]) + Landau(x, &par_values[6]));

  return value;

}
*/

//top mass fit function
Double_t Mtop_function(Double_t *x,  Double_t *par) {

  int npar = npars_sep_mtop;
  int npar_comb = npars_comb_mtop;

  Double_t mtop = par[npar_comb+0];
  Double_t JSF  = par[npar_comb+1];
  Double_t bJSF = par[npar_comb+2];

  Double_t *par_values = new Double_t[npar];
  ConvertPars(par, par_values, npar, "mtop", mtop, JSF, bJSF);

  Double_t value = par[npar_comb+3]*mtop_function(x, par_values);

  delete [] par_values;
  return value;

}

//W mass fit function
Double_t Mw_function(Double_t *x,  Double_t *par) {

  int npar = npars_sep_mw;
  int npar_comb = npars_comb_mw;

  Double_t JSF  = par[npar_comb+0];

  double *par_values = new double[npar];
  ConvertPars(par, par_values, npar, "mw", 172.5, JSF, 1.);

  Double_t value = par[npar_comb+1]*mw_function(x, par_values);

  delete par_values;
  return value;

}

//Rbq fit function
Double_t Rbq_function(Double_t *x,  Double_t *par) {

  int npar = npars_sep_rbq;
  int npar_comb = npars_comb_rbq;

  Double_t mtop = par[npar_comb+0];
  Double_t JSF  = par[npar_comb+1];
  Double_t bJSF = par[npar_comb+2];
   
  double *par_values = new double[npar];
  ConvertPars(par, par_values, npar, "rbq", mtop, JSF, bJSF);

  Double_t value = par[npar_comb+3]*rbq_function(x, par_values);
  
  delete [] par_values;
  return value;

}

//mlb fit function
Double_t Mtop_function_dil(Double_t *x,  Double_t *par) {

  int npar = npars_sep_mlb;
  int npar_comb = npars_comb_mlb;

  Double_t mtop = par[npar_comb+0];

  double *par_values = new double[npar];
  ConvertPars(par, par_values, npar, "mlb", mtop, 1., 1.);

  Double_t value = par[npar_comb+1]*mlb_function(x, par_values);

  delete [] par_values;
  return value;

}



PseudoExperimentsFit::PseudoExperimentsFit(string ParameterFile, bool OnePE, int FitDimension, bool IsLeptonJets)
{

  std::cout << "Here constructor!" << std::endl;

  if(IsLeptonJets){
    fmtop = new TF1("ftop", Mtop_function, fitmin_mtop, fitmax_mtop, npars_comb_mtop+4);
    fmw   = new TF1("fmw",  Mw_function,   fitmin_mw,   fitmax_mw,   npars_comb_mw+2);
    frbq  = new TF1("frbq", Rbq_function,  fitmin_rbq,  fitmax_rbq,  npars_comb_rbq+4);
  }
  else{
    fmtop_dil = new TF1("ftop_dil", Mtop_function_dil, fitmin_mlb, fitmax_mlb, npars_comb_mlb+2);
  }

  fParameterFile = ParameterFile;
  fRunOnePE      = OnePE;
  fFitDimension  = FitDimension;
  fIsLeptonJets  = IsLeptonJets;

}


PseudoExperimentsFit::~PseudoExperimentsFit()
{
  
  if(fIsLeptonJets){
    delete fmtop;
    delete fmw;
    delete frbq;
  }
  else
    delete fmtop_dil;

}


void PseudoExperimentsFit::ReadParameters(std::string foldername){

  if(fIsLeptonJets){

    TFile *f1 = new TFile((foldername+"/mtop_pars.root").c_str(), "READ");
    TTree *t1 = (TTree*) f1 -> Get("pars");
    
    vector<double>  *Parameter1;
    t1->SetBranchAddress("Parameters", &Parameter1); 
    
    Parameter1 = 0;
    
    t1 -> GetEntry(0);
    
    for(unsigned int i = 0; i < Parameter1 -> size(); ++i){
      fmtop -> SetParameter(i,   Parameter1 -> at(i));
    }
    
    TFile *f2 = new TFile((foldername+"/mw_pars.root").c_str(), "READ");
    TTree *t2 = (TTree*) f2 -> Get("pars");
    
    vector<double>  *Parameter2;
    t2->SetBranchAddress("Parameters", &Parameter2);
    
    Parameter2 = 0;
   
    t2 -> GetEntry(0);
    
    for(unsigned int j = 0; j < Parameter2 -> size(); ++j)
      fmw  -> SetParameter(j, Parameter2 -> at(j));
    
    TFile *f3 = new TFile((foldername+"/rbq_pars.root").c_str(), "READ");
    TTree *t3 = (TTree*) f3 -> Get("pars");
    
    vector<double>  *Parameter3;
    t3->SetBranchAddress("Parameters", &Parameter3);
    
    Parameter3 = 0;
    
    t3 -> GetEntry(0);
    
    for(unsigned int k = 0; k < Parameter3 -> size(); ++k){
      frbq -> SetParameter(k, Parameter3 -> at(k));
    }
 
    fmtop -> SetParameter(npars_comb_mtop+0, 172.5);
    fmtop -> SetParameter(npars_comb_mtop+1,   1.0);
    fmtop -> SetParameter(npars_comb_mtop+2,   1.0);
    fmtop -> SetParameter(npars_comb_mtop+3,   1.0);
    
    std::cout << "directly after initialisation = " << fmtop -> Integral(fitmin_mtop, fitmax_mtop) << std::endl;

    fmw   -> SetParameter(npars_comb_mw+0,   1.0);
    fmw   -> SetParameter(npars_comb_mw+1,   1.0);
    
    std::cout << "directly after initialisation = " << fmw   -> Integral(fitmin_mw,   fitmax_mw) << std::endl;
    
    frbq  -> SetParameter(npars_comb_rbq+0, 172.5);
    frbq  -> SetParameter(npars_comb_rbq+1,   1.0); 
    frbq  -> SetParameter(npars_comb_rbq+2,   1.0);
    frbq  -> SetParameter(npars_comb_rbq+3,   1.0);
    
    std::cout << "directly after initialisation = " << frbq  -> Integral(fitmin_rbq, fitmax_rbq) << std::endl;
    
    Double_t Integral_mtop = fmtop -> Integral(fitmin_mtop, fitmax_mtop);
    Double_t Integral_jsf  = fmw   -> Integral(fitmin_mw,   fitmax_mw);
    Double_t Integral_bjsf = frbq  -> Integral(fitmin_rbq,  fitmax_rbq);
    
    fmtop -> SetParameter(npars_comb_mtop+3,  1.0/Integral_mtop);
    fmw   -> SetParameter(npars_comb_mw+1,    1.0/Integral_jsf);
    frbq  -> SetParameter(npars_comb_rbq+3,   1.0/Integral_bjsf);
    
    std::cout << "rbq after normalisation = " << frbq  -> Integral(fitmin_rbq, fitmax_rbq) << std::endl;

    f1 -> Close();
    f2 -> Close();
    f3 -> Close();

  }
  else{

    TFile *f1 = new TFile((foldername+"/mlb_pars.root").c_str(), "READ");
    TTree *t1 = (TTree*) f1 -> Get("pars");
    
    vector<double>  *Parameter1;
    t1->SetBranchAddress("Parameters", &Parameter1);
    
    Parameter1 = 0;
    
    t1 -> GetEntry(0);
    
    for(unsigned int i = 0; i < Parameter1 -> size(); ++i){
      fmtop_dil -> SetParameter(i,   Parameter1 -> at(i));

      std::cout << i << "\t" << Parameter1 -> at(i) << std::endl;

    }
    
    fmtop_dil  -> SetParameter(npars_comb_mlb+0, 172.5);
    fmtop_dil  -> SetParameter(npars_comb_mlb+1,   1.0);

    Double_t Integral_mtop = fmtop_dil -> Integral(fitmin_mlb, fitmax_mlb);

    std::cout << "Integral dilepton = " << Integral_mtop << std::endl;
    
    fmtop_dil -> SetParameter(npars_comb_mlb+1,   1.0/Integral_mtop);
    
    Integral_mtop = fmtop_dil -> Integral(fitmin_mlb, fitmax_mlb);

    std::cout << "Integral dilepton nachher = " << Integral_mtop << std::endl;

    f1 -> Close();

  }

}


double PseudoExperimentsFit::FitFCN(const Double_t *par) const
{

  double like = 0;

  if(fIsLeptonJets){
  
    fmtop     -> SetNpx(100000);
    fmw       -> SetNpx(100000);
    frbq      -> SetNpx(100000);
        
    fmtop -> SetParameter(npars_comb_mtop+0, par[0]); // mtop
    fmtop -> SetParameter(npars_comb_mtop+1, par[1]); // jsf
    fmtop -> SetParameter(npars_comb_mtop+2, par[2]); // bjsf
    fmtop -> SetParameter(npars_comb_mtop+3,    1.0); // normalisation
    
    fmw   -> SetParameter(npars_comb_mw+0,   par[1]); // jsf 
    fmw   -> SetParameter(npars_comb_mw+1,      1.0); // normalisation   
    
    frbq  -> SetParameter(npars_comb_rbq+0,  par[0]);
    frbq  -> SetParameter(npars_comb_rbq+1,  par[1]); // jsf
    frbq  -> SetParameter(npars_comb_rbq+2,  par[2]); // bjsf
    frbq  -> SetParameter(npars_comb_rbq+3,     1.0); // normalisation   
    
    double Integral_mtop = fmtop -> Integral(fitmin_mtop, fitmax_mtop);
    double Integral_jsf  = fmw   -> Integral(fitmin_mw,   fitmax_mw);
    double Integral_bjsf = frbq  -> Integral(fitmin_rbq,  fitmax_rbq);
    
    fmtop -> SetParameter(npars_comb_mtop+3, 1.0/Integral_mtop);
    fmw   -> SetParameter(npars_comb_mw+1,   1.0/Integral_jsf);
    frbq  -> SetParameter(npars_comb_rbq+3,  1.0/Integral_bjsf);

  }
  else{

    fmtop_dil -> SetNpx(10000);
    fmtop_dil -> SetParameter(npars_comb_mlb+0, par[0]); // mtop                
    fmtop_dil -> SetParameter(npars_comb_mlb+1,    1.0); // normalisation 

    double Integral_mtop = fmtop_dil -> Integral(fitmin_mlb, fitmax_mlb);

    fmtop_dil -> SetParameter(npars_comb_mlb+1,   1.0/Integral_mtop/2);

  }
    
  double counter0 = 0;
  double counter1 = 0;

  std::cout << "HERE!!!! 1 ===================================================> " << fTTbarInfoTmp.size() << std::endl;

  for (unsigned int idx = 0; idx < fTTbarInfoTmp.size(); idx++) {
    
    double f  = 1.0;

    if(fIsLeptonJets){

      f  =  fmtop -> Eval(fTTbarInfoTmp[idx][3]);
      double fw =  fmw   -> Eval(fTTbarInfoTmp[idx][4]);
      double fr =  frbq  -> Eval(fTTbarInfoTmp[idx][5]);

      if(fFitDimension > 1)
	f = f * fw;    
      if(fFitDimension > 2)
	f = f * fr;

    }
    else{

      f  =  fmtop_dil -> Eval(fTTbarInfoTmp[idx][3]);

      //      std::cout << f << fTTbarInfoTmp[idx][3] << std::endl;

    }
    
    //    std::cout << par[0] << "\t" << fTTbarInfoTmp[idx][3] << "\t" <<  fTTbarInfoTmp[idx][0] << "\t" << f << "\t" << log(f) << std::endl;

    if(fRunOnePE)
      like += fTTbarInfoTmp[idx][0]*log(f); // weighted event   
    else
      like += fTTbarInfoTmp[idx][1]*log(f);

    counter0 += fTTbarInfoTmp[idx][0];
    counter1 += fTTbarInfoTmp[idx][1];


  }
  
  like *= -2.0;
  
  std::cout << par[0] << "\t" << like << "\t" << counter0 << "\t" << counter1 << "\t" << fRunOnePE <<  std::endl;

  return like;

}


void PseudoExperimentsFit::PrepareOverlayPlot(double mtop, double jsf, double bjsf, std::string OutputFile, std::string FileString)
{

  std::cout << "Make Overlay Plot!!!" << std::endl;
  
  fmtop -> SetParameter(npars_comb_mtop+0,   mtop); // mtop
  fmtop -> SetParameter(npars_comb_mtop+1,    jsf); // jsf
  fmtop -> SetParameter(npars_comb_mtop+2,   bjsf); // bjsf

  fmw   -> SetParameter(npars_comb_mw+0,     jsf); // jsf

  frbq  -> SetParameter(npars_comb_rbq+0,   mtop); // mtop
  frbq  -> SetParameter(npars_comb_rbq+1,    jsf); // jsf
  frbq  -> SetParameter(npars_comb_rbq+2,   bjsf); // bjsf
                                                              
  TH1D *histo_mtop   = new TH1D("histo_mtop",   "histo_mtop",   fitmax_mtop-fitmin_mtop,      fitmin_mtop, fitmax_mtop);
  TH1D *histo_mw     = new TH1D("histo_mw",     "histo_mw",     fitmax_mw-fitmin_mw,          fitmin_mw,   fitmax_mw);
  TH1D *histo_rbq    = new TH1D("histo_rbq",    "histo_rbq",    (fitmax_rbq-fitmin_rbq)/0.05, fitmin_rbq,  fitmax_rbq);

  TH1D *histo_mtop_e = new TH1D("histo_mtop_e", "histo_mtop_e", fitmax_mtop-fitmin_mtop,      fitmin_mtop, fitmax_mtop);
  TH1D *histo_mw_e   = new TH1D("histo_mw_e",   "histo_mw_e",   fitmax_mw-fitmin_mw,          fitmin_mw,   fitmax_mw);
  TH1D *histo_rbq_e  = new TH1D("histo_rbq_e",  "histo_rbq_e",  (fitmax_rbq-fitmin_rbq)/0.05, fitmin_rbq,  fitmax_rbq);

  for(unsigned int idx = 0; idx < fTTbarInfoTmp.size(); idx++){

    histo_mtop -> Fill(fTTbarInfoTmp[idx][3], fTTbarInfoTmp[idx][0]);
    histo_mw   -> Fill(fTTbarInfoTmp[idx][4], fTTbarInfoTmp[idx][0]);
    histo_rbq  -> Fill(fTTbarInfoTmp[idx][5], fTTbarInfoTmp[idx][0]);

  }  

  Double_t IntegralMtop = fmtop -> Integral(fitmin_mtop, fitmax_mtop);
  Double_t IntegralMw   = fmw   -> Integral(fitmin_mw,   fitmax_mw);
  Double_t IntegralRbq  = frbq  -> Integral(fitmin_rbq,  fitmax_rbq);

  fmtop -> SetParameter(npars_comb_mtop+3, 1.0/IntegralMtop*histo_mtop -> GetBinWidth(1)); 
  fmw   -> SetParameter(npars_comb_mw+1,   1.0/IntegralMw*histo_mw     -> GetBinWidth(1)); 
  frbq  -> SetParameter(npars_comb_rbq+3,  1.0/IntegralRbq*histo_rbq   -> GetBinWidth(1));

  // have to run first plot twice, root weirdness...
  MakeOverlayPlot(OutputFile, fmtop, histo_mtop, histo_mtop_e, fitmin_mtop, fitmax_mtop, "mtop", FileString);
  MakeOverlayPlot(OutputFile, fmtop, histo_mtop, histo_mtop_e, fitmin_mtop, fitmax_mtop, "mtop", FileString);
  MakeOverlayPlot(OutputFile, fmw,   histo_mw,   histo_mw_e,   fitmin_mw,   fitmax_mw,     "mw", FileString);
  MakeOverlayPlot(OutputFile, frbq,  histo_rbq,  histo_rbq_e,  fitmin_rbq,  fitmax_rbq,   "rbq", FileString);

  delete histo_mtop;
  delete histo_mw;
  delete histo_rbq;
  delete histo_mtop_e;
  delete histo_mw_e;
  delete histo_rbq_e;
}



void PseudoExperimentsFit::PrepareOverlayPlot_Dil(double mtop, double jsf, double bjsf, std::string OutputFile, std::string FileString)
{
  
  fmtop_dil -> SetParameter(npars_comb_mlb+0,   mtop); // mtop
  fmtop_dil -> SetParameter(npars_comb_mlb+1,    1.0); // mtop
                               
  TH1D *histo_mtop   = new TH1D("histo_mtop",   "histo_mtop",   (fitmax_mlb-fitmin_mlb)/2, fitmin_mlb, fitmax_mlb);
  TH1D *histo_mtop_e = new TH1D("histo_mtop_e", "histo_mtop_e", (fitmax_mlb-fitmin_mlb)/2, fitmin_mlb, fitmax_mlb);

  for(unsigned int idx = 0; idx < fTTbarInfoTmp.size(); idx++){

    histo_mtop -> Fill(fTTbarInfoTmp[idx][3], fTTbarInfoTmp[idx][0]);

  }  

  Double_t IntegralMtop = fmtop_dil -> Integral(fitmin_mlb, fitmax_mlb);

  std::cout << "Overlay plot, integral dilepton mlb = " << IntegralMtop << std::endl;

  fmtop_dil -> SetParameter(npars_comb_mlb+1, 1.0/IntegralMtop*histo_mtop   -> GetBinWidth(1)); 

  IntegralMtop = fmtop_dil -> Integral(fitmin_mlb, fitmax_mlb);

  std::cout << "Overlay plot, integral dilepton mlb nachher = " << IntegralMtop << std::endl;

  // have to run first plot twice, root weirdness...
  MakeOverlayPlot(OutputFile, fmtop_dil, histo_mtop, histo_mtop_e, fitmin_mlb, fitmax_mlb, "mlb", FileString);

  delete histo_mtop;
  delete histo_mtop_e;
}



void PseudoExperimentsFit::MakeOverlayPlot(std::string OutputFile, TF1 *helpFunc, TH1D *helpHist, TH1D *helpHist_e, double down, double up, std::string var, std::string FileString)
{

  TCanvas *c0 = new TCanvas("c0", "c0", 720, 900);

  TPad *pad1  = new TPad("pad1","pad1", 0.0, 0.323, 1.0, 1.00);
  TPad *pad2  = new TPad("pad2","pad2", 0.0, 0.010, 1.0, 0.350);
 
  //  SetAtlasStyle();

  pad1->SetBottomMargin(0.050);
  pad1->SetBorderMode(0);
  pad2->SetBottomMargin(0.3);

  pad1->SetTicks(1,1);
  pad2->SetTicks(1,1);

  pad1->Draw();
  pad2->Draw();

  SetAtlasStyle();

  pad1 -> cd();

  helpHist -> GetXaxis() -> SetRangeUser(down, up);
  helpHist -> GetYaxis() -> SetTitle("Number of events");
  helpHist -> GetYaxis() -> SetTitleOffset(1.4);
  
  TGaxis::SetMaxDigits(3);

  helpFunc -> SetLineColor(kRed);
  helpFunc -> SetLineWidth(3);
  
  
  helpHist -> Scale(1.0/helpHist -> Integral());
  helpHist -> Draw("SAME");
  helpFunc -> Draw("SAME");

  // std::cout << "Integral in overlay function = " << helpFunc -> Integral(fitmin_mlb, fitmax_mlb) << std::endl;

  TLatex l2;
  l2.SetTextAlign(9);
  l2.SetTextFont(72);
  l2.SetTextSize(0.04);
  l2.SetNDC();
  l2.DrawLatex(0.660, 0.875, "ATLAS");
  TLatex l3;
  l3.SetTextAlign(9);
  l3.SetTextSize(0.04);
  l3.SetNDC();
  l3.DrawLatex(0.775, 0.875, "Simulation");
  l3.DrawLatex(0.660, 0.835, "Internal");
  


  pad2 -> cd();

  for(int iBin = 1; iBin < helpHist -> GetNbinsX()+1; ++iBin){

    double contHist   = helpHist -> GetBinContent(iBin);
    double binCenter  = helpHist -> GetBinCenter(iBin);
    double contFunc   = helpFunc -> Eval(binCenter);
    double contHist_e = helpHist -> GetBinError(iBin);
    double ratio      = (contHist - contFunc)/contHist_e;
    double ratio_e    = ratio*contHist_e/contHist;
    
    if(contHist_e > 0){
      helpHist_e -> SetBinContent(iBin, ratio);
      helpHist_e -> SetBinError(iBin, ratio_e);

    }

  }


  if(var == "mtop")
    helpHist_e -> GetXaxis() -> SetTitle("m_{top}^{reco} [GeV]");

  if(var == "mw")
    helpHist_e -> GetXaxis() -> SetTitle("m_{W}^{reco} [GeV]");

  if(var == "rbq")
    helpHist_e -> GetXaxis() -> SetTitle("R_{bq}^{reco}");  

  if(var == "mlb")
    helpHist_e -> GetXaxis() -> SetTitle("m_{lb}^{reco} [GeV]");


  helpHist_e -> SetMaximum(7);
  helpHist_e -> SetMinimum(-7);
  helpHist_e -> SetLabelSize(0.08, "X");
  helpHist_e -> SetLabelOffset(0.025,"X");
  helpHist_e -> SetTitleOffset(1.3,"X");
  helpHist_e -> SetTitleSize(0.09, "X");
  helpHist_e -> SetLabelSize(0.09, "Y");
  helpHist_e -> SetNdivisions(305,"Y");
  helpHist_e -> GetYaxis() -> SetTitleOffset(1.55);
  helpHist_e -> GetYaxis() -> SetTitleFont(63);
  helpHist_e -> GetYaxis() -> SetTitleSize(23);
  helpHist_e -> GetYaxis() -> SetTitle("(Sim.-fit)/#sigma");
  helpHist_e -> SetLineWidth(3);
  helpHist_e -> SetMarkerStyle(20);
  helpHist_e -> SetMarkerSize(1);
  helpHist_e -> SetLineWidth(3);
  helpHist_e -> GetXaxis() -> SetRangeUser(down, up);
  helpHist_e -> GetYaxis() -> CenterTitle();

  TLine* tline = new TLine(down, 0, up, 0);
  tline -> SetLineColor(2);
  tline -> SetLineStyle(1);
  tline -> SetLineWidth(2);

  helpHist_e -> Draw("P");
  tline      -> Draw("SAME");

  c0 -> Print((OutputFile+"_"+FileString+"_"+var+".pdf").c_str());

  delete tline;

  delete pad1;
  delete pad2;

  delete c0;



}
