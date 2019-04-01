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
#include "TChain.h"
#include "TGraphErrors.h"
#include "TLatex.h"
#include "TLine.h"

#include "TopMass_13TeV_PseudoExp/AtlasStyle.h"
#include "TopMass_13TeV_PseudoExp/EvaluatePseudoExperiments.h"

// emacs -nw ~/TMT_8TeV/Munich_Dilepton/Analysis/Dilep_Pexp_Plot.C

using namespace std;

EvaluatePseudoExperiments::EvaluatePseudoExperiments(string InputFile, string OutputFolder, string FileString, int Dim, double mtop, double jsf, double bjsf)
{
  
  fInputFile    = InputFile;
  fOutputFolder = OutputFolder;
  fFileString   = FileString;
  fFitDimension = Dim;
  fMtopInput    = mtop;
  fJSFInput     = jsf;
  fBJSFInput    = bjsf;

  std::cout << "CONSTRUCTOR!!!! ------------------------------------------> " << mtop << "\t" << jsf << "\t" << bjsf << std::endl;

}


EvaluatePseudoExperiments::~EvaluatePseudoExperiments()
{

}


void EvaluatePseudoExperiments::ReadInputFile()
{

  TChain *inTree = new TChain("PETree");
  inTree -> Add(fInputFile.c_str());

  double out_mtop, out_mtop_e, out_mtop_el, out_mtop_eh;
  double out_jsf,  out_jsf_e,  out_jsf_el,  out_jsf_eh;
  double out_bjsf, out_bjsf_e, out_bjsf_el, out_bjsf_eh;
  double sum_PE,   sum_PE2;
  int    NDim;
  int    Converged;
  std::vector<double> *yield_lumi;
  std::vector<double> *yield_mc;

  inTree -> SetBranchAddress("mtop",       &out_mtop);
  inTree -> SetBranchAddress("mtop_e",     &out_mtop_e);
  inTree -> SetBranchAddress("mtop_el",    &out_mtop_el);
  inTree -> SetBranchAddress("mtop_eh",    &out_mtop_eh);
  inTree -> SetBranchAddress("jsf",        &out_jsf);
  inTree -> SetBranchAddress("jsf_e",      &out_jsf_e);
  inTree -> SetBranchAddress("jsf_el",     &out_jsf_el);
  inTree -> SetBranchAddress("jsf_eh",     &out_jsf_eh);
  inTree -> SetBranchAddress("bjsf",       &out_bjsf);
  inTree -> SetBranchAddress("bjsf_e",     &out_bjsf_e);
  inTree -> SetBranchAddress("bjsf_el",    &out_bjsf_el);
  inTree -> SetBranchAddress("bjsf_eh",    &out_bjsf_eh);
  inTree -> SetBranchAddress("NDim",       &NDim);
  inTree -> SetBranchAddress("Converged",  &Converged);
  inTree -> SetBranchAddress("sum_PE",     &sum_PE);
  inTree -> SetBranchAddress("sum_PE2",    &sum_PE2);
  inTree -> SetBranchAddress("yield_lumi", &yield_lumi);
  inTree -> SetBranchAddress("yield_mc",   &yield_mc);

  yield_lumi = 0;
  yield_mc   = 0;

  double yield_lumi_barlow = 0.0;
  double yield_mc_barlow   = 0.0;

  double sum_lumi_barlow = 0.0;
  double sum_mc_barlow   = 0.0;

  int nEvents = inTree -> GetEntries();

  // make a loop first to determine upper and lower edges
  double mtop_low    = 1000.0;
  double mtop_high   =   -1.0;
  double mtop_e_low  = 1000.0;
  double mtop_e_high =   -1.0;

  double jsf_low     = 1000.0;
  double jsf_high    =   -1.0;
  double jsf_e_low   = 1000.0;
  double jsf_e_high  =   -1.0;

  double bjsf_low    = 1000.0;
  double bjsf_high   =   -1.0;
  double bjsf_e_low  = 1000.0;
  double bjsf_e_high =   -1.0;

  // Barlow Corrections Factors for Pexps in case of oversampling:                                                                               
  // www.hep.man.ac.uk/preprints/manhep99-4.ps                                                                                                                                                             
  // note the BarlowCF is supposed to be used for the error on the mean:                                                                                                                                   
  // as example: the error on the mean goes with 1/sqrt(N). with the Barlow Correction as 1*BarlowCF.                                                                                                      
  bool UseBarlowCF = true;

  std::vector<double> BarlowCF_vec;

  for(int iEvent = 0; iEvent < nEvents; ++iEvent){

    inTree -> GetEntry(iEvent);

    // std::cout << "TEST = " << fMtopInput << "\t" << out_mtop << "\t" << out_mtop_e << "\t" << (fMtopInput-out_mtop)/out_mtop_e << std::endl;

    if(out_mtop < mtop_low)
      mtop_low = out_mtop;
    if(out_mtop > mtop_high)
      mtop_high = out_mtop;
    if(out_mtop_e < mtop_e_low)
      mtop_e_low = out_mtop_e;
    if(out_mtop_e > mtop_e_high)
      mtop_e_high = out_mtop_e;
    if(out_jsf < jsf_low)
      jsf_low = out_jsf;
    if(out_jsf > jsf_high)
      jsf_high = out_jsf;
    if(out_jsf_e < jsf_e_low)
      jsf_e_low = out_jsf_e;
    if(out_jsf_e > jsf_e_high)
      jsf_e_high = out_jsf_e;
    if(out_bjsf < bjsf_low)
      bjsf_low = out_bjsf;
    if(out_bjsf > bjsf_high)
      bjsf_high = out_bjsf;
    if(out_bjsf_e < bjsf_e_low)
      bjsf_e_low = out_bjsf_e;
    if(out_bjsf_e > bjsf_e_high)
      bjsf_e_high = out_bjsf_e;
    
    if(iEvent == 0){

      for(int k = 0; k < yield_mc -> size(); ++k){

	sum_lumi_barlow += yield_lumi -> at(k);
	sum_mc_barlow   += yield_mc   -> at(k);
	
	BarlowCF_vec.push_back(BarCor(1, 3, yield_mc -> at(k), yield_lumi -> at(k), nEvents));
	
	
	// yield_lumi_barlow = yield_lumi -> at(k);
	// yield_mc_barlow   = yield_mc   -> at(k);
	//     std::cout << k << "\t" << yield_lumi_barlow << "\t" << yield_mc_barlow << "\t" << BarCor(1, 3, yield_mc_barlow, yield_lumi_barlow, nEvents) << std::endl;
	
      }
    }

  }


  double BarlowCorrection = 0.0;

  for(int k = 0; k < yield_mc -> size(); ++k){

    //    std::cout << yield_lumi -> at(k)/sum_lumi_barlow << "\t" << BarlowCF_vec[k] << std::endl;

    BarlowCorrection += yield_lumi -> at(k)/sum_lumi_barlow*BarlowCF_vec[k];

  }

  // test
  //  BarlowCorrection = 0.4;

  mtop_low    = mtop_low*0.998;
  mtop_high   = mtop_high*1.002;
  mtop_e_low  = mtop_e_low*0.95;
  mtop_e_high = mtop_e_high*1.05;
    
  jsf_low     = jsf_low*0.9;
  jsf_high    = jsf_high*1.1;
  jsf_e_low   = jsf_e_low*0.95;
  jsf_e_high  = jsf_e_high*1.05;

  bjsf_low    = bjsf_low*0.9;
  bjsf_high   = bjsf_high*1.1;
  bjsf_e_low  = bjsf_e_low*0.95;
  bjsf_e_high = bjsf_e_high*1.05;


  TH1D *hist_mtop      = new TH1D("mtop",      "mtop",       50, mtop_low,   mtop_high);
  TH1D *hist_mtop_e    = new TH1D("mtop_e",    "mtop_e",     50, mtop_e_low, mtop_e_high);
  TH1D *hist_mtop_pull = new TH1D("mtop_pull", "mtop_pull",  51, -5.5,       5.5);
  TH1D *hist_mtop_diff = new TH1D("mtop_diff", "mtop_diff",  51, -0.55,      0.55);

  TH1D *hist_jsf       = new TH1D("jsf",       "jsf",        50, jsf_low,    jsf_high);
  TH1D *hist_jsf_e     = new TH1D("jsf_e",     "jsf_e",      50, jsf_e_low,  jsf_e_high);
  TH1D *hist_jsf_pull  = new TH1D("jsf_pull",  "jsf_pull",   51, -5.5,       5.5);
  TH1D *hist_jsf_diff  = new TH1D("jsf_diff",  "jsf_diff",   51, -0.55,      0.55);

  TH1D *hist_bjsf      = new TH1D("bjsf",      "bjsf",       50, bjsf_low,   bjsf_high);
  TH1D *hist_bjsf_e    = new TH1D("bjsf_e",    "bjsf_e",     50, bjsf_e_low, bjsf_e_high);
  TH1D *hist_bjsf_pull = new TH1D("bjsf_pull", "bjsf_pull",  51, -5.5,       5.5);
  TH1D *hist_bjsf_diff = new TH1D("bjsf_diff", "bjsf_diff",  51, -0.55,      0.55);

  // rescale the error
  double error_sf = 1.0;

  for(int iEvent = 0; iEvent < nEvents; ++iEvent){

    inTree -> GetEntry(iEvent);

    //yield_data = ;
    //yield_mc   = ;

    // don't know yet what to do here
    error_sf = sqrt(sum_PE2/sum_PE);

    //    std::cout << error_sf << "\t" << sum_PE2 << "\t" << sum_PE << std::endl;


    //    std::cout << out_mtop_e << "\t" << out_mtop_el << "\t" << out_mtop_eh << std::endl;

    double pull_mtop = (fMtopInput - out_mtop)/out_mtop_e/error_sf;
    double pull_jsf  = (fJSFInput  - out_jsf)/out_jsf_e/error_sf;
    double pull_bjsf = (fBJSFInput - out_bjsf)/out_bjsf_e/error_sf;

    //    if (out_mtop <= fMtopInput)  pull_mtop = (fMtopInput - out_mtop) / out_mtop_eh;
    // else pull_mtop = (out_mtop - fMtopInput) / out_mtop_el;

    double diff_mtop = fMtopInput - out_mtop;
    double diff_jsf  = fJSFInput  - out_jsf;
    double diff_bjsf = fBJSFInput - out_bjsf;

    hist_mtop      -> Fill(out_mtop);
    hist_mtop_e    -> Fill(out_mtop_e);
    hist_mtop_pull -> Fill(pull_mtop);
    hist_mtop_diff -> Fill(diff_mtop);

    hist_jsf       -> Fill(out_jsf);
    hist_jsf_e     -> Fill(out_jsf_e);
    hist_jsf_pull  -> Fill(pull_jsf);
    hist_jsf_diff  -> Fill(diff_jsf);

    hist_bjsf      -> Fill(out_bjsf);
    hist_bjsf_e    -> Fill(out_bjsf_e);
    hist_bjsf_pull -> Fill(pull_bjsf);
    hist_bjsf_diff -> Fill(diff_bjsf);

  }

  //  double BarlowCorrection = 0.0; // BarCor(1, 3, yield_mc_barlow, yield_lumi_barlow, nEvents);

  // now calculate BarlowCorrection taking into account the relative fractions


  

  //  std::cout << "Barlow CF = " << BarlowCorrection << std::endl; //  "\t" << yield_mc_barlow << "\t" << yield_lumi_barlow << "\t" << nEvents << std::endl;

  //  if (UseBarlowCF) width = histo_outmass[massbin]->GetRMS()*BarlowCF[massbin];

  // now store output in vectors for later usage
  fVectorMtop.clear();
  fVectorMtop.push_back(hist_mtop_diff->GetMean());
  fVectorMtop.push_back(hist_mtop_diff->GetMeanError());
  if(nEvents > 1)
    fVectorMtop.push_back(hist_mtop_diff->GetRMS()*BarlowCorrection);
  else
    fVectorMtop.push_back(hist_mtop_e->GetMean());
  fVectorMtop.push_back(hist_mtop_e->GetMean());
  fVectorMtop.push_back(hist_mtop_pull->GetRMS());
  fVectorMtop.push_back(hist_mtop_pull->GetRMSError());

  fVectorJSF.clear();
  fVectorJSF.push_back(hist_jsf_diff->GetMean());
  fVectorJSF.push_back(hist_jsf_diff->GetMeanError());
  fVectorJSF.push_back(hist_jsf_diff->GetRMS()*BarlowCorrection);
  fVectorJSF.push_back(hist_jsf_e->GetMean());
  fVectorJSF.push_back(hist_jsf_pull->GetRMS());
  fVectorJSF.push_back(hist_jsf_pull->GetRMSError());

  fVectorBJSF.clear();
  fVectorBJSF.push_back(hist_bjsf_diff->GetMean());
  fVectorBJSF.push_back(hist_bjsf_diff->GetMeanError());
  fVectorBJSF.push_back(hist_bjsf_diff->GetRMS()*BarlowCorrection);
  fVectorBJSF.push_back(hist_bjsf_e->GetMean());
  fVectorBJSF.push_back(hist_bjsf_pull->GetRMS());
  fVectorBJSF.push_back(hist_bjsf_pull->GetRMSError());


  // now make pretty plots  
  MakeCrosscheckPlots(hist_mtop,      "mtop",      "m_{top}^{out} [GeV]",                "Number of PE");
  MakeCrosscheckPlots(hist_mtop_e,    "mtop_err",  "#sigma(m_{top}^{out})",              "Number of PE");
  MakeCrosscheckPlots(hist_mtop_pull, "mtop_pull", "Pull(m_{top}^{out})",                "Number of PE");
  MakeCrosscheckPlots(hist_mtop_diff, "mtop_diff", "m_{top}^{in} - m_{top}^{out} [GeV]", "Number of PE");

  if(fFitDimension > 1){

    MakeCrosscheckPlots(hist_jsf,       "jsf",       "JSF^{out}",                    "Number of PE");
    MakeCrosscheckPlots(hist_jsf_e,     "jsf_err",   "#sigma(JSF^{out})",            "Number of PE");
    MakeCrosscheckPlots(hist_jsf_pull,  "jsf_pull",  "Pull(JSF^{out})",              "Number of PE");
    MakeCrosscheckPlots(hist_jsf_diff,  "jsf_diff",  "JSF^{in} - JSF^{out}",         "Number of PE");

    if(fFitDimension > 2){

      MakeCrosscheckPlots(hist_bjsf,      "bjsf",      "bJSF^{out}",                   "Number of PE");
      MakeCrosscheckPlots(hist_bjsf_e,    "bjsf_err",  "#sigma(bJSF^{out})",           "Number of PE");
      MakeCrosscheckPlots(hist_bjsf_pull, "bjsf_pull", "Pull(bJSF^{out})",             "Number of PE");
      MakeCrosscheckPlots(hist_bjsf_diff, "bjsf_diff", "bJSF^{in} - bJSF^{out}",       "Number of PE");
      
    }

  }

  delete hist_mtop;
  delete hist_mtop_e;
  delete hist_mtop_pull;
  delete hist_mtop_diff;
  delete hist_jsf;
  delete hist_jsf_e;
  delete hist_jsf_pull;
  delete hist_jsf_diff;
  delete hist_bjsf;
  delete hist_bjsf_e;
  delete hist_bjsf_pull;
  delete hist_bjsf_diff;

  delete inTree;

}


void EvaluatePseudoExperiments::MakeCrosscheckPlots(TH1D *histo, std::string var, std::string XTitle, std::string YTitle){

  TCanvas *c0 = new TCanvas("c0", "c0", 900, 900);  

  SetAtlasStyle();

  histo -> GetXaxis() -> SetTitle(XTitle.c_str());
  histo -> GetYaxis() -> SetTitle(YTitle.c_str());
  histo -> GetXaxis() -> SetTitleOffset(1.4);
  histo -> GetYaxis() -> SetTitleOffset(1.3);
  histo -> GetXaxis() -> SetLabelSize(0.045);
  histo -> GetYaxis() -> SetLabelSize(0.045);
  histo -> GetXaxis() -> SetTitleSize(0.045);
  histo -> GetYaxis() -> SetTitleSize(0.045);
  histo -> Draw();

  TLatex l2;
  l2.SetTextAlign(9);
  l2.SetTextFont(72);
  l2.SetTextSize(0.04);
  l2.SetNDC();
  l2.DrawLatex(0.610, 0.865, "ATLAS");
  TLatex l3;
  l3.SetTextAlign(9);
  l3.SetTextSize(0.04);
  l3.SetNDC();
  l3.DrawLatex(0.745, 0.865, "Simulation");
  l3.DrawLatex(0.610, 0.815, "Internal");


  c0 -> Print((fOutputFolder+"/CheckSingle_"+fFileString+"_"+var+".pdf").c_str());

  delete c0;

  
}


void EvaluatePseudoExperiments::MakeClosurePlot(std::vector<double> XVal, std::vector<double> YVal, std::vector<double> YVal_e, std::string XTitle, std::string YTitle, std::string OutputFile, std::string var, std::string type, std::string dim, std::string N_PE)
{

  // transfer the values into TGraphs
  double x[5]  = {XVal[0],   XVal[1],   XVal[2],   XVal[3],   XVal[4]}; //,   XVal[5],  XVal[6],    XVal[7],   XVal[8]};
  double y[5]  = {YVal[0],   YVal[1],   YVal[2],   YVal[3],   YVal[4]}; //,   YVal[5],   YVal[6],   YVal[7],   YVal[8]};
  double ye[5] = {YVal_e[0], YVal_e[1], YVal_e[2], YVal_e[3], YVal_e[4]}; //, YVal_e[5], YVal_e[6], YVal_e[7], YVal_e[8]};
  double xe[5] = {0, 0, 0, 0, 0}; //, 0, 0, 0, 0};

  TGraphErrors *graph  = new TGraphErrors(5, x, y, xe, ye);

  for(int i = 0; i < 5; ++i)
    std::cout << i << "\t" << x[i] << "\t" << y[i] << "\t" << ye[i] << std::endl; 

  graph -> SetLineWidth(2);
  graph -> SetMarkerStyle(20);
  graph -> SetMarkerSize(1.45);
  graph -> SetLineColor(kBlack);
  graph -> SetLineStyle(1);

  TCanvas *c0 = new TCanvas("c0", "c0", 1100, 900);

  SetAtlasStyle();

  gStyle -> SetPadLeftMargin(0.155);

  graph -> GetXaxis() -> SetTitle(XTitle.c_str());
  graph -> GetYaxis() -> SetTitle(YTitle.c_str());
  graph -> GetXaxis() -> SetTitleOffset(1.45);
  graph -> GetYaxis() -> SetTitleOffset(1.55);
  graph -> GetXaxis() -> SetLabelSize(0.045);
  graph -> GetYaxis() -> SetLabelSize(0.045);

  if(type != "diff"){

    graph -> SetMinimum(0.75);
    graph -> SetMaximum(1.25);

  }
  else{

    // graph -> SetMinimum(-YVal[3]);
    // graph -> SetMaximum(2.5*YVal[3]);

    graph -> SetMinimum(-0.25);
    graph -> SetMaximum(0.25);

    if(var != "mtop"){

      graph -> SetMinimum(-0.003);
      graph -> SetMaximum(0.003);

    }
  
  }

  graph -> Draw("AP");

  double line_min = 170.75;
  double line_max = 174.25;
  double line_pos = 0.0;

  if(var != "mtop"){
   
    line_min = 0.9775;
    line_max = 1.0225;

  }

  if(type == "pull")
    line_pos = 1.0;

  TLine* tline = new TLine(line_min, line_pos, line_max, line_pos);
  tline -> SetLineColor(1);
  tline -> SetLineStyle(2);
  tline -> SetLineWidth(2);
  tline -> Draw("SAME");

  TF1 *func = new TF1("func", "[0]", line_min, line_max);
  graph -> Fit(func, "n0q");
  
  std::stringstream oss1, oss2;
  oss1   << setprecision(2) << func -> GetParameter(0);
  oss2   << setprecision(1) << func -> GetParError(0);
  
  func -> SetLineColor(kRed);
  func -> Draw("SAME");

  TLatex l2;
  l2.SetTextAlign(9);
  l2.SetTextFont(72);
  l2.SetTextSize(0.04);
  l2.SetNDC();
  l2.DrawLatex(0.660, 0.265, "ATLAS");
  TLatex l3;
  l3.SetTextAlign(9);
  l3.SetTextSize(0.04);
  l3.SetNDC();
  l3.DrawLatex(0.775, 0.265, "Simulation");
  l3.DrawLatex(0.660, 0.215, "Internal");

  if(type == "diff" && var == "mtop")
    l3.DrawLatex(0.210, 0.855, ("m_{top}^{in} - m_{top}^{out} = "+oss1.str()+" #pm "+oss2.str()+" [GeV]").c_str());
  if(type == "diff" && var == "jsf")
    l3.DrawLatex(0.210, 0.855, ("JSF^{in} - JSF^{out} = "+oss1.str()+" #pm "+oss2.str()).c_str());
  if(type == "diff" && var == "bjsf")
    l3.DrawLatex(0.210, 0.855, ("bJSF^{in} - bJSF^{out} = "+oss1.str()+" #pm "+oss2.str()).c_str());
  if(type == "pull")
    l3.DrawLatex(0.210, 0.855, ("Pull width = "+oss1.str()+" #pm "+oss2.str()).c_str());


  l3.DrawLatex(0.210, 0.215, (dim+" fit, "+N_PE+" PE").c_str());
  
  c0 -> Print(OutputFile.c_str());

  delete c0;
  delete func;
  delete tline;
  delete graph;

}



//-RN:----------------------------------------------------------
//-RN: Calculate Barlow correlation
//-RN:----------------------------------------------------------
//-RN:       IndRho < 0 <==> Print out
//-RN: Abs(IndRho) == 1 <==> without replacement
//-RN: Abs(IndRho) == 2 <==>    with replacement [1-exp(r)]
//-RN: Abs(IndRho) == 3 <==>    with replacement [Eq 7]
//-RN:           EvtSam <==> Number of events per sample
//-RN:           EvtTot <==> Total number of events >= EvtSam
//-RN:----------------------------------------------------------

double EvaluatePseudoExperiments::BarRho(int IndRho =  2, double EvtTot = 1000., double EvtSam = 100.){

  //-RN: Reset rho value
  double RhoVal = -1.;

  //-RN: Check print flag  
  int IndPri = 0;
  if(IndRho < 0)IndPri = 1;

  //-RN: Check steering flag
  int IndFla = TMath::Abs(IndRho);
  if(IndFla > 3 || IndFla == 0){
    if(IndPri > 0)printf("... BarRho: Bad steering flag %i \n",IndRho);
    return RhoVal;
  }

  //-RN: Check numbers of events per sample and in total
  if(EvtSam > EvtTot || EvtSam < 0 || EvtTot < 0){
    if(IndPri > 0)printf("... BarRho: Bad N_event input %8.0f %8.0f \n", 
			 EvtSam, EvtTot);
    return RhoVal;
  }

  //-RN: Define ratio
  double RatEvt = EvtSam / EvtTot;

  //-RN: Define variables for IndFla == 2
  double        ri = 0., rj = 0.;
  const int NumPro = 6;
  double    ProNum[NumPro] = {0.};
  double    RhoSum = 0.;

  //-RN: Calculate depending on IndFla
  if(IndFla == 1){
    //-RN: Without replacement
    RhoVal = RatEvt;
    if(IndPri > 0)printf("... BarRho: Without replacement");
  }else if(IndFla == 2){
    //-RN: With replacement
    RhoVal = 1. - TMath::Exp(-1. * RatEvt);
    if(IndPri > 0)printf("... BarRho:    With replacement [1-exp(r)]");
  }else if(IndFla == 3){
    //-RN: Without replacement but Eq.7
    for(int i=0; i<NumPro; i++){
      ri        = static_cast<double>(i);
      ProNum[i] = TMath::Poisson(ri,RatEvt);
    }
    RhoVal = 1. - ProNum[0];
    for(int i=1; i<NumPro; i++){
      ri     = static_cast<double>(i);
      rj     = 0.;
      RhoSum = 0;
      for(int j=i; j>0; j--){
	rj = rj + 1.;
	RhoSum = RhoSum + ProNum[j] * rj;
      }
      RhoVal = RhoVal - ProNum[i]/(ri+1.) * RhoSum;
    }
    if(IndPri > 0)printf("... BarRho:    With replacement [Eq 7]");
  }

  //-RN: Print out if wanted and return
  if(IndPri > 0)printf(" ==> Correlation = %8.6f \n", RhoVal);
  return RhoVal;
}

//-RN:----------------------------------------------------------
//-RN: Calculate Barlow correction to the uncertainty of the mean
//-RN:----------------------------------------------------------
//-RN:       IndCor < 0 <==> Correction to "sigma" in Eq(x) and Print out
//-RN:                       sigma -> sigma * BarCor
//-RN: Abs(IndCor) == 1 <==> Eq(1)
//-RN: Abs(IndCor) == 2 <==> Eq(2)
//-RN: Abs(IndCor) == 3 <==> Eq(3)
//-RN:           IndRho <==> Steering for BarRho
//-RN:           EvtSam <==> Number of events per sample
//-RN:           EvtTot <==> Total number of events >= EvtSam
//-RN:           NumPex <==> Number of pseudo-experiments > 0
//-RN:----------------------------------------------------------

double EvaluatePseudoExperiments::BarCor(int    IndCor =     1, int    IndRho =    2, 
                double EvtTot = 1000., double EvtSam = 100., 
		double NumPex =  100){

  //-RN: Reset correction value
  double BarVal = -1.;

  //-RN: Check print flag  
  int IndPri = 0;
  if(IndCor < 0)IndPri = 1;

  //-RN: Check steering flag
  int IndFla = TMath::Abs(IndCor);
  if(IndFla > 3 || IndFla == 0){
    if(IndPri > 0)printf("... BarCor: Bad steering flag %i \n",IndCor);
    return BarVal;
  }

  //-RN: Check numbers of events per sample and in total
  if(EvtSam > EvtTot || EvtSam < 0 || EvtTot < 0){
    if(IndPri > 0)printf("... BarCor: bad N_event input %8.0f %8.0f \n", 
			 EvtSam, EvtTot);
    return BarVal;
  }

  //-RN: Check number of pseudo experiments
  if(NumPex < 1){
    if(IndPri > 0)printf("... BarCor: Bad number of samples %8.0f \n", NumPex);
    return BarVal;
  }

  //-RN: Get Correlation 
  double RhoVal = BarRho(IndRho, EvtTot, EvtSam);

  //  std::cout << "RHO == " << RhoVal << std::endl;

  if(RhoVal == -1.)return BarVal;

  //-RN: Calculate correction to ...
  if(IndFla == 1){
    // Sigma from Eq 1
    BarVal = TMath::Sqrt((1. + (NumPex - 1.) * RhoVal) / NumPex);
    if(IndPri > 0)printf("... BarCor: Eq(1)");
  }else{
    BarVal = (1. + (NumPex - 1.) * RhoVal * RhoVal) / NumPex;
    if(IndFla == 2){
      // Sigma from Eq 2
      BarVal = 2. * BarVal;
      BarVal = TMath::Sqrt(BarVal);
      if(IndPri > 0)printf("... BarCor: Eq(2)");
    }else if(IndFla == 3){
      // Sigma from Eq 3
      BarVal = BarVal / 2.;
      if(IndPri > 0)printf("... BarCor: Eq(3)");
    }
    BarVal = TMath::Sqrt(BarVal);
  }

  //-RN: Print out if wanted and return
  if(IndPri > 0)printf(" ==> Correction = %8.6f \n", BarVal);
  return BarVal;
}

