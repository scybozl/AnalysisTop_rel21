#include "TopMass_13TeV_Parameterization/SepFitPar.h" 
#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions
#include "TopMass_13TeV_Parameterization/FCN.h"
#include "TopMass_13TeV_Parameterization/MakePlots.h" 
#include "TopMass_13TeV_Parameterization/ConfigClass.h"

#include "TChain.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TH2D.h"
#include "TSystem.h"
#include "TGraphErrors.h"
#include "TMinuit.h"
#include "TMinuitMinimizer.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>

using namespace std;


SepFitPar::SepFitPar(){}
SepFitPar::~SepFitPar(){}
TString category;
int npars_sep;

void SepFitPar::GetInitPars(TString S_hist = "hist_klf_window_mtop_reco", TString S_config = "../TopMass_13TeV_FrMu/TopMass_13TeV_Parameterization/data/MainConfigFile_LJ"){

  //Make output directory
  TString output_dir = "sepfit_output/";
  gSystem->Exec("mkdir -p " + output_dir);

  //Check if histogram name is valid
  double fitmin;
  double fitmax;
  if(S_hist == "h_mtop_param"){
    category = "mtop";
    fitmin = fitmin_mtop;
    fitmax = fitmax_mtop;
    npars_sep = npars_sep_mtop;
  }
  else if(S_hist == "h_mw_orig"){
    category = "mw";
    fitmin = fitmin_mw;
    fitmax = fitmax_mw;
    npars_sep = npars_sep_mw;
  }
  else if(S_hist == "h_rbq_orig"){
    category = "rbq";
    fitmin = fitmin_rbq;
    fitmax = fitmax_rbq;
    npars_sep = npars_sep_rbq;
  }
  else if((S_hist == "h_mlb") || 
	  (S_hist == "hist_mlb") || 
	  (S_hist == "hist_klf_window_mlb_reco") || 
	  (S_hist == "hist_klf_original_mlb_reco")){
    category = "mlb";
    fitmin = fitmin_mlb;
    fitmax = fitmax_mlb;
    npars_sep = npars_sep_mlb;
  }
  else if(S_hist == "hist_rbq_DL"){
    category = "rbq_DL";
    fitmin = fitmin_rbq_DL;
    fitmax = fitmax_rbq_DL;
    npars_sep = npars_sep_rbq_DL;
  }
  else return;

  //Declare groups of files and their mtop/jsf/bjsf
  vector<pair<double,TString>> v_mtop;
  vector<pair<double,TString>> v_JSF;
  vector<pair<double,TString>> v_bJSF;

  //Get info from Config file
  std::shared_ptr<ConfigClass> fConfig(new ConfigClass());
  fConfig -> readSettingsFromConfig(S_config);
  TString FileList = fConfig -> GetFileList();
  string line;
  ifstream ListFile;
  ListFile.open(FileList);
  while (ListFile.good()) {
    
    getline(ListFile, line);
    if(line == "")
      continue;
    
    std::istringstream input_line(line);
    string name_s;
    string mtop_s;
    string jsf_s;
    string bjsf_s;
    input_line >> name_s;
    input_line >> mtop_s;
    input_line >> jsf_s;
    input_line >> bjsf_s;
    TString filename = name_s;
    double mtop_d = TString(mtop_s).Atof();
    double jsf_d = TString(jsf_s).Atof();
    double bjsf_d = TString(bjsf_s).Atof();

    std::cout << "========================================================>  " << filename << "\t" << mtop_d << "\t" << jsf_d << "\t" << bjsf_d << std::endl;
    
    if((jsf_d == 1.00) && (bjsf_d == 1.00))
      v_mtop.push_back(make_pair(mtop_d,filename));
    if((mtop_d == 172.5) && (bjsf_d == 1.00))
      v_JSF.push_back(make_pair(jsf_d,filename));
    if((mtop_d == 172.5) && (jsf_d == 1.00))
      v_bJSF.push_back(make_pair(bjsf_d,filename));
  }
  
  //Sort vector of pairs by their first element (mtop/jsf/bjsf)
  sort(v_mtop.begin(),v_mtop.end());
  sort(v_JSF.begin(),v_JSF.end());
  sort(v_bJSF.begin(),v_bJSF.end());

  //Get separate fits
  vector<TF1*> v_func_mtop;
  vector<TF1*> v_func_JSF;
  vector<TF1*> v_func_bJSF;
  for(unsigned int mtop_idx = 0; mtop_idx < v_mtop.size(); mtop_idx++){
    char char_name[10];
    sprintf(char_name,"mtop_%0.1f",v_mtop.at(mtop_idx).first);
    TString func_name = char_name;

    std::cout << "Sep fits = " << v_mtop.at(mtop_idx).first << "\t" << v_mtop.at(mtop_idx).second << "\t" << S_hist << "\t" << func_name << "\t" << fitmin << "\t" << fitmax << std::endl; 

    v_func_mtop.push_back((TF1*) SepFit(v_mtop.at(mtop_idx).second, S_hist, func_name, fitmin, fitmax, output_dir));
  }
  for(unsigned int JSF_idx = 0; JSF_idx < v_JSF.size(); JSF_idx++){
    char char_name[10];
    sprintf(char_name,"JSF_%0.2f",v_JSF.at(JSF_idx).first);
    TString func_name = char_name;
    v_func_JSF.push_back((TF1*) SepFit(v_JSF.at(JSF_idx).second, S_hist, func_name, fitmin, fitmax, output_dir));
  }
  for(unsigned int bJSF_idx = 0; bJSF_idx < v_bJSF.size(); bJSF_idx++){
    char char_name[10];
    sprintf(char_name,"bJSF_%0.2f",v_bJSF.at(bJSF_idx).first);
    TString func_name = char_name;
    v_func_bJSF.push_back((TF1*) SepFit(v_bJSF.at(bJSF_idx).second, S_hist, func_name, fitmin, fitmax, output_dir));
  }

  //Prepare output file
  TFile* outFile = new TFile(output_dir + category + "_pars_init.root","RECREATE");
  vector<double> vmtop_parA;
  vector<double> vmtop_parB;
  vector<double> vJSF_parA;
  vector<double> vJSF_parB;
  vector<double> vbJSF_parA;
  vector<double> vbJSF_parB;
  TTree *ttree = new TTree("pars_init","Tree with vectors");
  ttree->Branch("vmtop_parA",&vmtop_parA);
  ttree->Branch("vmtop_parB",&vmtop_parB);
  ttree->Branch("vJSF_parA",&vJSF_parA);
  ttree->Branch("vJSF_parB",&vJSF_parB);
  ttree->Branch("vbJSF_parA",&vbJSF_parA);
  ttree->Branch("vbJSF_parB",&vbJSF_parB);

  //parameters vs mtop,JSF,bJSF
  vector<TString> dep = {"mtop","JSF","bJSF"};
  for(unsigned int depidx = 0; depidx < dep.size(); depidx++){
    outFile->mkdir(dep.at(depidx) + "_canvas",dep.at(depidx) + "_canvas");
    outFile->cd(dep.at(depidx) + "_canvas");
    for(int paridx = 0; paridx < npars_sep; paridx++){
      char temp[2]; sprintf(temp,"%d",paridx);
      TString sparidx = temp;
      TCanvas* c_par = new TCanvas("par" + sparidx + "_vs_" + dep.at(depidx),"par" + sparidx + "_vs_" + dep.at(depidx), 800, 10, 600, 500);
      c_par->cd();

      //Make TGraph of parameter values 
      TGraphErrors* parTG;
      if(dep.at(depidx) == "mtop"){
	parTG = new TGraphErrors((int) v_mtop.size());
	for(unsigned int mtop_idx = 0; mtop_idx < v_mtop.size(); mtop_idx++){
	  parTG->SetPoint(mtop_idx, v_mtop.at(mtop_idx).first, v_func_mtop.at(mtop_idx)->GetParameter(paridx));
	  parTG->SetPointError(mtop_idx, 0, v_func_mtop.at(mtop_idx)->GetParError(paridx));
	}
	parTG->GetXaxis()->SetTitle("m_{top} [GeV]");
      }
      else if(dep.at(depidx) == "JSF"){
	parTG = new TGraphErrors((int) v_JSF.size());
	for(unsigned int JSF_idx = 0; JSF_idx < v_JSF.size(); JSF_idx++){
	  parTG->SetPoint(JSF_idx, v_JSF.at(JSF_idx).first, v_func_JSF.at(JSF_idx)->GetParameter(paridx));
	  parTG->SetPointError(JSF_idx, 0, v_func_JSF.at(JSF_idx)->GetParError(paridx));
	}
	parTG->GetXaxis()->SetTitle("JSF");
      }
      else if(dep.at(depidx) == "bJSF"){
	parTG = new TGraphErrors((int) v_bJSF.size());
	for(unsigned int bJSF_idx = 0; bJSF_idx < v_bJSF.size(); bJSF_idx++){
	  parTG->SetPoint(bJSF_idx, v_bJSF.at(bJSF_idx).first, v_func_bJSF.at(bJSF_idx)->GetParameter(paridx));
	  parTG->SetPointError(bJSF_idx, 0, v_func_bJSF.at(bJSF_idx)->GetParError(paridx));
	}
	parTG->GetXaxis()->SetTitle("bJSF");
      }
      parTG->GetYaxis()->SetTitle("par[" + sparidx + "]");
      parTG->GetYaxis()->SetRangeUser(parTG->GetYaxis()->GetXmin(),1.05*(parTG->GetYaxis()->GetXmax()));
      parTG->Draw("AP");
      
      //Linear fit to TGraph
      TF1* linfit;   
      if(dep.at(depidx) == "mtop")
	linfit = new TF1("linfit", linpar_function_mtop, parTG->GetXaxis()->GetXmin(), parTG->GetXaxis()->GetXmax(), 2);   
      else
	linfit = new TF1("linfit", linpar_function_SF, parTG->GetXaxis()->GetXmin(), parTG->GetXaxis()->GetXmax(), 2);   
      linfit->SetLineColor(2);
      parTG->Fit(linfit,"FQR");
      
      double par_a = linfit->GetParameter(0);
      double par_a_err = linfit->GetParError(0);
      double par_b = linfit->GetParameter(1);
      double par_b_err = linfit->GetParError(1);
      double lin_chisq = linfit->GetChisquare();
      int lin_ndf = linfit->GetNDF();
      double lin_prob = linfit->GetProb();

      //TTree output
      if(dep.at(depidx) == "mtop"){
	vmtop_parA.push_back(par_a);
	vmtop_parB.push_back(par_b);
      }
      else if(dep.at(depidx) == "JSF"){
	vJSF_parA.push_back(par_a);
	vJSF_parB.push_back(par_b);
      }
      else if(dep.at(depidx) == "bJSF"){
	vbJSF_parA.push_back(par_a);
	vbJSF_parB.push_back(par_b);
      }
      
      //Add fit details to canvas
      stringstream spar_a; spar_a << setprecision(3) << par_a;
      stringstream spar_a_err; spar_a_err << setprecision(3) << par_a_err;
      stringstream spar_b; spar_b << setprecision(3) << par_b;
      stringstream spar_b_err; spar_b_err << setprecision(3) << par_b_err;
      stringstream schisq; schisq << setprecision(3) << lin_chisq;
      stringstream sndf; sndf << lin_ndf;
      stringstream sprob; sprob << setprecision(3) << lin_prob;
      TLatex x2;
      x2.SetTextAlign(9);
      x2.SetTextSize(0.04);
      x2.SetTextColor(2);
      x2.SetNDC();
      if(dep.at(depidx) == "mtop")
	x2.DrawLatex(0.2, 0.85, "par[" + sparidx + "] = a + b*(m_{top} - 172.5 GeV)");
      else if(dep.at(depidx) == "JSF")
	x2.DrawLatex(0.2, 0.85, "par[" + sparidx + "] = a + b*(JSF - 1.00)");
      else if(dep.at(depidx) == "bJSF")
	x2.DrawLatex(0.2, 0.85, "par[" + sparidx + "] = a + b*(bJSF - 1.00)");
      x2.DrawLatex(0.2, 0.80, ("a = " + spar_a.str() + " #pm " + spar_a_err.str()).c_str());
      x2.DrawLatex(0.2, 0.75, ("b = " + spar_b.str() + " #pm " + spar_b_err.str()).c_str());
      x2.DrawLatex(0.2, 0.70, ("P(#chi^{2},ndf) = P(" + schisq.str() + "," + sndf.str() + ") = " + sprob.str()).c_str());
      
      c_par->SaveAs(output_dir + category + "_linfit_" + c_par->GetName() + ".pdf","recreate");
      c_par->Write();
      c_par->Close();
      linfit->Delete();
      parTG->Delete();
    }  
  }
  outFile->cd();
  ttree->Fill();
  ttree->Write();
  outFile->Close();

}



TF1* SepFitPar::SepFit(TString S_file, TString S_hist, TString func_name, double fitmin, double fitmax, TString out_dir){

  TString xaxis_title;
  TString xaxis_unit;

  TFile* f_file = TFile::Open(S_file);
  TH1D* h_hist = (TH1D*) f_file->Get(S_hist);
  h_hist->Sumw2();
  double histmin = h_hist->GetXaxis()->GetXmin();
  double histmax = h_hist->GetXaxis()->GetXmax();
  h_hist->GetXaxis()->SetRangeUser(fitmin,fitmax);
  h_hist->Scale(1./h_hist->Integral());//BP Change "width" back or keep everywhere!!!
  h_hist->GetXaxis()->SetRangeUser(histmin,histmax);

  TF1* f_func;

  std::cout << "HIER !!!!!!!!!!!!!!!!!!!!!     "  << npars_sep << "\t" << pars_init_mtop.size() << "\t" << pars_name_mtop.size()  <<  std::endl;

  if(S_hist == "h_mtop_param"){
    xaxis_title = xaxis_title_mtop;
    xaxis_unit = xaxis_unit_mtop;

    f_func = new TF1("mtop_"+func_name, mtop_function, fitmin, fitmax, npars_sep);   

    for(int i = 0; i < npars_sep; i++){
      //      if(i != 0 && i != 1)
      f_func->SetParameter(i,pars_init_mtop.at(i));
      f_func->SetParName(i,pars_name_mtop.at(i));
      
      double lower = pars_init_mtop.at(i)*0.5;
      double upper = pars_init_mtop.at(i)*6.5;

      if(i == 0){
	upper = 0.330;
	lower = 0.290;
      }

      if(i == 8){
        upper = 8.8;
        lower = 7.0;
      }

      
      if(i == 1 || i == 4 || i == 7){

	//lower = pars_init_mtop.at(i)*0.97;
	//upper = pars_init_mtop.at(i)*1.03;

	if(i == 7){
	  //          lower = pars_init_mtop.at(i)*0.9999;
	  // upper = pars_init_mtop.at(i)*1.0001;
        }


      } 

      std::cout << "Limits = " << i << "\t" << lower << "\t" << upper << std::endl;

      f_func->SetParLimits(i, lower, upper);

    }
    // MW der Verteilungen
    // f_func->SetParLimits(0,   0.0045, 0.075);
    // f_func->SetParLimits(1,   150.0, 170.0);
    // f_func->SetParLimits(2,   1.5, 5.5);    

    //   f_func->FixParameter(0, 0.005);	
    // f_func->FixParameter(1, 164.0);
    //f_func->FixParameter(4, 157.0);
    // f_func->FixParameter(2, 4.8);
    // f_func->FixParameter(7, 183.25);
  }
  else if(S_hist == "h_mw_orig"){
    xaxis_title = xaxis_title_mw;
    xaxis_unit = xaxis_unit_mw;

    f_func = new TF1("mw_"+func_name, mw_function, fitmin, fitmax, npars_sep);   

    for(int i = 0; i < npars_sep; i++){
      f_func->SetParameter(i,pars_init_mw.at(i));
      f_func->SetParName(i,pars_name_mw.at(i));

      double lower = pars_init_mtop.at(i)*0.15;
      double upper = pars_init_mtop.at(i)*6.5;

      if(i == 0){
        lower = 0.470;
        upper = 0.499;
      }
      

      if(i == 1 || i == 4){

	//	lower = pars_init_mtop.at(i)*0.95;
	//	upper = pars_init_mtop.at(i)*1.05;

      }

      f_func->SetParLimits(i, lower, upper);



    }



  }
  else if(S_hist == "h_rbq_orig"){
    xaxis_title = xaxis_title_rbq;
    xaxis_unit = xaxis_unit_rbq;

    f_func = new TF1("rbq_"+func_name, rbq_function, fitmin, fitmax, npars_sep);   

    for(int i = 0; i < npars_sep; i++){
      f_func->SetParameter(i,pars_init_rbq.at(i));
      f_func->SetParName(i,pars_name_rbq.at(i));

      double lower = pars_init_mtop.at(i)*0.0;
      double upper = pars_init_mtop.at(i)*15.5;

      if(i == 1 || i == 4 || i == 7){

	//        lower = pars_init_mtop.at(i)*0.90;
        // upper = pars_init_mtop.at(i)*1.10;

      }

      f_func->SetParLimits(i, lower, upper);

      

    }

    //    f_func->SetParLimits(0, 0.000, 0.0001);
    f_func->SetParLimits(3, 0.001, 10);

    /*    f_func->SetParLimits(0, 0.0001, 0.01);
    f_func->FixParameter(0, 0.0045);
    f_func->FixParameter(2, 0.57);
    f_func->SetParLimits(3, 0.001, 10);
    // f_func->SetParLimits(4, 1.05, 1.15);
    f_func->FixParameter(5, 0.41);
    f_func->SetParLimits(6, 0.001, 10);
    // f_func->SetParLimits(8, 0.01, 0.3); */
  }
  else if((S_hist == "h_mlb") || 
	  (S_hist == "hist_mlb") || 
	  (S_hist == "hist_klf_window_mlb_reco") ||
	  (S_hist == "hist_klf_original_mlb_reco")){
    xaxis_title = xaxis_title_mlb;
    xaxis_unit = xaxis_unit_mlb;

    //Extra step: dynamic initial parameter values
    TF1* f_help_func = new TF1("f_help_func", gauss, fitmin, fitmax, 3);  
    f_help_func->SetParameters(1,92,21);//Norm of 1.95 when sigma in norm (else 0.037)
    h_hist->Fit(f_help_func,"QBR0");
    double gausnorm  = f_help_func->GetParameter(0);
    double gausmean  = f_help_func->GetParameter(1);
    double gauswidth = f_help_func->GetParameter(2);
    f_help_func->Delete();

    //gaus
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth};
    // vector<TString> pars_name = {"gausnorm","gausmean","gauswidth"};
    //gaus double-width
    // vector<double> pars_init = {gausnorm,gausmean,(gauswidth),(gauswidth)};
    // vector<TString> pars_name = {"gausnorm","gausmean","gauswidthLow","gauswidthHigh"};
    //gaus+landau
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    // 				(5*gausnorm),70,10};
    // vector<TString> pars_name = {"gausnorm","gausmean","gauswidth",
    // 				 "landaunorm","landaumean","landauwidth"};
    //gaus+landau_n
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    // 				(2*gausnorm),120,5};
    // vector<TString> pars_name = {"gausnorm","gausmean","gauswidth",
    // 				 "nlandaunorm","nlandaumean","nlandauwidth"};
    //gaus+gaus *test
    // vector<double> pars_init = {(0.67*gausnorm),(gausmean - 10),(gauswidth - 2.3),
    // 				(0.53*gausnorm),(gausmean + 13),(gauswidth - 4.6)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
    // 				 "gaus2norm","gaus2mean","gaus2width"};
    //gaus+gaus *(same norm)
    // vector<double> pars_init = {(0.5*gausnorm),(gausmean-15),(gauswidth-10),
    // 				(gausmean+15),(gauswidth-10)};
    // vector<TString> pars_name = {"gaus12norm","gaus1mean","gaus1width",
    // 				 "gaus2mean","gaus2width"};
    //gaus+gaus *(same norm and width)
    // vector<double> pars_init = {(0.5*gausnorm),(gausmean-15),(gauswidth-10),
    // 				(gausmean+15)};
    // vector<TString> pars_name = {"gaus12norm","gaus1mean","gaus12width",
    // 				 "gaus2mean"};
    //gaus+gaus *(same norm + 1 fixed width)
    // vector<double> pars_init = {100*(0.5*gausnorm),(gausmean-15),(gauswidth-10),(gausmean+15)};
    // vector<TString> pars_name = {"gaus12norm","gaus1mean","gaus1width","gaus2mean"};
    //gaus+gaus *(same norm + fixed widths)
    // vector<double> pars_init = {100*(0.5*gausnorm),(gausmean-15),(gausmean+15)};
    // vector<TString> pars_name = {"gaus12norm","gaus1mean","gaus2mean"};
    //gaus+gaus *(same norm + fixed widths)
    // vector<double> pars_init = {(gausmean-15),(gausmean+15)};
    // vector<TString> pars_name = {"gaus1mean","gaus2mean"};
    //gaus+gaus *(fixed widths)
    // vector<double> pars_init = {100*(0.5*gausnorm),(gausmean-15),100*(0.5*gausnorm),(gausmean+15)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus2norm","gaus2mean"};
    //gaus+gaus *(1 fixed width)
    // vector<double> pars_init = {100*(0.5*gausnorm),(gausmean-15),(gauswidth-10),
    // 				100*(0.5*gausnorm),(gausmean+15)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
    // 				 "gaus2norm","gaus2mean"};
    //gaus+cosine
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    // 				(0.1*gausnorm),57,113};
    // vector<TString> pars_name = {"gausnorm","gausmean","gauswidth",
    // 				 "cosnorm","cosperiod","cosmaxpoint"};
    //gaus+gaus+landau
    // vector<double> pars_init = {(0.8*gausnorm),(gausmean-10),(gauswidth-10),
    // 				(0.3*gausnorm),(gausmean+10),(gauswidth-10),
    // 				(2*gausnorm),(gausmean-30),(gauswidth-12)}; 
    // vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
    // 				 "gaus2norm","gaus2mean","gaus2width",
    // 				 "landaunorm","landaumean","landauwidth"};
    //gaus+gaus+landau_n
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    // 				(0.05*gausnorm),(gausmean-25),(gauswidth-10),
    // 				(2*gausnorm),(gausmean+25),(gauswidth-12)}; 
    // vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
    // 				 "gaus2norm","gaus2mean","gaus2width",
    // 				 "nlandaunorm","nlandaumean","nlandauwidth"};
    //gaus+landau+landau_n
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    // 				(4.3*gausnorm),(gausmean-25),(gauswidth-10),
    // 				(2.3*gausnorm),(gausmean+25),(gauswidth-12)};
    // vector<TString> pars_name = {"gausnorm","gausmean","gauswidth",
    // 				 "landaunorm","landaumean","landauwidth",
    // 				 "nlandaunorm","nlandaumean","nlandauwidth"};
    //gaus+gaus+gaus
    vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    				(0.05*gausnorm),(gausmean-25),(gauswidth-10),
    				(0.05*gausnorm),(gausmean+25),(gauswidth-12)};
    vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
    				 "gaus2norm","gaus2mean","gaus2width",
    				 "gaus3norm","gaus3mean","gaus3width"};
    //gaus+gaus+gaus *(1 Fixed norm)
    // vector<double> pars_init = {gausmean,gauswidth,
    // 				100*(0.05*gausnorm),(gausmean-25),(gauswidth-10),
    // 				100*(0.05*gausnorm),(gausmean+25),(gauswidth-12)};
    // vector<TString> pars_name = {"gaus1mean","gaus1width",
    // 				 "gaus2norm","gaus2mean","gaus2width",
    // 				 "gaus3norm","gaus3mean","gaus3width"};
    //gaus+gaus+gaus *(Fixed norms)
    // vector<double> pars_init = {gausmean,gauswidth,
    // 				(gausmean-25),(gauswidth-10),
    // 				(gausmean+25),(gauswidth-12)};
    // vector<TString> pars_name = {"gaus1mean","gaus1width",
    // 				 "gaus2norm","gaus2mean","gaus2width",
    // 				 "gaus3norm","gaus3mean","gaus3width"};
    //gaus+gaus+gaus *(Fixed widths)
    // vector<double> pars_init = {gausnorm,gausmean,
    // 				(0.05*gausnorm),(gausmean-25),
    // 				(0.05*gausnorm),(gausmean+25)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean",
    // 				 "gaus2norm","gaus2mean",
    // 				 "gaus3norm","gaus3mean"};
    //gaus+gaus+gaus *(Fixed widths and 1 Norm)
    // vector<double> pars_init = {100*gausnorm,gausmean,
    // 				100*(0.05*gausnorm),(gausmean-25),
    // 				(gausmean+25)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean",
    // 				 "gaus2norm","gaus2mean",
    // 				 "gaus3mean"};
    //gaus+gaus+gaus *(Fixed widths and 2 Norm)
    // vector<double> pars_init = {100*gausnorm,gausmean,
    // 				(gausmean-25),
    // 				(gausmean+25)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean",
    // 				 "gaus2mean",
    // 				 "gaus3mean"};
    //gaus+gaus+gaus *(Fixed widths and Norms)
    // vector<double> pars_init = {gausmean,
    // 				(gausmean-25),
    // 				(gausmean+25)};
    // vector<TString> pars_name = {"gaus1mean",
    // 				 "gaus2mean",
    // 				 "gaus3mean"};
    //gaus+gaus+gaus *(same norm&width for small gaussians)
    // vector<double> pars_init = {gausnorm,gausmean,gauswidth,
    // 				(0.05*gausnorm),(gausmean-30),(gauswidth-10),
    // 				(gausmean+25)};
    // vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
    // 				 "gaus23norm","gaus2mean","gaus23width",
    // 				 "gaus3mean"};

    f_func = new TF1("mlb_"+func_name, mlb_function, fitmin, fitmax, npars_sep);   

    for(int i = 0; i < npars_sep; i++){
      f_func->SetParameter(i,pars_init.at(i));
      f_func->SetParName(i,pars_name.at(i));
    }
  }
  else if(S_hist == "hist_rbq_DL"){
    xaxis_title = xaxis_title_rbq_DL;
    xaxis_unit = xaxis_unit_rbq_DL;

    //Extra step: dynamic initial parameter values
    TF1* f_help_func = new TF1("f_help_func", gauss, fitmin, fitmax, 3);  
    f_help_func->SetParameters(0.037,1,1);
    h_hist->Fit(f_help_func,"QBR0");
    double gausnorm  = f_help_func->GetParameter(0);
    double gausmean  = f_help_func->GetParameter(1);
    double gauswidth = f_help_func->GetParameter(2);
    f_help_func->Delete();

    vector<double> pars_init = {gausnorm,gausmean,gauswidth,
				(0.05*gausnorm),(gausmean-0.3),(1.5*gauswidth),
				(0.1*gausnorm),(gausmean+0.3),(1.5*gauswidth)};
    vector<TString> pars_name = {"gaus1norm","gaus1mean","gaus1width",
				 "gaus2norm","gaus2mean","gaus2width",
				 "landau1norm","landau1mean","landau1width"};

    f_func = new TF1("rbq_DL_"+func_name, rbq_DL_function, fitmin, fitmax, npars_sep);   

    for(int i = 0; i < npars_sep; i++){
      f_func->SetParameter(i,pars_init.at(i));
      f_func->SetParName(i,pars_name.at(i));
    }
  }
  else{
    cout << "Invalid histogram name!" << endl;
    return nullptr;
  }

  // //Perform fit to histogram
  // int fitStatus = h_hist->Fit(f_func,"BRL");
  // if(fitStatus != 0){
  //   cout << "Error in fitting separate histograms!!!" << endl;
  //   return nullptr;
  // }
  //Setup minimizer
  TMinuitMinimizer* myMinuit;
  //Options for algorithm: Migrad (default),Simplex,Combined,Scan
  myMinuit = new TMinuitMinimizer("",npars_sep);
  vector<double> v1,v2,v3;
  vector<TH1D> v_hists; v_hists.push_back(*h_hist);
  FCN *Mf1 = new FCN(f_func, v_hists, v1, v2, v3, category);

  ROOT::Math::Functor myFunctor(Mf1, &FCN::FCN_chi2sep, npars_sep);

  // ROOT::Math::Functor myFunctor(Mf1, &FCN::FCN_chi2, npars_sep); 

  myMinuit -> SetFunction(myFunctor);
  //Set options
  myMinuit->SetMaxFunctionCalls(1000000); 
  myMinuit->SetMaxIterations(10000);
  //  myMinuit->SetTolerance(0.001);
  myMinuit->SetPrintLevel(1);

  for(int k = 0; k < npars_sep; k++){
    myMinuit->SetVariable(k,Form("par%i",k),f_func->GetParameter(k),0.01);

    Double_t upper = 0.0;
    Double_t lower = 0.0;
    f_func->GetParLimits(k, upper, lower);
    myMinuit->SetVariableLimits(k, upper, lower);

    // myMinuit -> FixVariable(0);                                                                                                                                                                    
    // myMinuit -> FixVariable(1);   
    // myMinuit -> FixVariable(2);

  }
  //myMinuit->SetVariableLimits(1,0,92);
  //myMinuit->SetVariableLimits(3,92,180);
  //Do the minimization
  bool minStatus = myMinuit->Minimize();
  if(!minStatus){
    cout << "Error in Minuit minimization of separate fit!!!" << endl;
    exit(1);
    return nullptr;
  }
  bool hesseStatus = myMinuit->Hesse();
  if(!hesseStatus){
    cout << "Error in Hesse calculation of separate fit!!!" << endl;
    exit(1);
    return nullptr;
  }
  
  bool minStatus2 = myMinuit->Minimize();
  if(!minStatus2){
    cout << "Error in 2nd Minuit minimization of separate fit!!!" << endl;
    exit(1);
    return nullptr;
  }

  //Save result of minimization
  const double *result_par = myMinuit->X();
  const double *result_par_error = myMinuit->Errors();
  double result_min = myMinuit->MinValue();
  int result_ndim = myMinuit->NFree();
  //Get the correlation matrix
  cout << endl << "Correlation Matrix:" << endl;
  for(int i = 0; i < npars_sep; i++){
    for(int j = 0; j < npars_sep; j++){
      double cor_ij = myMinuit->CovMatrix(i,j)/(result_par_error[i]*result_par_error[j]);
      cout << Form("%+5.5f ", cor_ij) << "  ";
    }
    cout << endl;
  }

  //Get NDF from: (total # of fitted histogram bins) - (# of free parameters in the fit)
  int nbinsfit = 0;
  for (int bin_idx = 1; bin_idx <= h_hist->GetNbinsX(); bin_idx++){
    double bincenter = h_hist->GetBinCenter(bin_idx);
    if((bincenter < fitmin) || (bincenter > fitmax))
      continue;
    nbinsfit++;
  }
  int total_ndf = nbinsfit - result_ndim;

  //Set parameters in f_func
  f_func->SetParameters(result_par);
  f_func->SetParErrors(result_par_error);
  
  double *func_pars = (double*)f_func->GetParameters();
  vector<TF1*> v_subfuncs;
  v_subfuncs = GetSubFuncs(func_pars, category);

  FitInfo fInfo;
  fInfo.InputHisto = h_hist;
  fInfo.SubFunctions = v_subfuncs;
  fInfo.SumFunctions = f_func;
  fInfo.Chi2 = result_min;
  fInfo.NDF = total_ndf;
  fInfo.OutputFile = out_dir + f_func->GetName();
  fInfo.xAxis_Title = xaxis_title;
  fInfo.xAxis_Unit = xaxis_unit;

  MakePlots* myMakePlots = new MakePlots();
  myMakePlots->FitPlots(fInfo);

  return f_func;
}

