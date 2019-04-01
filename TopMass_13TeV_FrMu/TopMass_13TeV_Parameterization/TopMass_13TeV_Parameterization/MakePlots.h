#ifndef MakePlots_H_
#define MakePlots_H_

#include "FitInfo.h"
#include "TString.h"
#include "TF1.h"

using namespace std;

class MakePlots{
  
 public: 
  
  //constructor
  MakePlots(); //constructor
  virtual ~MakePlots(); //constructor

  void FitPlots(FitInfo fInfo);
};

#endif
