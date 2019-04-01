#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions

#include "TMinuitMinimizer.h"
#include "TMatrixD.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TH2D.h"
#include "TSystem.h"
#include "TMath.h"
#include "Math/Functor.h"

#include "TROOT.h"
#include "TMath.h"
#include "TF1.h"
#include "TH1D.h"
#include <vector>
#include <string>

using namespace std;

// mtop values
double fitmin_mtop = 130.0;                                                                                                                                                                      
double fitmax_mtop = 200.0;                                                                                                                                                                      
int npars_sep_mtop = 9;                                                                                                                                                                          
int npars_comb_mtop = (npars_sep_mtop * 4);
TString xaxis_title_mtop = "m_{top}^{reco}";                                                                                                                                                     
TString xaxis_unit_mtop  = "GeV";             
vector<TString> v_mtop_subFunctionNames = {}; 
vector<TString> v_mtop_subFunctionTypes = {};
vector<double> pars_init_mtop  = {};
vector<TString> pars_name_mtop = {}; 

//mw values                                                                                                                                                                                               
double fitmin_mw = 55.0;                                                                                                                                                                         
double fitmax_mw = 110.0;                                                                                                                                                                        
int npars_sep_mw = 6;                                                                                                                                                                            
int npars_comb_mw = 12; //JSF dependence                                                                                                                                          
TString xaxis_title_mw = "m_{W}^{reco}";                                                                                                                                                         
TString xaxis_unit_mw  = "GeV";                                                                                                                                                                   
vector<TString> v_mw_subFunctionNames = {};
vector<TString> v_mw_subFunctionTypes = {};
vector<double> pars_init_mw  = {}; 
vector<TString> pars_name_mw = {}; 

//rbq values                                                                                                                                                                                         
double fitmin_rbq  = 0.5;                                                                                                                                                                         
double fitmax_rbq  = 3.0;                                                                                                                                                                         
int npars_sep_rbq  = 6;                                                                                                                                                                     
int npars_comb_rbq = (npars_sep_rbq * 4);
TString xaxis_title_rbq = "R_{bq}^{reco}";                                                                                                                                                       
TString xaxis_unit_rbq  = ""; 
vector<TString> v_rbq_subFunctionNames = {}; 
vector<TString> v_rbq_subFunctionTypes = {};                                                                                                                                                             
vector<double> pars_init_rbq  = {}; 
vector<TString> pars_name_rbq = {} ;


//mlb values                   //Range   L,  M,  S, XS                                                                                                                                                    
double fitmin_mlb  = 40.0; //GeV    30, 30, 34, 40   GaussCore 68                                                                                                                                  
double fitmax_mlb  = 148.0; //GeV  170,156,150,148  GaussCore 122                                                                                                                                  
int npars_sep_mlb  = 9;                                                                                                                                                                           
int npars_comb_mlb = (npars_sep_mlb * 2); //mtop,(change to 3 for bJSF) dependence                                                                                                                
TString xaxis_title_mlb = "m_{lb}";                                                                                                                                                              
TString xaxis_unit_mlb  = "GeV";                                                                                                                                                                  

//rbq_DL values                                                                                                                                                                                         
double fitmin_rbq_DL  = 0.3;                                                                                                                                                                      
double fitmax_rbq_DL  = 3.0;                                                                                                                                                                      
int npars_sep_rbq_DL  = 9;                                                                                                                                                                        
int npars_comb_rbq_DL = (npars_sep_rbq_DL * 3); //mtop,bJSF dependence                                                                                                                            
TString xaxis_title_rbq_DL  = "R_{bq}^{reco}";                                                                                                                                                    
TString xaxis_unit_rbq_DL   = ""; 



//////////////////////////////////////////////////////////
//Base functions
Double_t gauss(Double_t* x, Double_t* par) { // 3 par
  // par[0] ~ normalization, par[1] ~ mean, par[2] width
  //return par[0] * TMath::Gaus( x[0], par[1], par[2] );
  //return par[0]*exp(-0.5*pow((x[0]-par[1])/par[2],2));
  return (par[0]/sqrt(2*PI*pow(par[2],2)))*TMath::Gaus( x[0], par[1], par[2] );
}
Double_t landau(Double_t* x,  Double_t* par) { // 3 par
  // par[0] ~ normalization, par[1] ~ mean, par[2] broadness
  return par[0]*(TMath::Landau(x[0], par[1], par[2])/par[2]);
}
Double_t landau_n(Double_t* x,  Double_t* par) { // 3 par
  return par[0]*(TMath::Landau(2*par[1]-x[0], par[1], par[2])/par[2]);
}
Double_t cosine(Double_t* x, Double_t* par) { // 2 par
  // par[0] ~ normalization, par[1] ~ period, par[2] ~ max-point
  return par[0] * cos(2*PI*(x[0] - par[2])/par[1]);
}
Double_t cryball(Double_t *z, Double_t *par){ // 5 par      
  // Crystal Ball function
  // Gaussian: N = normalisation, m = mean, s = sigma
  // Tail:     a = boundary in sigma between gaussian and tail, n = relative hight of tail
  double x = -z[0];
  double N = par[0];
  double m = -par[1];
  double s = par[2];
  double a = par[3];
  double n = par[4];

  double A = pow(n/fabs(a),n)*exp(-pow(a,2)/2);
  double B = n/fabs(a)-fabs(a);

  double result = 0;
  if ((x-m)/s > -a) result = N*exp(-pow(x-m,2)/(2*pow(s,2)));
  else              result = N*A*pow(B-(x-m)/s,-n);
				   
  return result;
}
Double_t gauss2w(Double_t* x, Double_t* par) { // 4 par
  // par[0] ~ normalization, par[1] ~ mean, par[2] widthLow, par[3] widthHigh
  double result = 0;
  // if(x[0] < par[1]) result = (par[0]/sqrt(2*PI*pow(par[2],2)))*TMath::Gaus( x[0], par[1], par[2] );
  // else              result = (par[0]/sqrt(2*PI*pow(par[3],2)))*TMath::Gaus( x[0], par[1], par[3] );
  if(x[0] < par[1]) result = par[0]*TMath::Gaus( x[0], par[1], par[2] );
  else              result = par[0]*TMath::Gaus( x[0], par[1], par[3] );
  return result;
}
////////////////////////////////////////////////////////////////////
//3xGauss tests
Double_t mlb_3xGauss_SameWidthAndNorm(Double_t* x, Double_t* par) {
  return par[0] * TMath::Gaus(x[0], par[1], par[2]) + 
         par[3] * TMath::Gaus(x[0], par[4], par[5]) + 
         par[3] * TMath::Gaus(x[0], par[6], par[5]);
}
Double_t mlb_3xGauss_Fix1Norm(Double_t* x, Double_t* par) {
  return 0.01*3.53 * TMath::Gaus(x[0], par[0], par[1]) + 
         0.01*par[2] * TMath::Gaus(x[0], par[3], par[4]) + 
         0.01*par[5] * TMath::Gaus(x[0], par[6], par[7]);
}
Double_t mlb_3xGauss_FixNorms(Double_t* x, Double_t* par) {
  return 0.01*3.53 * TMath::Gaus(x[0], par[0], par[1]) + 
         0.01*0.45 * TMath::Gaus(x[0], par[2], par[3]) + 
         0.01*0.25 * TMath::Gaus(x[0], par[4], par[5]);
}
Double_t mlb_3xGauss_FixWidths(Double_t* x, Double_t* par) {
  // return 0.01*par[0] * TMath::Gaus(x[0], par[1], 19.7) + 
  //        0.01*par[2] * TMath::Gaus(x[0], par[3], 15.3) + 
  //        0.01*par[4] * TMath::Gaus(x[0], par[5], 11.2);
  double sigma1 = 19.8;
  double sigma2 = 15.5;
  double sigma3 = 11.5;
  return (par[0]/sqrt(2*PI*pow(sigma1,2)))*TMath::Gaus(x[0],par[1],sigma1) +
         (par[2]/sqrt(2*PI*pow(sigma2,2)))*TMath::Gaus(x[0],par[3],sigma2) +
         (par[4]/sqrt(2*PI*pow(sigma3,2)))*TMath::Gaus(x[0],par[5],sigma3);

  // double *parset1 = new double[3];
  // double *parset2 = new double[3];
  // double *parset3 = new double[3];
  // parset1[0] = par[0]; parset1[1] = par[1]; parset1[2] = 19.8;
  // parset2[0] = par[2]; parset2[1] = par[3]; parset2[2] = 15.5;
  // parset3[0] = par[4]; parset3[1] = par[5]; parset3[2] = 11.5;
  // return gauss(x,&parset1[0]) + gauss(x,&parset2[0]) + gauss(x,&parset3[0]);
}
Double_t mlb_3xGauss_Fix1NormFixWidths(Double_t* x, Double_t* par) {
  return 0.01*par[0] * TMath::Gaus(x[0], par[1], 19.7) + 
         0.01*par[2] * TMath::Gaus(x[0], par[3], 15.3) + 
         0.01*0.215 * TMath::Gaus(x[0], par[4], 11.2);
}
Double_t mlb_3xGauss_Fix2NormFixWidths(Double_t* x, Double_t* par) {
  return 0.01*par[0] * TMath::Gaus(x[0], par[1], 19.7) + 
         0.01*0.555 * TMath::Gaus(x[0], par[2], 15.3) + 
         0.01*0.215 * TMath::Gaus(x[0], par[3], 11.2);
}
Double_t mlb_3xGauss_FixNormsFixWidths(Double_t* x, Double_t* par) {
  return 0.01*3.53 * TMath::Gaus(x[0], par[0], 19.7) + 
         0.01*0.555 * TMath::Gaus(x[0], par[1], 15.3) + 
         0.01*0.215 * TMath::Gaus(x[0], par[2], 11.2);
}
////////////////////////////////////////////////////////////////////
//2xGauss tests
Double_t mlb_2xGauss(Double_t* x, Double_t* par) {
  return gauss(x,&par[0]) + gauss(x,&par[3]);
}
Double_t mlb_2xGauss_SameMean(Double_t* x, Double_t* par) {
  double *par2set = new double[3];
  par2set[0] = par[3]; par2set[1] = par[1]; par2set[2] = par[4];
  return gauss(x,&par[0]) + gauss(x,&par2set[0]);
}
Double_t mlb_2xGauss_SameWidth(Double_t* x, Double_t* par) {
  double *par2set = new double[3];
  par2set[0] = par[3]; par2set[1] = par[4]; par2set[2] = par[2];
  return gauss(x,&par[0]) + gauss(x,&par2set[0]);
}
Double_t mlb_2xGauss_SameNorm(Double_t* x, Double_t* par) {
  double *par2set = new double[3];
  par2set[0] = par[0]; par2set[1] = par[3]; par2set[2] = par[4];
  return gauss(x,&par[0]) + gauss(x,&par2set[0]);
}
Double_t mlb_2xGauss_SameNormSameWidth(Double_t* x, Double_t* par) {
  double *par2set = new double[3];
  par2set[0] = par[0]; par2set[1] = par[3]; par2set[2] = par[2];
  return gauss(x,&par[0]) + gauss(x,&par2set[0]);
}
Double_t mlb_2xGauss_SameNormFix1Width(Double_t* x, Double_t* par) {
  return 0.01*par[0] * TMath::Gaus(x[0], par[1], par[2]) + 
         0.01*par[0] * TMath::Gaus(x[0], par[3], 17.2);
}
Double_t mlb_2xGauss_SameNormFixWidths(Double_t* x, Double_t* par) {
  return 0.01*par[0] * TMath::Gaus(x[0], par[1], 18.6) + 
         0.01*par[0] * TMath::Gaus(x[0], par[2], 17.2);
}
Double_t mlb_2xGauss_FixWidths(Double_t* x, Double_t* par) {
  return 0.01*par[0] * TMath::Gaus(x[0], par[1], 18.6) + 
         0.01*par[2] * TMath::Gaus(x[0], par[3], 17.2);
}
Double_t mlb_2xGauss_Fix1Width(Double_t* x, Double_t* par) {
  // return 0.01*par[0] * TMath::Gaus(x[0], par[1], par[2]) + 
  //        0.01*par[3] * TMath::Gaus(x[0], par[4], 17.2);
  double *par2set = new double[3];
  par2set[0] = par[3]; par2set[1] = par[4]; par2set[2] = 17.1;
  return gauss(x,&par[0]) + gauss(x,&par2set[0]);
}
Double_t mlb_2xGauss_FixNormsFixWidths(Double_t* x, Double_t* par) {
  return 0.01*2.25 * TMath::Gaus(x[0], par[0], 18.6) + 
         0.01*2.25 * TMath::Gaus(x[0], par[1], 17.2);
}


//////////////////////////////////////////////////////////
//Linear fit functions
Double_t linpar_function_mtop(Double_t* x, Double_t* par) {
  return par[0] + par[1]*(x[0] - 172.5);
}
Double_t linpar_function_SF(Double_t* x, Double_t* par) {
  return par[0] + par[1]*(x[0] - 1.00);
}


//////////////////////////////////////////////////////////
//Fit sub-functions
vector<TF1*> v_mtop_subFunctions = {};
vector<TF1*> v_mw_subFunctions   = {};
vector<TF1*> v_rbq_subFunctions  = {}; 

// new TF1("rbq_gauss2", gauss, fitmin_rbq, fitmax_rbq, 3),
//				   new TF1("rbq_landau", landau, fitmin_rbq, fitmax_rbq, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss", gauss, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("gauss2w", gauss2w, fitmin_mlb, fitmax_mlb, 4)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_landau", landau, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_landau_n", landau_n, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss1", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_gauss2", gauss, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_cosine", cosine, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss1", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_gauss2", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_landau", landau, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss1", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_gauss2", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_landau_n", landau_n, fitmin_mlb, fitmax_mlb, 3)};
// vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss", gauss, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_landau", landau, fitmin_mlb, fitmax_mlb, 3),
// 				   new TF1("mlb_landau_n", landau_n, fitmin_mlb, fitmax_mlb, 3)};
vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_gauss1", gauss, fitmin_mlb, fitmax_mlb, 3),
 				   new TF1("mlb_gauss2", gauss, fitmin_mlb, fitmax_mlb, 3),
 				   new TF1("mlb_gauss3", gauss, fitmin_mlb, fitmax_mlb, 3)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_SameWidthAndNorm", mlb_3xGauss_SameWidthAndNorm, fitmin_mlb, fitmax_mlb, 7)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_Fix1Norm", mlb_3xGauss_Fix1Norm, fitmin_mlb, fitmax_mlb, 8)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_FixNorms", mlb_3xGauss_FixNorms, fitmin_mlb, fitmax_mlb, 6)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_FixWidths", mlb_3xGauss_FixWidths, fitmin_mlb, fitmax_mlb, 6)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_Fix1NormFixWidths", mlb_3xGauss_Fix1NormFixWidths, fitmin_mlb, fitmax_mlb, 5)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_Fix2NormFixWidths", mlb_3xGauss_Fix2NormFixWidths, fitmin_mlb, fitmax_mlb, 4)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_3xGauss_FixNormsFixWidths", mlb_3xGauss_FixNormsFixWidths, fitmin_mlb, fitmax_mlb, 3)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_FixNormsFixWidths", mlb_2xGauss_FixNormsFixWidths, fitmin_mlb, fitmax_mlb, 2)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_SameNormFixWidths", mlb_2xGauss_SameNormFixWidths, fitmin_mlb, fitmax_mlb, 3)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_SameNormFix1Width", mlb_2xGauss_SameNormFix1Width, fitmin_mlb, fitmax_mlb, 4)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_SameNormSameWidth", mlb_2xGauss_SameNormSameWidth, fitmin_mlb, fitmax_mlb, 4)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_SameNorm", mlb_2xGauss_SameNorm, fitmin_mlb, fitmax_mlb, 5)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_FixWidths", mlb_2xGauss_FixWidths, fitmin_mlb, fitmax_mlb, 4)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss_Fix1Width", mlb_2xGauss_Fix1Width, fitmin_mlb, fitmax_mlb, 5)};
//vector<TF1*> v_mlb_subFunctions = {new TF1("mlb_2xGauss", mlb_2xGauss, fitmin_mlb, fitmax_mlb, 6)};
vector<TF1*> v_rbq_DL_subFunctions = {new TF1("rbq_DL_gauss1", gauss, fitmin_rbq_DL, fitmax_rbq_DL, 3),
				      new TF1("rbq_DL_gauss2", gauss, fitmin_rbq_DL, fitmax_rbq_DL, 3),
				      new TF1("rbq_DL_landau", landau, fitmin_rbq_DL, fitmax_rbq_DL, 3)};

//////////////////////////////////////////////////////////
//Fit functions
Double_t mtop_function(Double_t* x, Double_t* par) {
  double value = 0;
  int par_idx = 0;
  for(unsigned int i = 0; i < v_mtop_subFunctions.size(); i++){
    value += v_mtop_subFunctions.at(i)->EvalPar(x,&par[par_idx]);
    par_idx += v_mtop_subFunctions.at(i)->GetNpar();
  }
  return value;
}
Double_t mw_function(Double_t* x, Double_t* par) {
  double value = 0;
  int par_idx = 0;
  for(unsigned int i = 0; i < v_mw_subFunctions.size(); i++){
    value += v_mw_subFunctions.at(i)->EvalPar(x,&par[par_idx]);
    par_idx += v_mw_subFunctions.at(i)->GetNpar();
  }
  return value;
}
Double_t rbq_function(Double_t* x, Double_t* par) {
  double value = 0;
  int par_idx = 0;
  for(unsigned int i = 0; i < v_rbq_subFunctions.size(); i++){
    value += v_rbq_subFunctions.at(i)->EvalPar(x,&par[par_idx]);
    par_idx += v_rbq_subFunctions.at(i)->GetNpar();
  }
  return value;
}
Double_t mlb_function(Double_t* x, Double_t* par) {
  double value = 0;
  int par_idx = 0;
  for(unsigned int i = 0; i < v_mlb_subFunctions.size(); i++){
    value += v_mlb_subFunctions.at(i)->EvalPar(x,&par[par_idx]);
    par_idx += v_mlb_subFunctions.at(i)->GetNpar();
  }
  return value;
}
Double_t rbq_DL_function(Double_t* x, Double_t* par) {
  double value = 0;
  int par_idx = 0;
  for(unsigned int i = 0; i < v_rbq_DL_subFunctions.size(); i++){
    value += v_rbq_DL_subFunctions.at(i)->EvalPar(x,&par[par_idx]);
    par_idx += v_rbq_DL_subFunctions.at(i)->GetNpar();
  }
  return value;
}
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//Definition of subfunctions
vector<TF1*> GetSubFuncs(const Double_t* input_pars, TString category){
  vector<TF1*> output_subFunctions;
  if(category == "mtop"){
    int par_idx = 0;
    for(unsigned int func_idx = 0; func_idx < v_mtop_subFunctions.size(); func_idx++){
      output_subFunctions.push_back((TF1*)v_mtop_subFunctions.at(func_idx));
      output_subFunctions.at(func_idx)->SetParameters(&input_pars[par_idx]);
      par_idx += output_subFunctions.at(func_idx)->GetNpar();
    }
  }
  else if(category == "mw"){
    int par_idx = 0;
    for(unsigned int func_idx = 0; func_idx < v_mw_subFunctions.size(); func_idx++){
      output_subFunctions.push_back((TF1*)v_mw_subFunctions.at(func_idx));
      output_subFunctions.at(func_idx)->SetParameters(&input_pars[par_idx]);
      par_idx += output_subFunctions.at(func_idx)->GetNpar();
    }
  }
  else if(category == "rbq"){
    int par_idx = 0;
    for(unsigned int func_idx = 0; func_idx < v_rbq_subFunctions.size(); func_idx++){
      output_subFunctions.push_back((TF1*)v_rbq_subFunctions.at(func_idx));
      output_subFunctions.at(func_idx)->SetParameters(&input_pars[par_idx]);
      par_idx += output_subFunctions.at(func_idx)->GetNpar();
    }
  }
  else if(category == "mlb"){
    int par_idx = 0;
    for(unsigned int func_idx = 0; func_idx < v_mlb_subFunctions.size(); func_idx++){
      output_subFunctions.push_back((TF1*)v_mlb_subFunctions.at(func_idx));
      output_subFunctions.at(func_idx)->SetParameters(&input_pars[par_idx]);
      par_idx += output_subFunctions.at(func_idx)->GetNpar();
    }
  }
  // else if(category == "mlb"){
  //     // par[0] * TMath::Gaus(x[0], par[1], par[2]) + 
  //     // par[3] * TMath::Gaus(x[0], par[4], par[5]) + 
  //     // par[3] * TMath::Gaus(x[0], par[6], par[5]);
  //   output_subFunctions.push_back((TF1*)v_mlb_subFunctions.at(0));
  //   output_subFunctions.at(0)->SetParameter(0,input_pars[0]);
  //   output_subFunctions.at(0)->SetParameter(1,input_pars[1]);
  //   output_subFunctions.at(0)->SetParameter(2,input_pars[2]);
  //   output_subFunctions.push_back((TF1*)v_mlb_subFunctions.at(1));
  //   output_subFunctions.at(1)->SetParameter(0,input_pars[3]);
  //   output_subFunctions.at(1)->SetParameter(1,input_pars[4]);
  //   output_subFunctions.at(1)->SetParameter(2,input_pars[5]);
  //   output_subFunctions.push_back((TF1*)v_mlb_subFunctions.at(2));
  //   output_subFunctions.at(2)->SetParameter(0,input_pars[3]);
  //   output_subFunctions.at(2)->SetParameter(1,input_pars[6]);
  //   output_subFunctions.at(2)->SetParameter(2,input_pars[5]);
  // }
  else if(category == "rbq_DL"){
    int par_idx = 0;
    for(unsigned int func_idx = 0; func_idx < v_rbq_DL_subFunctions.size(); func_idx++){
      output_subFunctions.push_back((TF1*)v_rbq_DL_subFunctions.at(func_idx));
      output_subFunctions.at(func_idx)->SetParameters(&input_pars[par_idx]);
      par_idx += output_subFunctions.at(func_idx)->GetNpar();
    }
  }
  else{
    cout << "Unrecognized category: " << category << ". No parameter conversion possible." << endl;
    //return 0;
  }

  return output_subFunctions;
}


//////////////////////////////////////////////////////////
//Parameter converter
void ConvertPars(const Double_t* input_pars, Double_t* output_pars, const int npar_out, TString category, double mtop, double JSF, double bJSF){
  // double *output_pars = new double[npar_out];
  if((category == "mtop") || (category == "rbq")){
    for (int k=0; k<npar_out; k++){
      output_pars[k] = (input_pars[k + 0*npar_out] +
                        input_pars[k + 1*npar_out]*(mtop - 172.5) +
                        input_pars[k + 2*npar_out]*(JSF  - 1.00) +
                        input_pars[k + 3*npar_out]*(bJSF - 1.00));
    }
  }
  else if(category == "mw"){
    for (int k=0; k<npar_out; k++){
      output_pars[k] = (input_pars[k + 0*npar_out] +
                        input_pars[k + 1*npar_out]*(JSF - 1.00));
    }
  }
  else if((category == "mlb") || (category == "rbq_DL")){
    for (int k=0; k<npar_out; k++){
      output_pars[k] = (input_pars[k + 0*npar_out] +
                        input_pars[k + 1*npar_out]*(mtop - 172.5));
      // output_pars[k] = (input_pars[k + 0*npar_out] +                                                                                                                                                     
      //                   input_pars[k + 1*npar_out]*(mtop - 172.5) +                                                                                                                                      
      //                   input_pars[k + 2*npar_out]*(bJSF - 1.00));                                                                                                                                       
    }
  }
  //  else{
  //  cout << "Unrecognized category: " << category << ". No parameter conversion possible." << endl;
  //  return 0;
  // }

  //  return output_pars;
}


//////////////////////////////////////////////////////////
//Tools to plot pull or ratio of a TF1 to a histogram 
TH1D* FitPull(TF1* f, TH1D* h){
  TH1D* hpull=(TH1D*) h->Clone("hpull");
  double range_min = f->GetXmin();
  double range_max = f->GetXmax();
  for (int i = 1; i <= hpull->GetNbinsX(); i++)
    {
      double x=hpull->GetBinCenter(i);
      double valf=f->Eval(x);
      double valh=hpull->GetBinContent(i);
      double errh=hpull->GetBinError(i);
      double diff_sigma=(valf - valh)/errh;
      if((x < range_min) || (x > range_max))
	hpull->SetBinContent(i,0);
      else
	hpull->SetBinContent(i,diff_sigma);
    }
  hpull->SetMaximum(4);    
  hpull->SetMinimum(-4);  
  hpull->GetYaxis()->SetTitle("(fit-Sim.)/#sigma");
  hpull->SetLineColor(f->GetLineColor());
  hpull->SetLineWidth(2);
  return hpull;
}

TH1D* FitRatio(TF1* f, TH1D* h){
  TH1D* hratio=(TH1D*) h->Clone("hratio");
  double range_min = f->GetXmin();
  double range_max = f->GetXmax();
  for (int i = 1; i <= hratio->GetNbinsX(); i++)
    {
      double x=hratio->GetBinCenter(i);
      double valf=f->Eval(x);
      double valh=hratio->GetBinContent(i);
      double errh=hratio->GetBinError(i);
      double ratio=valf/valh;
      double ratioerr=ratio*(errh/valh);
      if((x < range_min) || (x > range_max)){
	hratio->SetBinContent(i,0);
	hratio->SetBinError(i,0);
      }
      else{
	hratio->SetBinContent(i,ratio);
	hratio->SetBinError(i,ratioerr);
      }
    }
  hratio->SetMaximum(2);    
  hratio->SetMinimum(-2);  
  hratio->GetYaxis()->SetTitle("fit/Sim.");
  hratio->SetLineColor(f->GetLineColor());
  hratio->SetLineWidth(2);
  return hratio;
}


