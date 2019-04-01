#include "TopMass_13TeV_Parameterization/FCN.h" 
#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions

#include "TMinuit.h"
#include "TMinuitMinimizer.h"
#include "TMatrixD.h"
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
#include "TMath.h"
#include "Math/Functor.h"


using namespace std;

/*TString category;
TF1* f_func;
vector<TString> v_files;
vector<double> v_mtop; vector<double> v_JSF; vector<double> v_bJSF;
vector<vector<double>> vv_bincenter;
vector<vector<double>> vv_bincontent;
vector<vector<double>> vv_binerror;

*/

FCN::FCN(TF1* fitFunc, std::vector<TH1D> hists, std::vector<double> vals_mtop, std::vector<double> vals_jsf, std::vector<double> vals_bjsf, TString category){
  f_func      = fitFunc;
  f_hists     = hists;
  f_vals_mtop = vals_mtop;
  f_vals_jsf  = vals_jsf;
  f_vals_bjsf = vals_bjsf;
  f_category  = category;
}

FCN::~FCN(){}


Double_t FCN::FCN_chi2(const Double_t* par){
  //Calculate total ChiSq over all applicable files for a given distribution
  double chi2total = 0;
  double range_min = f_func->GetXmin();
  double range_max = f_func->GetXmax();

  for(unsigned int file_idx = 0; file_idx < f_hists.size(); file_idx++){
    const int npar = f_func->GetNpar();
    double *lincombo_par = new double[npar];
    ConvertPars(par, lincombo_par, npar, f_category, f_vals_mtop.at(file_idx), f_vals_jsf.at(file_idx), f_vals_bjsf.at(file_idx));
    f_func->SetParameters(lincombo_par);

    double chi2 = 0;
    for (int bin_idx = 1; bin_idx < f_hists[file_idx].GetNbinsX()+1; bin_idx++)
      {
	double bincenter = f_hists[file_idx].GetBinCenter(bin_idx);
	if((bincenter < range_min) || (bincenter > range_max))
	  continue;
	double f_val     = f_func->Eval(bincenter);
	double h_val     = f_hists[file_idx].GetBinContent(bin_idx);
	double h_val_err = f_hists[file_idx].GetBinError(bin_idx);
	chi2 += pow((f_val - h_val)/h_val_err,2);
      }
    chi2total += chi2; 
    delete lincombo_par;
  }

  return chi2total;
}

Double_t FCN::FCN_chi2sep(const Double_t* par){
  //Calculate the ChiSq of a single file for a given distribution
  f_func->SetParameters(par);
  double range_min = f_func->GetXmin();
  double range_max = f_func->GetXmax();

  double chi2 = 0;
  for (int bin_idx = 1; bin_idx < f_hists[0].GetNbinsX()+1; bin_idx++)
    {
      double bincenter = f_hists[0].GetBinCenter(bin_idx);
      if((bincenter < range_min) || (bincenter > range_max))
	continue;
      double f_val     = f_func->Eval(bincenter);
      double h_val     = f_hists[0].GetBinContent(bin_idx);
      double h_val_err = f_hists[0].GetBinError(bin_idx);
      chi2 += pow((f_val - h_val)/h_val_err,2);
    }
  
  return chi2;
}

