#ifndef CombFitPar_H_
#define CombFitPar_H_

#include "TString.h"

using namespace std;

class CombFitPar{
  
 public: 
  
  //constructor
  CombFitPar(); //constructor
  //CombFitPar(const TString histo_name); //constructor
  virtual ~CombFitPar(); //constructor

  void GetFinalPars(TString S_hist, TString S_config);
  //  Double_t FCN(const Double_t* par);

};

#endif
