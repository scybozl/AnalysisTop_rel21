#include "TopMass_13TeV_Parameterization/CombFitPar.h"
#include "TopMass_13TeV_Parameterization/ConfigClass.h" 
#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions
#include "TopMass_13TeV_Parameterization/FCN.h"
#include "TopMass_13TeV_Parameterization/MakePlots.h"

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
#include "TH1D.h"
#include "TSystem.h"
#include "TMath.h"
#include "Math/Functor.h"


using namespace std;


CombFitPar::CombFitPar(){}
CombFitPar::~CombFitPar(){}

void CombFitPar::GetFinalPars(TString S_hist = "hist_klf_window_mtop_reco", TString S_config = "../TopMass_13TeV_FrMu/TopMass_13TeV_Parameterization/data/MainConfigFile_LJ"){
  TString category;
  TF1* f_func;
  vector<TF1*> f_subfunc;
  vector<TString> v_files;
  vector<double> v_mtop; vector<double> v_JSF; vector<double> v_bJSF;
  vector<TH1D> v_hists;
  int npars_lincombo;
  int npars_sep;
  double fitmin;
  double fitmax;
  TString xaxis_title;
  TString xaxis_unit;
  
  //Initialize function and values depending on distribution
  if(S_hist == "h_mtop_param"){
    category = "mtop";
    xaxis_title = xaxis_title_mtop;
    xaxis_unit = xaxis_unit_mtop;
    fitmin = fitmin_mtop;
    fitmax = fitmax_mtop;
    npars_lincombo = npars_comb_mtop;
    npars_sep = npars_sep_mtop;
    f_func = new TF1("f_func", mtop_function, fitmin, fitmax, npars_sep);  
  }
  else if(S_hist == "h_mw_orig"){
    category = "mw";
    xaxis_title = xaxis_title_mw;
    xaxis_unit = xaxis_unit_mw;
    fitmin = fitmin_mw;
    fitmax = fitmax_mw;
    npars_lincombo = npars_comb_mw;
    npars_sep = npars_sep_mw;
    f_func = new TF1("f_func", mw_function, fitmin, fitmax, npars_sep);   
  }
  else if(S_hist == "h_rbq_orig"){
    category = "rbq";
    xaxis_title = xaxis_title_rbq;
    xaxis_unit = xaxis_unit_rbq;
    fitmin = fitmin_rbq;
    fitmax = fitmax_rbq;
    npars_lincombo = npars_comb_rbq;
    npars_sep = npars_sep_rbq;
    f_func = new TF1("f_func", rbq_function, fitmin, fitmax, npars_sep);   
  }
  else if((S_hist == "h_mlb") || 
	  (S_hist == "hist_mlb") || 
	  (S_hist == "hist_klf_window_mlb_reco") || 
	  (S_hist == "hist_klf_original_mlb_reco")){
    category = "mlb";
    xaxis_title = xaxis_title_mlb;
    xaxis_unit = xaxis_unit_mlb;
    fitmin = fitmin_mlb;
    fitmax = fitmax_mlb;
    npars_lincombo = npars_comb_mlb;
    npars_sep = npars_sep_mlb;
    f_func = new TF1("f_func", mlb_function, fitmin, fitmax, npars_sep);   
  }
  else if(S_hist == "hist_rbq_DL"){
    category = "rbq_DL";
    xaxis_title = xaxis_title_rbq_DL;
    xaxis_unit = xaxis_unit_rbq_DL;
    fitmin = fitmin_rbq_DL;
    fitmax = fitmax_rbq_DL;
    npars_lincombo = npars_comb_rbq_DL;
    npars_sep = npars_sep_rbq_DL;
    f_func = new TF1("f_func", rbq_DL_function, fitmin, fitmax, npars_sep);   
  }
  else{
    cout << "Invalid histogram name!" << endl;
    return;
  }

  TString output_dir = "combfit_output/";
  gSystem->Exec("mkdir -p " + output_dir);

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
    
    if( (category == "mw") && ((mtop_d != 172.5) || (bjsf_d != 1.00)) )
      continue;
    if( ((category == "mlb") || (category == "rbq_DL")) && (jsf_d != 1.00) )
      continue;
    v_files.push_back(filename);
    v_mtop.push_back(mtop_d);
    v_JSF.push_back(jsf_d);
    v_bJSF.push_back(bjsf_d);
  }

  //Get histogram bin centers,contents,errors for chi2 minimization
  //#pragma omp parallel for
  for(unsigned int file_idx = 0; file_idx < v_files.size(); file_idx++){
    TFile* f_file = TFile::Open(v_files.at(file_idx));
    TH1D* h_hist = (TH1D*) f_file->Get(S_hist);
    h_hist->Sumw2();
    double histmin = h_hist->GetXaxis()->GetXmin();
    double histmax = h_hist->GetXaxis()->GetXmax();
    h_hist->GetXaxis()->SetRangeUser(fitmin,fitmax);
    h_hist->Scale(1./h_hist->Integral());//BP Change "width" back or keep everywhere!!!
    h_hist->GetXaxis()->SetRangeUser(histmin,histmax);
    
    v_hists.push_back(*h_hist);
  }

  //Get starting parameters from separate-fit root files 
  TString pars_init_dir = "sepfit_output/";

  TFile* f_pars_init = TFile::Open(pars_init_dir + category + "_pars_init.root","READ");
  if (!f_pars_init) { return; }

  TTree* t_pars_init = (TTree*)f_pars_init->Get("pars_init");

  //parameters from linear form: A + Bx
  vector<double>* vmtop_parA;
  vector<double>* vmtop_parB;
  vector<double>* vJSF_parA;
  vector<double>* vJSF_parB;
  vector<double>* vbJSF_parA;
  vector<double>* vbJSF_parB;

  vmtop_parA = 0;
  vmtop_parB = 0;
  vJSF_parA  = 0;
  vJSF_parB  = 0;
  vbJSF_parA = 0;
  vbJSF_parB = 0;

  t_pars_init->SetBranchAddress("vmtop_parA", &vmtop_parA);
  t_pars_init->SetBranchAddress("vmtop_parB", &vmtop_parB);
  t_pars_init->SetBranchAddress("vJSF_parA",  &vJSF_parA);
  t_pars_init->SetBranchAddress("vJSF_parB",  &vJSF_parB);
  t_pars_init->SetBranchAddress("vbJSF_parA", &vbJSF_parA);
  t_pars_init->SetBranchAddress("vbJSF_parB", &vbJSF_parB);

  int nentries = t_pars_init->GetEntries();
  
  t_pars_init->GetEntry(0);

  t_pars_init->ResetBranchAddresses();
  f_pars_init->Close();

  //Setup minimizer
  TMinuitMinimizer* myMinuit;
  //Options for algorithm: Migrad (default),Simplex,Combined,Scan
  myMinuit = new TMinuitMinimizer("",npars_lincombo);

  //Set function to be minimized
  FCN *Mf1 = new FCN(f_func, v_hists, v_mtop, v_JSF, v_bJSF, category);
  ROOT::Math::Functor myFunctor(Mf1, &FCN::FCN_chi2, npars_lincombo);  
  myMinuit -> SetFunction(myFunctor);

  //Set options
  myMinuit->SetMaxFunctionCalls(1000000); 
  myMinuit->SetMaxIterations(10000);
  myMinuit->SetTolerance(0.001);
  myMinuit->SetPrintLevel(1);

  // Set the free variables to be minimized!
  if(category == "mtop"){
    for(int k = 0; k < npars_sep_mtop; k++){
      myMinuit->SetVariable(k + 0*npars_sep_mtop,Form("mtop_par%i_A"     ,k),vmtop_parA->at(k),0.01);
      myMinuit->SetVariable(k + 1*npars_sep_mtop,Form("mtop_par%i_B_mtop",k),vmtop_parB->at(k),0.01);
      myMinuit->SetVariable(k + 2*npars_sep_mtop,Form("mtop_par%i_B_JSF" ,k),vJSF_parB->at(k) ,0.01);
      myMinuit->SetVariable(k + 3*npars_sep_mtop,Form("mtop_par%i_B_bJSF",k),vbJSF_parB->at(k),0.01);
    }
  }
  else if(category == "mw"){
    for(int k = 0; k < npars_sep_mw; k++){
      myMinuit->SetVariable(k + 0*npars_sep_mw,Form("mw_par%i_A"    ,k),vJSF_parA->at(k),0.01);
      myMinuit->SetVariable(k + 1*npars_sep_mw,Form("mw_par%i_B_JSF",k),vJSF_parB->at(k),0.01);
    }
  }
  else if(category == "rbq"){
    for(int k = 0; k < npars_sep_rbq; k++){
      myMinuit->SetVariable(k + 0*npars_sep_rbq,Form("rbq_par%i_A"     ,k),vmtop_parA->at(k),0.01);
      myMinuit->SetVariable(k + 1*npars_sep_rbq,Form("rbq_par%i_B_mtop",k),vmtop_parB->at(k),0.01);
      myMinuit->SetVariable(k + 2*npars_sep_rbq,Form("rbq_par%i_B_JSF" ,k),vJSF_parB->at(k) ,0.01);
      myMinuit->SetVariable(k + 3*npars_sep_rbq,Form("rbq_par%i_B_bJSF",k),vbJSF_parB->at(k),0.01);
    }
  }
  else if(category == "mlb"){
    for(int k = 0; k < npars_sep_mlb; k++){
      myMinuit->SetVariable(k + 0*npars_sep_mlb,Form("mlb_par%i_A"     ,k),vmtop_parA->at(k),0.01);
      myMinuit->SetVariable(k + 1*npars_sep_mlb,Form("mlb_par%i_B_mtop",k),vmtop_parB->at(k),0.01);
      //myMinuit->SetVariable(k + 2*npars_sep_mlb,Form("mlb_par%i_B_bJSF",k),vbJSF_parB->at(k),0.01);
    }
  }
  else if(category == "rbq_DL"){
    for(int k = 0; k < npars_sep_rbq_DL; k++){
      myMinuit->SetVariable(k + 0*npars_sep_rbq_DL,Form("rbq_DL_par%i_A"     ,k),vmtop_parA->at(k),0.01);
      myMinuit->SetVariable(k + 1*npars_sep_rbq_DL,Form("rbq_DL_par%i_B_mtop",k),vmtop_parB->at(k),0.01);
      myMinuit->SetVariable(k + 2*npars_sep_rbq_DL,Form("rbq_DL_par%i_B_bJSF",k),vbJSF_parB->at(k),0.01);
    }
  }
  
  //Do the minimization
  bool minStatus = myMinuit->Minimize();
  if(!minStatus){
    cout << "Error in Minuit minimization of combined fit!!!" << endl;
    return;
  }
  bool hesseStatus = myMinuit->Hesse();
  if(!hesseStatus){
    cout << "Error in Minuit Hesse minimization of combined fit!!!" << endl;
    return;
  }

  //Get result of minimization
  const double *result_par = myMinuit->X();
  const double *result_par_error = myMinuit->Errors();
  double result_chi2 = myMinuit->MinValue();
  int result_ndim = myMinuit->NFree();

  //Get NDF from: (total # of fitted histogram bins) - (# of free parameters in the fit)
  int nbinsfit = 0;
  for (unsigned int hist_idx = 0; hist_idx < v_hists.size(); hist_idx++){
    for (int bin_idx = 1; bin_idx < v_hists[hist_idx].GetNbinsX()+1; bin_idx++){
      double bincenter = v_hists[hist_idx].GetBinCenter(bin_idx);
      if((bincenter < fitmin) || (bincenter > fitmax))
	continue;
      nbinsfit++;
    }
  }
  int total_ndf = nbinsfit - result_ndim;
      
  //Prepare output file
  TFile* outFile = new TFile(output_dir + category + "_pars.root","RECREATE");
  vector<double> Parameters;
  vector<double> Errors;
  vector<TString> Names;
  TTree *ttree = new TTree("pars","Tree with vectors");
  ttree->Branch("Parameters",&Parameters);
  ttree->Branch("Errors",&Errors);
  ttree->Branch("Names",&Names);

  //Fill TTree
  int min_npar = myMinuit->NDim();
  for(int paridx = 0; paridx < min_npar; paridx++){
    Parameters.push_back(result_par[paridx]);
    Errors.push_back(result_par_error[paridx]);
    TString varName = myMinuit->VariableName(paridx);
    Names.push_back(varName);
  }
  outFile->cd();
  ttree->Fill();
  ttree->Write();
  outFile->Close();

  //Make fit overlay plots
  for(unsigned int file_idx = 0; file_idx < v_files.size(); file_idx++){
    TFile* f_file = TFile::Open(v_files.at(file_idx));
    TH1D* h_hist = (TH1D*) f_file->Get(S_hist);
    h_hist->Sumw2();
    double histmin = h_hist->GetXaxis()->GetXmin();
    double histmax = h_hist->GetXaxis()->GetXmax();
    h_hist->GetXaxis()->SetRangeUser(fitmin,fitmax);
    h_hist->Scale(1./h_hist->Integral());//BP Change "width" back or keep everywhere!!!
    h_hist->GetXaxis()->SetRangeUser(histmin,histmax);

    //Combine linear pars into single pars for input to function
    double *func_pars = new double[npars_sep];
    ConvertPars(result_par, func_pars, npars_sep, category, v_mtop.at(file_idx), v_JSF.at(file_idx), v_bJSF.at(file_idx));
    f_func->SetParameters(func_pars);

    //Get sub-functions
    vector<TF1*> v_subfuncs;
    v_subfuncs = GetSubFuncs(func_pars, category);    

    //Input fit info
    char file_metadata[10];
    sprintf(file_metadata,"mtop_%0.1f_JSF_%0.2f_bJSF_%0.2f",v_mtop.at(file_idx),v_JSF.at(file_idx),v_bJSF.at(file_idx));

    FitInfo fInfo;
    fInfo.InputHisto = h_hist;
    fInfo.SubFunctions = v_subfuncs;
    fInfo.SumFunctions = f_func;
    fInfo.Chi2 = result_chi2;
    fInfo.NDF = total_ndf;
    fInfo.OutputFile = output_dir + category + "_" + file_metadata;
    fInfo.xAxis_Title = xaxis_title;
    fInfo.xAxis_Unit = xaxis_unit;
    
    MakePlots* myMakePlots = new MakePlots();
    myMakePlots->FitPlots(fInfo);

    delete func_pars;
  }
  
  delete myMinuit;
  delete Mf1;
  delete f_func;
}
