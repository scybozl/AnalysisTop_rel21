#include "TopMass_13TeV_PseudoExp/EvaluatePseudoExperiments.h"

#include "TSystem.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TMinuit.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <set>
#include <iomanip>
#include <string>

using namespace std;


int main(int argc, char* argv[]){

  if(argc != 7){
    
    cout << "\t" << endl;
    cout << "ERROR: Number of input variables is wrong!!!   ===> " << argc << endl;
    cout << "\t" << endl;
    
    return 1;
    
  }
  else{
    
  }
  
  string InputFolder   = argv[1];
  string OutputFolder  = argv[2];
  int    FitDimension  = TString(argv[3]).Atoi(); // can be 1,2,3 depending on if we fit only mtop, or mtop+JSF, or mtop+JSF+bJSF
  string NrPE          = argv[4];
  string FileString1   = argv[5];
  string CheckType     = argv[6]; // can be: mtop, jsf, bjsf
  string JustDim       = argv[3];

  std::vector<double> result_mtop_169p0_1p0_1p0;
  std::vector<double> result_mtop_171p0_1p0_1p0;
  std::vector<double> result_mtop_172p0_1p0_1p0;
  std::vector<double> result_mtop_172p25_1p0_1p0;
  std::vector<double> result_mtop_172p5_1p0_1p0;
  std::vector<double> result_mtop_172p75_1p0_1p0;
  std::vector<double> result_mtop_173p0_1p0_1p0;
  std::vector<double> result_mtop_174p0_1p0_1p0;
  std::vector<double> result_mtop_176p0_1p0_1p0;

  std::vector<double> result_mtop_172p5_0p98_1p0;
  std::vector<double> result_mtop_172p5_0p99_1p0;
  std::vector<double> result_mtop_172p5_1p01_1p0;
  std::vector<double> result_mtop_172p5_1p02_1p0;

  std::vector<double> result_mtop_172p5_1p0_0p98;
  std::vector<double> result_mtop_172p5_1p0_0p99;
  std::vector<double> result_mtop_172p5_1p0_1p01;
  std::vector<double> result_mtop_172p5_1p0_1p02;

  std::string Dim        = JustDim+"D";  // "1_"+argv[3]+"D";
  std::string FileString = "169p0_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
  std::string InputFile  = InputFolder+"/"+FileString+".root";
  double InputMtop = 171.0;
  double InputJSF  = 1.0;
  double InputBJSF = 1.0;

  if(CheckType == "mtop"){

    //    EvaluatePseudoExperiments *fEval1 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 169.0, 1.0, 1.0);
    //fEval1 -> ReadInputFile();
    //result_mtop_169p0_1p0_1p0 = fEval1 -> ReturnResultsMtop();

    FileString = "171p0_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";  
    InputFile  = InputFolder+"/"+FileString+".root";
    EvaluatePseudoExperiments *fEval2 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 171.0, 1.0, 1.0);
    fEval2 -> ReadInputFile();
    result_mtop_171p0_1p0_1p0 = fEval2 -> ReturnResultsMtop(); // mtop_diff_mean, mtop_diff_mean_err, mtop_diff_rms, mtop_e_mean, mtop_pull_rms

    FileString = "172p0_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    InputFile  = InputFolder+"/"+FileString+".root";
    EvaluatePseudoExperiments *fEval3 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 172.0, 1.0, 1.0);
    fEval3 -> ReadInputFile();
    result_mtop_172p0_1p0_1p0 = fEval3 -> ReturnResultsMtop();

    //FileString = "172p25_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    //InputFile  = InputFolder+"/"+FileString+".root";
    //EvaluatePseudoExperiments *fEval4 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 172.25, 1.0, 1.0);
    //fEval4 -> ReadInputFile();
    //result_mtop_172p25_1p0_1p0 = fEval4 -> ReturnResultsMtop();

    FileString = "172p5_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    InputFile  = InputFolder+"/"+FileString+".root";
    EvaluatePseudoExperiments *fEval5 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 172.5, 1.0, 1.0);
    fEval5 -> ReadInputFile();
    result_mtop_172p5_1p0_1p0 = fEval5 -> ReturnResultsMtop();

    //FileString = "172p75_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    //InputFile  = InputFolder+"/"+FileString+".root";
    //EvaluatePseudoExperiments *fEval6 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 172.75, 1.0, 1.0);
    //fEval6 -> ReadInputFile();
    //result_mtop_172p75_1p0_1p0 = fEval6 -> ReturnResultsMtop();

    FileString = "173p0_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    InputFile  = InputFolder+"/"+FileString+".root";
    EvaluatePseudoExperiments *fEval7 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 173.0, 1.0, 1.0);
    fEval7 -> ReadInputFile();
    result_mtop_173p0_1p0_1p0 = fEval7 -> ReturnResultsMtop();

    FileString = "174p0_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    InputFile  = InputFolder+"/"+FileString+".root";
    EvaluatePseudoExperiments *fEval8 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 174.0, 1.0, 1.0);
    fEval8 -> ReadInputFile();
    result_mtop_174p0_1p0_1p0 = fEval8 -> ReturnResultsMtop();

    //FileString = "176p0_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    //InputFile  = InputFolder+"/"+FileString+".root";
    //EvaluatePseudoExperiments *fEval9 = new EvaluatePseudoExperiments(InputFile, OutputFolder, FileString, FitDimension, 176.0, 1.0, 1.0);
    //fEval9 -> ReadInputFile();
    //result_mtop_176p0_1p0_1p0 = fEval9 -> ReturnResultsMtop();

    std::vector<double> mtop_in;
    //    mtop_in.push_back(169.0);
    mtop_in.push_back(171.0);
    mtop_in.push_back(172.0);
    // mtop_in.push_back(172.25);
    mtop_in.push_back(172.5);
    // mtop_in.push_back(172.75);
    mtop_in.push_back(173.0);
    mtop_in.push_back(174.0);
    // mtop_in.push_back(176.0);

    std::vector<double> mtop_out;
    //mtop_out.push_back(result_mtop_169p0_1p0_1p0[0]);
    mtop_out.push_back(result_mtop_171p0_1p0_1p0[0]);
    mtop_out.push_back(result_mtop_172p0_1p0_1p0[0]);
    //mtop_out.push_back(result_mtop_172p25_1p0_1p0[0]);
    mtop_out.push_back(result_mtop_172p5_1p0_1p0[0]);
    //mtop_out.push_back(result_mtop_172p75_1p0_1p0[0]);
    mtop_out.push_back(result_mtop_173p0_1p0_1p0[0]);
    mtop_out.push_back(result_mtop_174p0_1p0_1p0[0]);
    //mtop_out.push_back(result_mtop_176p0_1p0_1p0[0]);

    std::vector<double> mtop_out_err;
    //mtop_out_err.push_back(result_mtop_169p0_1p0_1p0[2]);
    mtop_out_err.push_back(result_mtop_171p0_1p0_1p0[2]);
    mtop_out_err.push_back(result_mtop_172p0_1p0_1p0[2]);
    //mtop_out_err.push_back(result_mtop_172p25_1p0_1p0[2]);
    mtop_out_err.push_back(result_mtop_172p5_1p0_1p0[2]);
    //mtop_out_err.push_back(result_mtop_172p75_1p0_1p0[2]);
    mtop_out_err.push_back(result_mtop_173p0_1p0_1p0[2]);
    mtop_out_err.push_back(result_mtop_174p0_1p0_1p0[2]);
    //mtop_out_err.push_back(result_mtop_176p0_1p0_1p0[2]);

    std::vector<double> mtop_pull;
    //mtop_pull.push_back(result_mtop_169p0_1p0_1p0[4]);
    mtop_pull.push_back(result_mtop_171p0_1p0_1p0[4]);
    mtop_pull.push_back(result_mtop_172p0_1p0_1p0[4]);
    //mtop_pull.push_back(result_mtop_172p25_1p0_1p0[4]);
    mtop_pull.push_back(result_mtop_172p5_1p0_1p0[4]);
    //mtop_pull.push_back(result_mtop_172p75_1p0_1p0[4]);
    mtop_pull.push_back(result_mtop_173p0_1p0_1p0[4]);
    mtop_pull.push_back(result_mtop_174p0_1p0_1p0[4]);
    //mtop_pull.push_back(result_mtop_176p0_1p0_1p0[4]);

    std::vector<double> mtop_pull_err;
    //mtop_pull_err.push_back(result_mtop_169p0_1p0_1p0[5]);
    mtop_pull_err.push_back(result_mtop_171p0_1p0_1p0[5]);
    mtop_pull_err.push_back(result_mtop_172p0_1p0_1p0[5]);
    //mtop_pull_err.push_back(result_mtop_172p25_1p0_1p0[5]);
    mtop_pull_err.push_back(result_mtop_172p5_1p0_1p0[5]);
    //mtop_pull_err.push_back(result_mtop_172p75_1p0_1p0[5]);
    mtop_pull_err.push_back(result_mtop_173p0_1p0_1p0[5]);
    mtop_pull_err.push_back(result_mtop_174p0_1p0_1p0[5]);
    //mtop_pull_err.push_back(result_mtop_176p0_1p0_1p0[5]);

    fEval5 -> MakeClosurePlot(mtop_in, mtop_out,  mtop_out_err,  "m_{top}^{in} [GeV]", "m_{top}^{in} - m_{top}^{out} [GeV]", (OutputFolder+"/Closure_mtop_diff_"+FileString1+".pdf").c_str(), "mtop", "diff", Dim, NrPE);
    fEval5 -> MakeClosurePlot(mtop_in, mtop_out,  mtop_out_err,  "m_{top}^{in} [GeV]", "m_{top}^{in} - m_{top}^{out} [GeV]", (OutputFolder+"/Closure_mtop_diff_"+FileString1+".pdf").c_str(), "mtop", "diff", Dim, NrPE);
    fEval5 -> MakeClosurePlot(mtop_in, mtop_pull, mtop_pull_err, "m_{top}^{in} [GeV]", "m_{top} pull width",                 (OutputFolder+"/Closure_mtop_pull_"+FileString1+".pdf").c_str(), "mtop", "pull", Dim, NrPE);



  }

  if(CheckType == "jsf"){

    FileString = "172p5_0p98_1p0_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval6 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 0.98, 1.0);
    fEval6 -> ReadInputFile();
    result_mtop_172p5_0p98_1p0 = fEval6 -> ReturnResultsJSF();
    
    FileString = "172p5_0p99_1p0_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval7 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 0.99, 1.0);
    fEval7 -> ReadInputFile();
    result_mtop_172p5_0p99_1p0 = fEval7 -> ReturnResultsJSF();
    
    FileString = "172p5_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval3 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.0, 1.0);
    fEval3 -> ReadInputFile();
    result_mtop_172p5_1p0_1p0 = fEval3 -> ReturnResultsJSF();

    FileString = "172p5_1p01_1p0_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval8 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.01, 1.0);
    fEval8 -> ReadInputFile();
    result_mtop_172p5_1p01_1p0 = fEval8 -> ReturnResultsJSF();
    
    FileString = "172p5_1p02_1p0_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval9 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.02, 1.0);
    fEval9 -> ReadInputFile();
    result_mtop_172p5_1p02_1p0 = fEval9 -> ReturnResultsJSF();

    std::vector<double> jsf_in;
    jsf_in.push_back(0.98);
    jsf_in.push_back(0.99);
    jsf_in.push_back(1.00);
    jsf_in.push_back(1.01);
    jsf_in.push_back(1.02);

    std::vector<double> jsf_out;
    jsf_out.push_back(result_mtop_172p5_0p98_1p0[0]);
    jsf_out.push_back(result_mtop_172p5_0p99_1p0[0]);
    jsf_out.push_back(result_mtop_172p5_1p0_1p0[0]);
    jsf_out.push_back(result_mtop_172p5_1p01_1p0[0]);
    jsf_out.push_back(result_mtop_172p5_1p02_1p0[0]);

    std::vector<double> jsf_out_err;
    jsf_out_err.push_back(result_mtop_172p5_0p98_1p0[2]);
    jsf_out_err.push_back(result_mtop_172p5_0p99_1p0[2]);
    jsf_out_err.push_back(result_mtop_172p5_1p0_1p0[2]);
    jsf_out_err.push_back(result_mtop_172p5_1p01_1p0[2]);
    jsf_out_err.push_back(result_mtop_172p5_1p02_1p0[2]);

    std::vector<double> jsf_pull;
    jsf_pull.push_back(result_mtop_172p5_0p98_1p0[4]);
    jsf_pull.push_back(result_mtop_172p5_0p99_1p0[4]);
    jsf_pull.push_back(result_mtop_172p5_1p0_1p0[4]);
    jsf_pull.push_back(result_mtop_172p5_1p01_1p0[4]);
    jsf_pull.push_back(result_mtop_172p5_1p02_1p0[4]);

    std::vector<double> jsf_pull_err;
    jsf_pull_err.push_back(result_mtop_172p5_0p98_1p0[5]);
    jsf_pull_err.push_back(result_mtop_172p5_0p99_1p0[5]);
    jsf_pull_err.push_back(result_mtop_172p5_1p0_1p0[5]);
    jsf_pull_err.push_back(result_mtop_172p5_1p01_1p0[5]);
    jsf_pull_err.push_back(result_mtop_172p5_1p02_1p0[5]);

    fEval9 -> MakeClosurePlot(jsf_in, jsf_out,  jsf_out_err,  "JSF^{in} [GeV]", "JSF^{in} - JSF^{out} [GeV]",  (OutputFolder+"/Closure_jsf_diff_"+FileString1+".pdf").c_str(), "jsf", "diff", Dim, NrPE);
    fEval9 -> MakeClosurePlot(jsf_in, jsf_out,  jsf_out_err,  "JSF^{in} [GeV]", "JSF^{in} - JSF^{out} [GeV]",  (OutputFolder+"/Closure_jsf_diff_"+FileString1+".pdf").c_str(), "jsf", "diff", Dim, NrPE);
    fEval9 -> MakeClosurePlot(jsf_in, jsf_pull, jsf_pull_err, "JSF^{in} [GeV]", "JSF pull width",              (OutputFolder+"/Closure_jsf_pull_"+FileString1+".pdf").c_str(), "jsf", "pull", Dim, NrPE);

  }

  if(CheckType == "bjsf"){

    FileString = "172p5_1p0_0p98_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval10 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.0, 0.98);
    fEval10 -> ReadInputFile();
    result_mtop_172p5_1p0_0p98 = fEval10 -> ReturnResultsBJSF();
    
    FileString = "172p5_1p0_0p99_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval11 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.0, 0.99);
    fEval11 -> ReadInputFile();
    result_mtop_172p5_1p0_0p99 = fEval11 -> ReturnResultsBJSF();

    FileString = "172p5_1p0_1p0_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval3 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.0, 1.0);
    fEval3 -> ReadInputFile();
    result_mtop_172p5_1p0_1p0 = fEval3 -> ReturnResultsBJSF();
    
    FileString = "172p5_1p0_1p01_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval12 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.0, 1.01);
    fEval12 -> ReadInputFile();
    result_mtop_172p5_1p0_1p01 = fEval12 -> ReturnResultsBJSF();
    
    FileString = "172p5_1p0_1p02_"+NrPE+"PE_"+argv[3]+"D";
    EvaluatePseudoExperiments *fEval13 = new EvaluatePseudoExperiments(InputFolder+"/"+FileString+".root", OutputFolder, FileString, FitDimension, 172.5, 1.0, 1.02);
    fEval13 -> ReadInputFile();
    result_mtop_172p5_1p0_1p02 = fEval13 -> ReturnResultsBJSF();


    std::vector<double> bjsf_in;
    bjsf_in.push_back(0.98);
    bjsf_in.push_back(0.99);
    bjsf_in.push_back(1.00);
    bjsf_in.push_back(1.01);
    bjsf_in.push_back(1.02);

    std::vector<double> bjsf_out;
    bjsf_out.push_back(result_mtop_172p5_1p0_0p98[0]);
    bjsf_out.push_back(result_mtop_172p5_1p0_0p99[0]);
    bjsf_out.push_back(result_mtop_172p5_1p0_1p0[0]);
    bjsf_out.push_back(result_mtop_172p5_1p0_1p01[0]);
    bjsf_out.push_back(result_mtop_172p5_1p0_1p02[0]);

    std::vector<double> bjsf_out_err;
    bjsf_out_err.push_back(result_mtop_172p5_1p0_0p98[2]);
    bjsf_out_err.push_back(result_mtop_172p5_1p0_0p99[2]);
    bjsf_out_err.push_back(result_mtop_172p5_1p0_1p0[2]);
    bjsf_out_err.push_back(result_mtop_172p5_1p0_1p01[2]);
    bjsf_out_err.push_back(result_mtop_172p5_1p0_1p02[2]);

    std::vector<double> bjsf_pull;
    bjsf_pull.push_back(result_mtop_172p5_1p0_0p98[4]);
    bjsf_pull.push_back(result_mtop_172p5_1p0_0p99[4]);
    bjsf_pull.push_back(result_mtop_172p5_1p0_1p0[4]);
    bjsf_pull.push_back(result_mtop_172p5_1p0_1p01[4]);
    bjsf_pull.push_back(result_mtop_172p5_1p0_1p02[4]);

    std::vector<double> bjsf_pull_err;
    bjsf_pull_err.push_back(result_mtop_172p5_1p0_0p98[5]);
    bjsf_pull_err.push_back(result_mtop_172p5_1p0_0p99[5]);
    bjsf_pull_err.push_back(result_mtop_172p5_1p0_1p0[5]);
    bjsf_pull_err.push_back(result_mtop_172p5_1p0_1p01[5]);
    bjsf_pull_err.push_back(result_mtop_172p5_1p0_1p02[5]);
   
    fEval13 -> MakeClosurePlot(bjsf_in, bjsf_out,  bjsf_out_err,  "bJSF^{in} [GeV]", "bJSF^{in} - bJSF^{out} [GeV]", (OutputFolder+"/Closure_bjsf_diff_"+FileString1+".pdf").c_str(), "bjsf", "diff", Dim, NrPE);
    fEval13 -> MakeClosurePlot(bjsf_in, bjsf_out,  bjsf_out_err,  "bJSF^{in} [GeV]", "bJSF^{in} - bJSF^{out} [GeV]", (OutputFolder+"/Closure_bjsf_diff_"+FileString1+".pdf").c_str(), "bjsf", "diff", Dim, NrPE);
    fEval13 -> MakeClosurePlot(bjsf_in, bjsf_pull, bjsf_pull_err, "bJSF^{in} [GeV]", "bJSF pull width",              (OutputFolder+"/Closure_bjsf_pull_"+FileString1+".pdf").c_str(), "bjsf", "pull", Dim, NrPE);
 
  }



  return 0;

}

