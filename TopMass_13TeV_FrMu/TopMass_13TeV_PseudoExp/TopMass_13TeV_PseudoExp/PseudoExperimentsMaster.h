#ifndef PseudoExperimentsMaster_H_
#define PseudoExperimentsMaster_H_

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

#include "TopMass_13TeV_PseudoExp/PETreeReader.h"

using namespace std;


struct PEInput_Per_DSIDs{
  int DSID;
  std::vector<std::vector<float> > PEInput;
  float fSumW_All;
  float fSumW_NoLumi;
  float fSumW_MCPU;
};

class PseudoExperimentsMaster
{

 public:

  
  PseudoExperimentsMaster(std::string, std::string, std::string, std::string, std::string, std::string, int, std::string, int, bool);
  virtual ~PseudoExperimentsMaster();
  
  void ReadInputFile();
  void DrawPseudoExperiment(int, int);
  void RunAllPseudoExperiments(int);
  void SetFitVector(std::vector<std::vector<float> > help) {fFitInfoTmp = help;};
  void UnbinnedLikelihoodFit(bool, bool OnePE=false);
  std::vector<int> ReturnListDSID(std::vector<int> FullDSIDList);

 private:
  
  TF1 *fmtop,*fmw,*frbq,*fmtop_dil;

  std::string fInputFile;
  std::string fOutputFolder;
  std::string fFileString;
  std::string fTreeName;
  std::string fWeightNameNom;
  std::string fWeightNameSys;
  std::string fParameterFolder;


  int fWeightPos;
  int fFitDimension;

  PETreeReader *fFlatTree;

  std::vector<PEInput_Per_DSIDs> fSignalInfo;

  //  std::vector<std::vector<float> > fTTbarInfo;
  std::vector<std::vector<float> > fFitInfoTmp;
  std::vector<std::vector<float> > fSignalInfoTmp;
  std::vector<std::vector<float> > fBkgInfoTmp;

  //  float fSumW_All_ttbar;     // consider all weights
  //  float fSumW_NoLumi_ttbar;  // consider everything except lumi weight
  //  float fSumW_MCPU_ttbar;    // consider only MC and PU weights

  TRandom3 *fRandom;

  TFile *outFile;
  TTree *outTree;

  // variables for output tree
  double out_mtop,   out_mtop_e, out_mtop_el, out_mtop_eh;
  double out_jsf,    out_jsf_e,  out_jsf_el,  out_jsf_eh;
  double out_bjsf,   out_bjsf_e, out_bjsf_el, out_bjsf_eh;
  double sum_PE,     sum_PE2;
  std::vector<double> yield_lumi, yield_mc;

  int NDim;
  int Converged;

  bool fIsLeptonJets;

};


#endif
