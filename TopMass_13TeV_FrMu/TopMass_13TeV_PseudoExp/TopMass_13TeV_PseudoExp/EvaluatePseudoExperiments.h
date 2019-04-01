#ifndef EvaluatePseudoExperiments_H_
#define EvaluatePseudoExperiments_H_

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
//#include <omp.h>
#include "TF1.h"
#include "TRandom3.h"
#include "TH1D.h"

using namespace std;

class EvaluatePseudoExperiments
{

 public:
  
  EvaluatePseudoExperiments(std::string, std::string, std::string, int, double, double, double);
  virtual ~EvaluatePseudoExperiments();
  
  void ReadInputFile();
  void MakeCrosscheckPlots(TH1D*, std::string, std::string, std::string);
  void MakeClosurePlot(std::vector<double> , std::vector<double>, std::vector<double>, std::string, std::string, std::string, std::string, std::string, std::string, std::string);

  std::vector<double> ReturnResultsMtop(){return fVectorMtop;};
  std::vector<double> ReturnResultsJSF(){ return fVectorJSF;};
  std::vector<double> ReturnResultsBJSF(){return fVectorBJSF;};

  // for Barlow correction, adapted from the 8 TeV code
  double BarRho(int, double, double);
  double BarCor(int, int, double, double, double);

 private:
  
  std::string fInputFile;
  std::string fOutputFolder;
  std::string fFileString;

  int fFitDimension;

  std::vector<double> fVectorMtop, fVectorJSF, fVectorBJSF;

  double fMtopInput, fJSFInput, fBJSFInput;

};


#endif
