#include "TopMass_13TeV_Parameterization/MakePlots.h" 
#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions
#include "TopMass_13TeV_Parameterization/AtlasStyle.h" 

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
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <stdio.h>

using namespace std;


MakePlots::MakePlots(){}
MakePlots::~MakePlots(){}

//void MakePlots::LinearPlots(FitInfo fInfo){
//}
void MakePlots::FitPlots(FitInfo fInfo){

  //Unpack FitInfo
  TH1D* h_hist = (TH1D*) fInfo.InputHisto;
  vector<TF1*> v_subfuncs = (vector<TF1*>) fInfo.SubFunctions;
  TF1* f_func = (TF1*) fInfo.SumFunctions;
  double chi2 = fInfo.Chi2;
  int ndf = fInfo.NDF;
  TString output_FileName = (TString) fInfo.OutputFile;
  TString xaxis_title = (TString) fInfo.xAxis_Title;
  TString xaxis_unit = (TString) fInfo.xAxis_Unit;

  //Draw fitted histogram
  ////////////////////////////////////////////////////////////////////
  SetAtlasStyle();
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  double tsize = gStyle->GetLabelSize("X");

  h_hist->UseCurrentStyle();

  //Set colors for subfunctions
  vector<int> mycolors;
  mycolors.push_back(601);//kBlue+1
  mycolors.push_back(617);//kMagenta+1
  mycolors.push_back(417);//kGreen+1
  mycolors.push_back(433);//kCyan+1
  if(v_subfuncs.size() > mycolors.size()){
    cout << "Not enough colors for the number of subfunctions" << endl;
    return;
  }

  TCanvas *myCanvas = new TCanvas("myCanvas","myCanvas", 800, 800);
  myCanvas->cd();
  
  double padsize=0.30;
  TPad *pad1 = new TPad("pad1","pad1",0.,padsize,1.,1.);
  pad1->SetBottomMargin(0.02); 
  pad1->SetLeftMargin(0.12);
  pad1->SetRightMargin(0.06);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  TPad *pad2 = new TPad("pad2","pad2",0.,0.04,1.,padsize);
  pad2->SetBottomMargin(0.325);
  pad2->SetLeftMargin(0.12);
  pad2->SetRightMargin(0.06);

  //pad2->SetGridx(); // vertical grid
  pad2->SetGridy();
  pad2->Draw();

  pad1->cd();               // pad1 becomes the current pad
  
  h_hist->SetMaximum(1.3*h_hist->GetMaximum());
  h_hist->SetMinimum(0);
  //h_hist->GetYaxis()->SetTitle(Form("Normalised events / %2.1f GeV", h_hist->GetBinWidth(1))); 
  h_hist->GetYaxis()->SetTitle(Form("Events / %2.2f ", h_hist->GetBinWidth(1)) + xaxis_unit); 
  h_hist->GetYaxis()->SetTitleFont(43);
  h_hist->GetYaxis()->SetLabelFont(43);
  h_hist->GetYaxis()->SetTitleSize(28);
  h_hist->GetYaxis()->SetLabelSize(22);
  h_hist->GetXaxis()->SetLabelSize(0);
  h_hist->GetYaxis()->SetTitleOffset(1.6);

  //h_hist->SetLabelOffset(0.3,"X");
  //h_hist->SetTitleOffset(0.95,"Y");
  
  //Line and marker formatting   
  f_func->SetLineColor(2);
  f_func->SetLineWidth(3);
  h_hist->SetLineWidth(3);
  h_hist->SetMarkerSize(0.8);

  h_hist->Draw("same");
  f_func->Draw("same");
  
  //Write chi^2 if applicable
  ////////////////////////////////////////////////////////////////////
  double Prob = TMath::Prob(chi2,ndf);
  double COM = chi2/ndf;
  
  stringstream oss_chi2; oss_chi2 << setprecision(3) << chi2;
  stringstream oss_ndf; oss_ndf << ndf;
  stringstream oss_Prob; oss_Prob << setprecision(3) << Prob;
  stringstream oss_COM; oss_COM << setprecision(3) << COM;
  
  TLatex l04;
  l04.SetTextAlign(9);
  l04.SetTextSize(0.048);
  l04.SetLineWidth(2);
  l04.SetNDC();
  l04.DrawLatex(0.19,0.81, ("#chi^{2}/ndf = "+ oss_chi2.str() + "/" +oss_ndf.str() + " = " + oss_COM.str()).c_str());
  l04.DrawLatex(0.19,0.755, ("P(#chi^{2},ndf) = " + oss_Prob.str()).c_str());

  //ATLAS label
  ////////////////////////////////////////////////////////////////////    
  TLatex l05;
  l05.SetTextAlign(9);
  l05.SetTextSize(0.05);
  l05.SetLineWidth(2);
  l05.SetNDC();
  l05.SetTextFont(72);
  l05.DrawLatex(0.19, 0.875, "ATLAS");
  l05.SetTextFont(42);
  l05.DrawLatex(0.32, 0.875, "Internal");
  ////////////////////////////////////////////////////////////////////
  
  //Legend
  ////////////////////////////////////////////////////////////////////    
  TLegend *leg = new TLegend(0.7078059,0.6690754,0.8987342,0.8986966); //,NULL, ""); //"brNDC");
  leg->SetLineColor(kNone);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(tsize);
  leg->AddEntry(h_hist,"Simulation","lep");
  leg->AddEntry(f_func,"Fit","l");
  //Loop for adding subfunctions
  for(unsigned int i = 0; i < v_subfuncs.size(); i++){
    v_subfuncs.at(i)->SetLineColor(mycolors.at(i));
    v_subfuncs.at(i)->SetLineWidth(2);
    v_subfuncs.at(i)->Draw("same");
    leg->AddEntry(v_subfuncs.at(i),v_subfuncs.at(i)->GetName(),"l");
  }

  leg->Draw("same");
  
  
  //Draw the pull(or switch to ratio) between Fitfunction and Histogramm
  ////////////////////////////////////////////////////////////////////
  pad2->cd();    // pad2 becomes the current pad  
  
  TH1D* h_ratio = (TH1D*) FitPull(f_func,h_hist);
  //TH1D* h_ratio = (TH1D*) FitRatio(f_func,h_hist);
  
  if(xaxis_unit == "")
    h_ratio->GetXaxis()->SetTitle(xaxis_title);
  else
    h_ratio->GetXaxis()->SetTitle(xaxis_title + " [" + xaxis_unit + "]");

  /*h_ratio->SetLabelSize(0.14, "X");
  h_ratio->SetLabelOffset(0.05,"X");
  h_ratio->SetTitleOffset(1.2,"X");
  h_ratio->SetTitleSize(0.17, "X");

  h_ratio->SetLabelSize(0.10, "Y");
  h_ratio->SetTitleOffset(0.4,"Y");
  h_ratio->SetTitleSize(0.15, "Y");
  h_ratio->SetNdivisions(305,"Y");*/

  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetLabelFont(43);
  h_ratio->GetYaxis()->SetTitleSize(28);
  h_ratio->GetYaxis()->SetLabelSize(23);
  h_ratio->GetYaxis()->SetTitleOffset(1.6);

  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetLabelFont(43);
  h_ratio->GetXaxis()->SetTitleSize(28);
  h_ratio->GetXaxis()->SetLabelSize(24);
  h_ratio->GetXaxis()->SetTitleOffset(4.0);

  h_ratio->SetLineWidth(3);    
    
  h_ratio->Draw("hist");

  TLine* tline_0 = new TLine(f_func->GetXmin(),0,f_func->GetXmax(),0);
  tline_0->SetLineColor(1);
  tline_0->SetLineStyle(1);
  tline_0->SetLineWidth(2);
  tline_0->Draw("SAME");

  h_ratio->Draw("hist same");
  

  //Save fitted histogram
  myCanvas->Print(output_FileName + ".pdf");


  //Delete pointers
  tline_0->Delete();
  h_ratio->Delete();
  leg->Delete();
  pad1->Delete();
  pad2->Delete();
  myCanvas->Close();

  return;
}



