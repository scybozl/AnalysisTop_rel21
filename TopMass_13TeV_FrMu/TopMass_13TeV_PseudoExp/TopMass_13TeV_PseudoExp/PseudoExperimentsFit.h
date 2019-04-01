#ifndef PseudoExperimentsFit_H_
#define PseudoExperimentsFit_H_

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

#include "TopMass_13TeV_PseudoExp/PETreeReader.h"

using namespace std;

class PseudoExperimentsFit
{

 public:

  
  PseudoExperimentsFit(std::string, bool, int, bool);
  virtual ~PseudoExperimentsFit();
  
  void ReadParameters(std::string);
  double FitFCN(const Double_t *par) const;
  void SetFitVector(std::vector<std::vector<float> > help) {fTTbarInfoTmp = help;};
  void PrepareOverlayPlot(double, double, double, std::string, std::string);
  void PrepareOverlayPlot_Dil(double, double, double, std::string, std::string);
  void MakeOverlayPlot(std::string, TF1*, TH1D *, TH1D *, double, double, std::string, std::string);

 private:
  
  TF1 *fmtop,*fmw,*frbq,*fmtop_dil;

  std::string fParameterFile;

  int fFitDimension;

  PETreeReader *fFlatTree;

  std::vector<std::vector<float> > fTTbarInfo;
  std::vector<std::vector<float> > fTTbarInfoTmp;

  bool fRunOnePE;
  bool fIsLeptonJets;

};


#endif
