#include "TopMass_13TeV_PseudoExp/PseudoExperimentsMaster.h"

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

  if(argc != 12){
    
    cout << "\t" << endl;
    cout << "ERROR: Number of input variables is wrong!!!   ===> " << argc << endl;
    cout << "\t" << endl;
    
    return 1;
    
  }
  else{
    
  }
  
  string ParameterFolder = argv[1];
  string InputFile       = argv[2];
  string OutputFolder    = argv[3];
  string FileString      = argv[4];
  string TreeName        = argv[5];
  string WeightNameNom   = argv[6];
  string WeightNameSys   = argv[7];
  int    iWeightPos      = TString(argv[8]).Atoi();
  int    iPE             = TString(argv[9]).Atoi();
  int    FitDimension    = TString(argv[10]).Atoi(); // can be 1,2,3 depending on if we fit only mtop, or mtop+JSF, or mtop+JSF+bJSF
  int    IsLeptonJets    = TString(argv[11]).Atoi();

  PseudoExperimentsMaster *fPE = new PseudoExperimentsMaster(InputFile, OutputFolder, FileString, TreeName, WeightNameNom, WeightNameSys, iWeightPos, ParameterFolder, FitDimension, IsLeptonJets);
  fPE -> ReadInputFile();
  fPE -> RunAllPseudoExperiments(iPE);

  return 0;
}

