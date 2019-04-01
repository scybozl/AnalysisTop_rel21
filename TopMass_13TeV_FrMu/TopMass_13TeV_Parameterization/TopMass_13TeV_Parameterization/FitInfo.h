#ifndef FITINFO_H
#define FITINFO_H

#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1D.h"
#include "TString.h"
#include <vector>
#include <string>

using namespace std;

struct FitInfo{
  vector<TF1*> SubFunctions;
  vector<TString> SubFunctionNames;
  TF1* SumFunctions;
  double Chi2;
  int NDF;
  TH1D* InputHisto;
  TString OutputFile;
  TString xAxis_Title;
  TString xAxis_Unit;
};

//Universal values
const double PI  = 3.141592653589793238463;

//mtop values
extern double fitmin_mtop; 
extern double fitmax_mtop; 
extern int npars_sep_mtop; 
extern int npars_comb_mtop; 
extern TString xaxis_title_mtop; 
extern TString xaxis_unit_mtop; 
extern vector<TString> v_mtop_subFunctionNames; 
extern vector<TString> v_mtop_subFunctionTypes;
extern vector<double> pars_init_mtop;
extern vector<TString> pars_name_mtop;

//mw values
extern double fitmin_mw; 
extern double fitmax_mw; 
extern int npars_sep_mw; 
extern int npars_comb_mw;
extern TString xaxis_title_mw; 
extern TString xaxis_unit_mw; 
extern vector<TString> v_mw_subFunctionNames;
extern vector<TString> v_mw_subFunctionTypes;
extern vector<double> pars_init_mw; 
extern vector<TString> pars_name_mw;
  
//rbq values
extern double fitmin_rbq; 
extern double fitmax_rbq; 
extern int npars_sep_rbq; 
extern int npars_comb_rbq; 
extern TString xaxis_title_rbq; 
extern TString xaxis_unit_rbq; 
extern vector<TString> v_rbq_subFunctionNames;
extern vector<TString> v_rbq_subFunctionTypes;
extern vector<double> pars_init_rbq; 
extern vector<TString> pars_name_rbq;
 
//mlb values                   //Range   L,  M,  S, XS
extern double fitmin_mlb; // = 40.0;//GeV    30, 30, 34, 40   GaussCore 68
extern double fitmax_mlb; // = 148.0;//GeV  170,156,150,148  GaussCore 122
extern int npars_sep_mlb; // = 9;
extern int npars_comb_mlb; // = (npars_sep_mlb * 2);//mtop,(change to 3 for bJSF) dependence
extern TString xaxis_title_mlb; // = "m_{lb}";
extern TString xaxis_unit_mlb; // = "GeV";
  
//rbq_DL values
extern double fitmin_rbq_DL; // = 0.3;
extern double fitmax_rbq_DL; // = 3.0;
extern int npars_sep_rbq_DL; // = 9;
extern int npars_comb_rbq_DL; // = (npars_sep_rbq_DL * 3);//mtop,bJSF dependence
extern TString xaxis_title_rbq_DL; // = "R_{bq}^{reco}";
extern TString xaxis_unit_rbq_DL; // = "";

extern vector<TF1*> v_mtop_subFunctions;
extern vector<TF1*> v_mw_subFunctions;
extern vector<TF1*> v_rbq_subFunctions;

Double_t gauss(Double_t* x, Double_t* par);
Double_t landau(Double_t* x,  Double_t* par);
Double_t landau_n(Double_t* x,  Double_t* par);
Double_t cosine(Double_t* x, Double_t* par);
Double_t cryball(Double_t* x, Double_t* par);

Double_t linpar_function_mtop(Double_t* x, Double_t* par);
Double_t linpar_function_SF(Double_t* x, Double_t* par);

Double_t mtop_function(Double_t* x, Double_t* par);
Double_t mw_function(Double_t* x, Double_t* par);
Double_t rbq_function(Double_t* x, Double_t* par);
Double_t mlb_function(Double_t* x, Double_t* par);
Double_t rbq_DL_function(Double_t* x, Double_t* par);

vector<TF1*> GetSubFuncs(const Double_t* input_pars, TString category);
void ConvertPars(const Double_t* input_pars, Double_t* output_pars, const int npar_out, TString category, double mtop, double JSF, double bJSF);

TH1D* FitPull(TF1* f, TH1D* h);
TH1D* FitRatio(TF1* f, TH1D* h);

//};



#endif
