//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct  4 11:38:43 2017 by ROOT version 6.04/16
// from TTree t2/a new tree for top mass
// found on file: InputSamples/JSF1.0/Merged_Tree_ttbar.root
//////////////////////////////////////////////////////////

#ifndef PETreeReader_h
#define PETreeReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

#include <vector>
#include "TLorentzVector.h"

using namespace std;

class PETreeReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         FinalWeight;
   Float_t         LumiWeight;
   Double_t        nEvents;
   Double_t        nBTags;
   Double_t        jet_n;
   Double_t        met_met;
   Double_t        met_phi;
   Double_t        mu_n;
   Double_t        mu_pt;
   Double_t        mu_eta;
   Double_t        mu_phi;
   Double_t        mu_charge;
   Double_t        el_n;
   Double_t        el_pt;
   Double_t        el_eta;
   Double_t        el_phi;
   Double_t        el_charge;
   Double_t        jet0_pt;
   Double_t        jet0_eta;
   Double_t        jet0_phi;
   Double_t        jet1_pt;
   Double_t        jet1_eta;
   Double_t        jet1_phi;
   Double_t        jet2_pt;
   Double_t        jet2_eta;
   Double_t        jet2_phi;
   Double_t        jet3_pt;
   Double_t        jet3_eta;
   Double_t        jet3_phi;
   Double_t        jet_pt;
   Double_t        jet_eta;
   Double_t        jet_phi;
   Double_t        jet_mv2c10;
   Double_t        jet_jvt;
   Double_t        jet_truthflav;
   Double_t        mtw;
   Double_t        met_plus_mtw;
   Double_t        klf_original_Whad_m;
   Double_t        klf_original_Rbq_reco;
   Double_t        klf_original_mlb_reco;
   Double_t        klf_mtop_param;
   Double_t        klf_topLep_pt;
   Double_t        klf_topLep_eta;
   Double_t        klf_topLep_phi;
   Double_t        klf_topLep_E;
   Double_t        klf_topLep_m;
   Double_t        klf_topHad_pt;
   Double_t        klf_topHad_eta;
   Double_t        klf_topHad_phi;
   Double_t        klf_topHad_E;
   Double_t        klf_topHad_m;
   Double_t        klf_ttbar_pt;
   Double_t        klf_ttbar_eta;
   Double_t        klf_ttbar_phi;
   Double_t        klf_ttbar_E;
   Double_t        klf_ttbar_m;
   Double_t        klf_Wlep_pt;
   Double_t        klf_Wlep_eta;
   Double_t        klf_Wlep_phi;
   Double_t        klf_Wlep_m;
   Double_t        klf_Whad_pt;
   Double_t        klf_Whad_eta;
   Double_t        klf_Whad_phi;
   Double_t        klf_Whad_m;
   Double_t        klf_blep_pt;
   Double_t        klf_blep_eta;
   Double_t        klf_blep_phi;
   Double_t        klf_blep_m;
   Double_t        klf_bhad_pt;
   Double_t        klf_bhad_eta;
   Double_t        klf_bhad_phi;
   Double_t        klf_bhad_m;
   Double_t        klf_lq1_pt;
   Double_t        klf_lq1_eta;
   Double_t        klf_lq1_phi;
   Double_t        klf_lq1_m;
   Double_t        klf_lq2_pt;
   Double_t        klf_lq2_eta;
   Double_t        klf_lq2_phi;
   Double_t        klf_lq2_m;
   Double_t        klf_LL;
   Double_t        klf_eventProbability;
   Double_t        klf_minuitDidNotConverge;
   Double_t        klf_window_Whad_m;
   Double_t        klf_window_Rbq_reco;
   Double_t        klf_window_mlb_reco;
   Double_t        klf_mtop_window;

   // List of branches
   TBranch        *b_FinalWeight;   //!
   TBranch        *b_LumiWeight;
   TBranch        *b_nEvents;   //!
   TBranch        *b_nBTags;   //!
   TBranch        *b_jet_n;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_mu_n;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_el_n;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_jet0_pt;   //!
   TBranch        *b_jet0_eta;   //!
   TBranch        *b_jet0_phi;   //!
   TBranch        *b_jet1_pt;   //!
   TBranch        *b_jet1_eta;   //!
   TBranch        *b_jet1_phi;   //!
   TBranch        *b_jet2_pt;   //!
   TBranch        *b_jet2_eta;   //!
   TBranch        *b_jet2_phi;   //!
   TBranch        *b_jet3_pt;   //!
   TBranch        *b_jet3_eta;   //!
   TBranch        *b_jet3_phi;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_mv2c10;   //!
   TBranch        *b_jet_jvt;   //!
   TBranch        *b_jet_truthflav;   //!
   TBranch        *b_mtw;   //!
   TBranch        *b_met_plus_mtw;   //!
   TBranch        *b_klf_original_Whad_m;   //!
   TBranch        *b_klf_original_Rbq_reco;   //!
   TBranch        *b_klf_original_mlb_reco;   //!
   TBranch        *b_klf_mtop_param;   //!
   TBranch        *b_klf_topLep_pt;   //!
   TBranch        *b_klf_topLep_eta;   //!
   TBranch        *b_klf_topLep_phi;   //!
   TBranch        *b_klf_topLep_E;   //!
   TBranch        *b_klf_topLep_m;   //!
   TBranch        *b_klf_topHad_pt;   //!
   TBranch        *b_klf_topHad_eta;   //!
   TBranch        *b_klf_topHad_phi;   //!
   TBranch        *b_klf_topHad_E;   //!
   TBranch        *b_klf_topHad_m;   //!
   TBranch        *b_klf_ttbar_pt;   //!
   TBranch        *b_klf_ttbar_eta;   //!
   TBranch        *b_klf_ttbar_phi;   //!
   TBranch        *b_klf_ttbar_E;   //!
   TBranch        *b_klf_ttbar_m;   //!
   TBranch        *b_klf_Wlep_pt;   //!
   TBranch        *b_klf_Wlep_eta;   //!
   TBranch        *b_klf_Wlep_phi;   //!
   TBranch        *b_klf_Wlep_m;   //!
   TBranch        *b_klf_Whad_pt;   //!
   TBranch        *b_klf_Whad_eta;   //!
   TBranch        *b_klf_Whad_phi;   //!
   TBranch        *b_klf_Whad_m;   //!
   TBranch        *b_klf_blep_pt;   //!
   TBranch        *b_klf_blep_eta;   //!
   TBranch        *b_klf_blep_phi;   //!
   TBranch        *b_klf_blep_m;   //!
   TBranch        *b_klf_bhad_pt;   //!
   TBranch        *b_klf_bhad_eta;   //!
   TBranch        *b_klf_bhad_phi;   //!
   TBranch        *b_klf_bhad_m;   //!
   TBranch        *b_klf_lq1_pt;   //!
   TBranch        *b_klf_lq1_eta;   //!
   TBranch        *b_klf_lq1_phi;   //!
   TBranch        *b_klf_lq1_m;   //!
   TBranch        *b_klf_lq2_pt;   //!
   TBranch        *b_klf_lq2_eta;   //!
   TBranch        *b_klf_lq2_phi;   //!
   TBranch        *b_klf_lq2_m;   //!
   TBranch        *b_klf_LL;   //!
   TBranch        *b_klf_eventProbability;   //!
   TBranch        *b_klf_minuitDidNotConverge;   //!

   PETreeReader(TTree *tree=0);
   virtual ~PETreeReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef PETreeReader_cxx
PETreeReader::PETreeReader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("InputSamples/JSF1.0/Merged_Tree_ttbar.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("InputSamples/JSF1.0/Merged_Tree_ttbar.root");
      }
      f->GetObject("t2",tree);

   }
   Init(tree);
}

PETreeReader::~PETreeReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PETreeReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PETreeReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void PETreeReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("FinalWeight", &FinalWeight, &b_FinalWeight);
   fChain->SetBranchAddress("LumiWeight",  &LumiWeight,  &b_LumiWeight);
   fChain->SetBranchAddress("nEvents", &nEvents, &b_nEvents);
   fChain->SetBranchAddress("nBTags", &nBTags, &b_nBTags);
   fChain->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("mu_n", &mu_n, &b_mu_n);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("el_n", &el_n, &b_el_n);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("jet0_pt", &jet0_pt, &b_jet0_pt);
   fChain->SetBranchAddress("jet0_eta", &jet0_eta, &b_jet0_eta);
   fChain->SetBranchAddress("jet0_phi", &jet0_phi, &b_jet0_phi);
   fChain->SetBranchAddress("jet1_pt", &jet1_pt, &b_jet1_pt);
   fChain->SetBranchAddress("jet1_eta", &jet1_eta, &b_jet1_eta);
   fChain->SetBranchAddress("jet1_phi", &jet1_phi, &b_jet1_phi);
   fChain->SetBranchAddress("jet2_pt", &jet2_pt, &b_jet2_pt);
   fChain->SetBranchAddress("jet2_eta", &jet2_eta, &b_jet2_eta);
   fChain->SetBranchAddress("jet2_phi", &jet2_phi, &b_jet2_phi);
   fChain->SetBranchAddress("jet3_pt", &jet3_pt, &b_jet3_pt);
   fChain->SetBranchAddress("jet3_eta", &jet3_eta, &b_jet3_eta);
   fChain->SetBranchAddress("jet3_phi", &jet3_phi, &b_jet3_phi);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_mv2c10", &jet_mv2c10, &b_jet_mv2c10);
   fChain->SetBranchAddress("jet_jvt", &jet_jvt, &b_jet_jvt);
   fChain->SetBranchAddress("jet_truthflav", &jet_truthflav, &b_jet_truthflav);
   fChain->SetBranchAddress("mtw", &mtw, &b_mtw);
   fChain->SetBranchAddress("met_plus_mtw", &met_plus_mtw, &b_met_plus_mtw);
   fChain->SetBranchAddress("klf_original_Whad_m", &klf_original_Whad_m, &b_klf_original_Whad_m);
   fChain->SetBranchAddress("klf_original_Rbq_reco", &klf_original_Rbq_reco, &b_klf_original_Rbq_reco);
   fChain->SetBranchAddress("klf_original_mlb_reco", &klf_original_mlb_reco, &b_klf_original_mlb_reco);
   fChain->SetBranchAddress("klf_mtop_param", &klf_mtop_param, &b_klf_mtop_param);
   fChain->SetBranchAddress("klf_topLep_pt", &klf_topLep_pt, &b_klf_topLep_pt);
   fChain->SetBranchAddress("klf_topLep_eta", &klf_topLep_eta, &b_klf_topLep_eta);
   fChain->SetBranchAddress("klf_topLep_phi", &klf_topLep_phi, &b_klf_topLep_phi);
   fChain->SetBranchAddress("klf_topLep_E", &klf_topLep_E, &b_klf_topLep_E);
   fChain->SetBranchAddress("klf_topLep_m", &klf_topLep_m, &b_klf_topLep_m);
   fChain->SetBranchAddress("klf_topHad_pt", &klf_topHad_pt, &b_klf_topHad_pt);
   fChain->SetBranchAddress("klf_topHad_eta", &klf_topHad_eta, &b_klf_topHad_eta);
   fChain->SetBranchAddress("klf_topHad_phi", &klf_topHad_phi, &b_klf_topHad_phi);
   fChain->SetBranchAddress("klf_topHad_E", &klf_topHad_E, &b_klf_topHad_E);
   fChain->SetBranchAddress("klf_topHad_m", &klf_topHad_m, &b_klf_topHad_m);
   fChain->SetBranchAddress("klf_ttbar_pt", &klf_ttbar_pt, &b_klf_ttbar_pt);
   fChain->SetBranchAddress("klf_ttbar_eta", &klf_ttbar_eta, &b_klf_ttbar_eta);
   fChain->SetBranchAddress("klf_ttbar_phi", &klf_ttbar_phi, &b_klf_ttbar_phi);
   fChain->SetBranchAddress("klf_ttbar_E", &klf_ttbar_E, &b_klf_ttbar_E);
   fChain->SetBranchAddress("klf_ttbar_m", &klf_ttbar_m, &b_klf_ttbar_m);
   fChain->SetBranchAddress("klf_Wlep_pt", &klf_Wlep_pt, &b_klf_Wlep_pt);
   fChain->SetBranchAddress("klf_Wlep_eta", &klf_Wlep_eta, &b_klf_Wlep_eta);
   fChain->SetBranchAddress("klf_Wlep_phi", &klf_Wlep_phi, &b_klf_Wlep_phi);
   fChain->SetBranchAddress("klf_Wlep_m", &klf_Wlep_m, &b_klf_Wlep_m);
   fChain->SetBranchAddress("klf_Whad_pt", &klf_Whad_pt, &b_klf_Whad_pt);
   fChain->SetBranchAddress("klf_Whad_eta", &klf_Whad_eta, &b_klf_Whad_eta);
   fChain->SetBranchAddress("klf_Whad_phi", &klf_Whad_phi, &b_klf_Whad_phi);
   fChain->SetBranchAddress("klf_Whad_m", &klf_Whad_m, &b_klf_Whad_m);
   fChain->SetBranchAddress("klf_blep_pt", &klf_blep_pt, &b_klf_blep_pt);
   fChain->SetBranchAddress("klf_blep_eta", &klf_blep_eta, &b_klf_blep_eta);
   fChain->SetBranchAddress("klf_blep_phi", &klf_blep_phi, &b_klf_blep_phi);
   fChain->SetBranchAddress("klf_blep_m", &klf_blep_m, &b_klf_blep_m);
   fChain->SetBranchAddress("klf_bhad_pt", &klf_bhad_pt, &b_klf_bhad_pt);
   fChain->SetBranchAddress("klf_bhad_eta", &klf_bhad_eta, &b_klf_bhad_eta);
   fChain->SetBranchAddress("klf_bhad_phi", &klf_bhad_phi, &b_klf_bhad_phi);
   fChain->SetBranchAddress("klf_bhad_m", &klf_bhad_m, &b_klf_bhad_m);
   fChain->SetBranchAddress("klf_lq1_pt", &klf_lq1_pt, &b_klf_lq1_pt);
   fChain->SetBranchAddress("klf_lq1_eta", &klf_lq1_eta, &b_klf_lq1_eta);
   fChain->SetBranchAddress("klf_lq1_phi", &klf_lq1_phi, &b_klf_lq1_phi);
   fChain->SetBranchAddress("klf_lq1_m", &klf_lq1_m, &b_klf_lq1_m);
   fChain->SetBranchAddress("klf_lq2_pt", &klf_lq2_pt, &b_klf_lq2_pt);
   fChain->SetBranchAddress("klf_lq2_eta", &klf_lq2_eta, &b_klf_lq2_eta);
   fChain->SetBranchAddress("klf_lq2_phi", &klf_lq2_phi, &b_klf_lq2_phi);
   fChain->SetBranchAddress("klf_lq2_m", &klf_lq2_m, &b_klf_lq2_m);
   fChain->SetBranchAddress("klf_LL", &klf_LL, &b_klf_LL);
   fChain->SetBranchAddress("klf_eventProbability", &klf_eventProbability, &b_klf_eventProbability);
   fChain->SetBranchAddress("klf_minuitDidNotConverge", &klf_minuitDidNotConverge, &b_klf_minuitDidNotConverge);
   fChain->SetBranchAddress("klf_window_Whad_m", &klf_window_Whad_m, &b_klf_window_Whad_m);
   fChain->SetBranchAddress("klf_window_Rbq_reco", &klf_window_Rbq_reco, &b_klf_window_Rbq_reco);
   fChain->SetBranchAddress("klf_window_mlb_reco", &klf_window_mlb_reco, &b_klf_window_mlb_reco);
   fChain->SetBranchAddress("klf_mtop_window", &klf_mtop_window, &b_klf_mtop_window);
   Notify();
}

Bool_t PETreeReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PETreeReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PETreeReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef PETreeReader_cxx
