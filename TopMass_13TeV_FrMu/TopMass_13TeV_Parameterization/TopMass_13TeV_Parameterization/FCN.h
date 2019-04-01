#ifndef FCN_H_
#define FCN_H_


#include "TSystem.h"
#include "TFile.h"
#include "TF1.h"
#include "TTree.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TPad.h"
#include "TMath.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMinuit.h"
#include "TMinuitMinimizer.h"
#include "TAttMarker.h"
#include "Math/Functor.h"
#include "Math/Functor.h"

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

//#include "PlotFactory_13TeV/TemplateHolder.h"
//#include "PlotFactory_13TeV/TemplateHolderbg.h"
using namespace std;


class FCN
{


 public:
  // std::vector<TemplateHolder*> gALL;
  // std::vector<TemplateHolderbg*> gBackground;
  
  FCN(TF1*, std::vector<TH1D>, std::vector<double>, std::vector<double>, std::vector<double>, TString);
  ~FCN();

  Double_t FCN_chi2(const Double_t* par);
  Double_t FCN_chi2sep(const Double_t* par);
   
 private:
  
  TF1 * f_func;
  std::vector<TH1D>   f_hists;
  std::vector<double> f_vals_mtop;
  std::vector<double> f_vals_jsf;
  std::vector<double> f_vals_bjsf;
  TString f_category;

  /*  //Fit functions
  //Gauss

    double big_ftop_fcn(const Double_t *par) const;

    double big_fw_fcn(const Double_t *par) const;

    double big_frbq_fcn(const Double_t *par) const;

//void big_all_fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag){
    double big_all_fcn(const Double_t *par) const;


    double big_ftop_fcnbg(const Double_t *par) const;

    double big_fw_fcnbg(const Double_t *par) const;

    double big_frbq_fcnbg(const Double_t *par) const;

//void big_all_fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag){
    double big_all_fcnbg(const Double_t *par) const;


  */


};


#endif
