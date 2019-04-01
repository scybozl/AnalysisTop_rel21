#ifndef SepFitPar_H_
#define SepFitPar_H_

#include "TString.h"
#include "TF1.h"

using namespace std;

class SepFitPar{
  
 public: 
  
  //constructor
  SepFitPar(); //constructor
  //SepFitPar(const TString histo_name); //constructor
  virtual ~SepFitPar(); //constructor

  void GetInitPars(TString S_hist, TString S_config);
  TF1* SepFit(TString S_file, TString S_hist, TString func_name, double fitmin, double fitmax, TString out_dir);

};

#endif
