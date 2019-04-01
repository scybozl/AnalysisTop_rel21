#include "TString.h"
#include "TMinuitMinimizer.h"
#include "TMatrixD.h"

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
#include <omp.h>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "Math/Functor.h"

#include "TopMass_13TeV_PseudoExp/PseudoExperimentsFit.h"
#include "TopMass_13TeV_PseudoExp/PseudoExperimentsMaster.h"

#include "TopMass_13TeV_Parameterization/FitInfo.h" // Fit Functions definitions 

using namespace std;



PseudoExperimentsMaster::PseudoExperimentsMaster(string InputFile, string OutputFolder, string FileString, string TreeName, string WeightNameNom, string WeightNameSys, int WeightPos, string ParameterFolder, int Dim, bool IsLeptonJets)
{
  
  std::cout << "Here constructor!" << std::endl;
  
  fInputFile       = InputFile;
  fOutputFolder    = OutputFolder;
  fFileString      = FileString;
  fTreeName        = TreeName;
  fWeightNameNom   = WeightNameNom;
  fWeightNameSys   = WeightNameSys;
  fParameterFolder = ParameterFolder;
  fFitDimension    = Dim;
  fIsLeptonJets    = IsLeptonJets;
  fWeightPos       = WeightPos;

  fRandom        = new TRandom3(0);

  outTree = new TTree("PETree", "PETree");

  outTree -> Branch("mtop",       &out_mtop);
  outTree -> Branch("mtop_e",     &out_mtop_e);
  outTree -> Branch("mtop_eh",    &out_mtop_eh);
  outTree -> Branch("mtop_el",    &out_mtop_el);

  outTree -> Branch("jsf",        &out_jsf);
  outTree -> Branch("jsf_e",      &out_jsf_e);
  outTree -> Branch("jsf_eh",     &out_jsf_eh);
  outTree -> Branch("jsf_el",     &out_jsf_el);

  outTree -> Branch("bjsf",       &out_bjsf);
  outTree -> Branch("bjsf_e",     &out_bjsf_e);
  outTree -> Branch("bjsf_eh",    &out_bjsf_eh);
  outTree -> Branch("bjsf_el",    &out_bjsf_el);

  outTree -> Branch("NDim",       &NDim);
  outTree -> Branch("Converged",  &Converged);
  
  outTree -> Branch("sum_PE",     &sum_PE);
  outTree -> Branch("sum_PE2",    &sum_PE2);

  outTree -> Branch("yield_lumi", &yield_lumi);
  outTree -> Branch("yield_mc",   &yield_mc);


}


PseudoExperimentsMaster::~PseudoExperimentsMaster()
{

}


std::vector<int> PseudoExperimentsMaster::ReturnListDSID(std::vector<int> FullDSIDList)
{

  std::cout << "Count DSIDs" << std::endl;

  vector<int> v = FullDSIDList;
  
  vector<int>::iterator ip; 
  
  std::sort(v.begin(), v.end()); 

  ip = std::unique(v.begin(), v.end()); 
  v.resize(std::distance(v.begin(), ip)); 
  
  std::cout << "Done counting" << std::endl;

  // Displaying the vector after applying std::unique 
  for (ip = v.begin(); ip != v.end(); ++ip) { 
    cout << *ip << " "; 
  } 

  
  return v;

}


void PseudoExperimentsMaster::ReadInputFile()
{

  std::cout << "Read input file to run PE on..." << "\t" << fTreeName.c_str() << "\t" << fInputFile.c_str() << std::endl;

  TChain *inTree = new TChain(fTreeName.c_str());
  inTree -> Add(fInputFile.c_str());

  Float_t         weight_mc;
  Float_t         weight_pileup;
  Float_t         weight_leptonSF;
  Float_t         weight_bTagSF_77;
  Float_t         weight_jvt;
  vector<double>  *tma_klfitter_mtop_param;
  vector<double>  *tma_original_mw;
  vector<double>  *tma_original_rbq;
  Double_t         tma_mlb_minmaxavg;
  Float_t          NormFactor;
  Int_t            mcChannelNumber;

  Float_t weight_nom;
  Float_t weight_sys;
  vector<float> *weight_sys_vec;

  tma_klfitter_mtop_param = 0;
  tma_original_mw         = 0;
  tma_original_rbq        = 0;

  inTree -> SetBranchAddress("NormFactor",              &NormFactor);
  
  if(fIsLeptonJets){
    inTree -> SetBranchAddress("tma_klfitter_mtop_param", &tma_klfitter_mtop_param);
    inTree -> SetBranchAddress("tma_original_mw",         &tma_original_mw);
    inTree -> SetBranchAddress("tma_original_rbq",        &tma_original_rbq);
  }
  else{
    inTree -> SetBranchAddress("tma_mlb_minmaxavg",       &tma_mlb_minmaxavg);
  }

  inTree -> SetBranchAddress("weight_leptonSF",         &weight_leptonSF);
  inTree -> SetBranchAddress("weight_jvt",              &weight_jvt);
  inTree -> SetBranchAddress("weight_bTagSF_MV2c10_77", &weight_bTagSF_77);
  inTree -> SetBranchAddress("weight_mc",               &weight_mc);
  inTree -> SetBranchAddress("weight_pileup",           &weight_pileup);
  inTree -> SetBranchAddress("mcChannelNumber",         &mcChannelNumber);

  std::cout << "Hier 1 = " << fWeightNameNom.c_str() << "\t" << fWeightNameSys << std::endl;

  if(fWeightNameNom != "nominal" && fWeightNameSys != "nominal"){

    std::cout << "Hier 2" << std::endl;
    
    if(fWeightNameNom != "weight_bTagSF_MV2c10_77" || fWeightPos == -1){

      std::cout << "Hier 3" << std::endl;

      inTree -> SetBranchAddress(fWeightNameSys.c_str(), &weight_sys);
    }
    else{

      std::cout << "Hier 4" << std::endl;

      weight_sys_vec = 0;
      inTree -> SetBranchAddress(fWeightNameSys.c_str(), &weight_sys_vec);
    }
  }
  else{

    // for ISR and FSR weights
    if(fWeightNameNom == "nominal" && fWeightNameSys != "nominal"){
    
      inTree -> SetBranchAddress(fWeightNameSys.c_str(), &weight_sys);

    }
    else{
      weight_nom = 1.0;
      weight_sys = 1.0;
    }

  }

  int nEvents = inTree -> GetEntries();   std::cout << nEvents << std::endl;

  std::vector<int> FullDSIDList;

  // loop once to get full list of DSIDs 
  for(int iEvent = 0; iEvent < nEvents; ++iEvent){
    inTree -> GetEntry(iEvent);
    FullDSIDList.push_back(mcChannelNumber);
  }

  std::vector<int> SignalDSID_List = ReturnListDSID(FullDSIDList);

  std::cout << "Number of different DSIDs = " << SignalDSID_List.size() << std::endl;

  // now that we know how many different DSIDs we have in the root file, we can start making a structure for each DSID
  // std::vector<PEInput_Per_DSIDs> SignalInfo

  for(unsigned int iDSID = 0; iDSID < SignalDSID_List.size(); iDSID++){
    PEInput_Per_DSIDs helpInput;
    helpInput.DSID = SignalDSID_List[iDSID];
    helpInput.fSumW_All    = 0.0;
    helpInput.fSumW_NoLumi = 0.0;
    helpInput.fSumW_MCPU   = 0.0;

    fSignalInfo.push_back(helpInput);

  }

  for(unsigned int iDSID = 0; iDSID < fSignalInfo.size(); iDSID++){ 

    for(int iEvent = 0; iEvent < nEvents; ++iEvent){
      
      inTree -> GetEntry(iEvent);
      
      if(mcChannelNumber != fSignalInfo[iDSID].DSID)
	continue;

      // not elegant but the only way it works:
      if(fWeightNameNom == "weight_bTagSF_MV2c10_77")
	weight_nom = weight_bTagSF_77;
      else if(fWeightNameNom == "weight_jvt")
        weight_nom = weight_jvt;
      else if(fWeightNameNom == "weight_pileup")
        weight_nom = weight_pileup;
      else if(fWeightNameNom == "weight_leptonSF")
        weight_nom = weight_leptonSF;
      else
	weight_nom = 1.0;

      double sign = 1.0;
      
      // happens super-rarely, but occasionally happens
      if(weight_nom == 0)
	continue;

      if(weight_mc < 0.0) sign = -1.0; // check for dilepton samples ===> 
      
      double mult_weight = 0;
      
      if(fWeightNameNom != "weight_bTagSF_MV2c10_77" || fWeightPos == -1)
	mult_weight = weight_sys/weight_nom;
      else
	mult_weight = weight_sys_vec -> at(fWeightPos)/weight_nom;

      //      std::cout << weight_mc << "\t" << mult_weight << "\t" << weight_sys_vec -> at(fWeightPos)  << "\t" << weight_nom << std::endl;

      Float_t Weight     = weight_leptonSF*weight_jvt*weight_bTagSF_77*weight_mc*weight_pileup*NormFactor*mult_weight;
      Float_t WeightLumi = weight_leptonSF*weight_jvt*weight_bTagSF_77*weight_pileup*sign*mult_weight; // have 1.8 M events, expect 488 k events
      Float_t WeightSF   = weight_mc;

      // for ISR and FSR weights that were stored multiplicative  
      if(fWeightNameNom == "nominal" && fWeightNameSys != "nominal"){
     
	Weight     = weight_leptonSF*weight_jvt*weight_bTagSF_77*weight_mc*weight_pileup*NormFactor*weight_sys;
	WeightLumi = weight_leptonSF*weight_jvt*weight_bTagSF_77*weight_pileup*sign*weight_sys;
	WeightSF   = weight_mc*weight_sys;
	
      }
      
      //      std::cout << Weight << "\t" << WeightLumi << std::endl;

      if(isnan(WeightSF) || WeightSF == 0) std::cout << iEvent << "\t" << WeightSF << "\t" << NormFactor << "\t" << weight_leptonSF << "\t" << weight_jvt << "\t" << weight_bTagSF_77 << "\t" << mult_weight << std::endl;
      
      //    if(nominal == 0) continue;


      //      std::cout << Weight << "\t" << weight_leptonSF*weight_jvt*weight_bTagSF_77*weight_mc*weight_pileup*NormFactor << std::endl;
      
      std::vector<float> help;
      help.push_back(Weight);
      help.push_back(WeightLumi);
      help.push_back(WeightSF);
      
      bool IsInRange = true;

      if(fIsLeptonJets){

	/*	if(tma_klfitter_mtop_param -> at(0) < fitmin_mtop || tma_klfitter_mtop_param -> at(0) > fitmax_mtop)
	  IsInRange = false;
	
	if(tma_original_mw -> at(0) < fitmin_mw || tma_original_mw -> at(0) > fitmax_mw)
          IsInRange = false;

	if(tma_original_rbq -> at(0) < fitmin_rbq || tma_original_rbq -> at(0) > fitmax_rbq)
	IsInRange = false;*/

      }
      else{

	if(tma_mlb_minmaxavg/1000.0 < fitmin_mlb || tma_mlb_minmaxavg/1000.0 > fitmax_mlb)
          IsInRange = false;

      }

      if(fIsLeptonJets){

	help.push_back(tma_klfitter_mtop_param -> at(0));
	help.push_back(tma_original_mw -> at(0));
	help.push_back(tma_original_rbq -> at(0));

      }
      else{

	help.push_back(tma_mlb_minmaxavg/1000.0);
	// std::cout << tma_mlb_minmaxavg/1000.0 << std::endl;
      }
      
      if(IsInRange){

	fSignalInfo[iDSID].PEInput.push_back(help);
      
	fSignalInfo[iDSID].fSumW_All    += Weight;
	fSignalInfo[iDSID].fSumW_NoLumi += WeightLumi;
	fSignalInfo[iDSID].fSumW_MCPU   += WeightSF;
      
      }

    }
    
  }

  std::cout << "==============================================================" << std::endl;

  for(unsigned int iDSID = 0; iDSID < fSignalInfo.size(); iDSID++){

    std::cout << iDSID << "\t" << fSignalInfo[iDSID].DSID << "\t" << fSignalInfo[iDSID].PEInput.size() << std::endl;

  }  

  inTree->Delete();

  /*
  std::cout << "==============================================================" << std::endl;
  std::cout << fTTbarInfo.size() << std::endl;
  std::cout << "SumW All ttbar     = " << fSumW_All_ttbar    << std::endl;
  std::cout << "SumW NoLumi ttbar  = " << fSumW_NoLumi_ttbar << std::endl;
  std::cout << "SumW MCPU ttbar    = " << fSumW_MCPU_ttbar   << std::endl;
  */

}


void PseudoExperimentsMaster::RunAllPseudoExperiments(int NrPE)
{

  std::cout << "Run " << NrPE << " pseudo-experiments! " << std::endl;

  for(unsigned int iDSID = 0; iDSID < fSignalInfo.size(); iDSID++){
    
    yield_lumi.push_back(0);
    yield_mc.push_back(0);

    for(unsigned int iEntry = 0; iEntry < fSignalInfo[iDSID].PEInput.size(); ++iEntry){                                                                                                          
                                                                                                                                                                                                          
      yield_lumi[iDSID] += fSignalInfo[iDSID].PEInput[iEntry][0]; // store full event yield                                                                                                            
      yield_mc[iDSID]   += fSignalInfo[iDSID].PEInput[iEntry][1];                                                                                                                                     
           
      if(NrPE == 1)
	fFitInfoTmp.push_back(fSignalInfo[iDSID].PEInput[iEntry]);
                                                                                                                                                                                                    
    }

  }

  /*for(unsigned int iEntry = 0; iEntry < fTTbarInfo.size(); ++iEntry){

    yield_lumi += fTTbarInfo[iEntry][0]; // store full event yield
    yield_mc   += fTTbarInfo[iEntry][1];

    }*/

  if(NrPE > 1){

    for(int iPE = 0; iPE < NrPE; ++iPE){

      std::cout << "==============================================================" << std::endl;
      std::cout << "Run Pseudo-Experiment No. " << iPE << std::endl;
      
      DrawPseudoExperiment(iPE, NrPE);
      
    }
  }
  else{

    UnbinnedLikelihoodFit(true, NrPE==1);
    
  }
  
  
}


void PseudoExperimentsMaster::DrawPseudoExperiment(int iPE, int NrPE)
{

  // initialize always with a fix seed so that the results are reproducible!
  fRandom -> SetSeed(1234567+iPE);

  // clear vector and fill it again
  fFitInfoTmp.clear();

  // here we now need to loop over all DSIDs and make sure that we pull as many events as expected in the data lumi per DSID
  for(unsigned int iDSID = 0; iDSID < fSignalInfo.size(); iDSID++){

    float SumW_local = 0;
    
    sum_PE  = 0;
    sum_PE2 = 0;
    
    while(SumW_local < fSignalInfo[iDSID].fSumW_All){
      
      int position = gRandom -> Uniform(0, fSignalInfo[iDSID].PEInput.size());
      
      fFitInfoTmp.push_back(fSignalInfo[iDSID].PEInput[position]);
      
      double weight = fSignalInfo[iDSID].PEInput[position][1]; // FinalWeight/LumiWeight
      
      SumW_local += weight;
      
      sum_PE  += weight;
      sum_PE2 += weight*weight;
      
    }
    
  }

  std::cout << "Len Tmp Vector = " << fFitInfoTmp.size() << "\t" << sum_PE <<  std::endl;

  UnbinnedLikelihoodFit(iPE==NrPE-1, NrPE==1);

}

void PseudoExperimentsMaster::UnbinnedLikelihoodFit(bool last, bool OnePE)
{

  TMinuitMinimizer *aMinuit = new TMinuitMinimizer("fit", 3);
  aMinuit->SetPrintLevel(1000);

  std::cout << "UnbinnedLikelihoodFit OnePE = " << OnePE << std::endl;

  // ok need to change this, does not make sense to read this for each PE
  PseudoExperimentsFit *help = new PseudoExperimentsFit(fParameterFolder, OnePE, fFitDimension, fIsLeptonJets);
  help -> ReadParameters(fParameterFolder);
  help -> SetFitVector(fFitInfoTmp);

  // NOTE: NEED TO CHANGE THIS CODE BELOW AS SOON AS WE ADD BKG!!!!

  if(fFileString == "171p0_1p0_1p0_1PE_1D"){
    if(fIsLeptonJets)
      help -> PrepareOverlayPlot(171.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
    else
      help -> PrepareOverlayPlot_Dil(171.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
  }
  if(fFileString == "172p0_1p0_1p0_1PE_1D"){
    if(fIsLeptonJets)
      help -> PrepareOverlayPlot(172.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
    else
      help -> PrepareOverlayPlot_Dil(172.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
  }
  if(fFileString == "172p5_1p0_1p0_1PE_1D"){
    if(fIsLeptonJets)
      help -> PrepareOverlayPlot(172.5, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
    else
      help -> PrepareOverlayPlot_Dil(172.5, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
  }
  if(fFileString == "173p0_1p0_1p0_1PE_1D"){
    if(fIsLeptonJets)
      help -> PrepareOverlayPlot(173.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
    else
      help -> PrepareOverlayPlot_Dil(173.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
  }
  if(fFileString == "174p0_1p0_1p0_1PE_1D"){
    if(fIsLeptonJets)
      help -> PrepareOverlayPlot(174.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);
    else
      help -> PrepareOverlayPlot_Dil(174.0, 1.0, 1.0, fOutputFolder+"/Overlay", fFileString);

  }

  ROOT::Math::Functor f(help, &PseudoExperimentsFit::FitFCN, 3);

  // set minimization function                                                                                                                                                                                            
  aMinuit -> SetFunction(f);

  aMinuit -> SetVariable(0, "mtop", 180.0, 0.01);
  aMinuit -> SetVariable(1, "jsf",    1.0, 0.01);
  aMinuit -> SetVariable(2, "bjsf",   1.0, 0.01);

  //aMinuit -> SetLimitedVariable( 0, "mtop", 180.0, 20.00, 150.0, 190.0);
  //aMinuit -> SetLimitedVariable( 1, "jsf" ,   1.1,  0.02,   0.8,   1.2);
  //aMinuit -> SetLimitedVariable( 2, "bjsf",   1.1,  0.02,   0.8,   1.2);

  //  rmin->mnparm( 2, "mtop", 172.5, 0.05,0, 0, ierror );


  if(fFitDimension == 1)
    aMinuit -> FixVariable(1);
  if(fFitDimension != 3)
    aMinuit -> FixVariable(2);

  Converged = aMinuit -> Minimize();
  aMinuit -> Hesse();
  aMinuit -> PrintResults();

  const double *P = aMinuit -> X();
  const double *E = aMinuit -> Errors();

  out_mtop   = P[0];
  out_mtop_e = E[0];
  out_jsf    = P[1];
  out_jsf_e  = E[1];
  out_bjsf   = P[2];
  out_bjsf_e = E[2];

  //  GetMinosError (unsigned int ivar, double &errLow, double &errUp, int option=0)
  aMinuit -> GetMinosError(0, out_mtop_el, out_mtop_eh);
  aMinuit -> GetMinosError(1, out_jsf_el , out_jsf_eh);
  aMinuit -> GetMinosError(2, out_bjsf_el, out_bjsf_eh);

  NDim       = aMinuit -> NDim();
  
  outTree -> Fill();

  if(last){

    TFile *outFile = new TFile((fOutputFolder+"/"+fFileString+".root").c_str(), "RECREATE");

    outTree -> Write();
    outFile -> Close();

  }

  delete help;
  delete aMinuit;
 
  
}
