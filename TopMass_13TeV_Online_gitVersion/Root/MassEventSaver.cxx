/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
*/

#include "TopMass_13TeV_Online/MassEventSaver.h"
#include "TopMass_13TeV_Online/NeutrinoWeighter.h"
#include "TopEvent/Event.h"
#include "TopEventSelectionTools/TreeManager.h"
#include "TopParticleLevel/ParticleLevelEvent.h"
#include "TopConfiguration/TopConfig.h"

#include <TRandom3.h>
#include "TopEvent/EventTools.h"


namespace top{
  ///-- Construcutor --///
  MassEventSaver::MassEventSaver() :
    m_tma_nbjets_85(0.),
    m_tma_nbjets_77(0.),
    m_tma_nbjets_70(0.),
    m_tma_nbjets_60(0.),
    m_tma_njets(0.),
    m_tma_etdr(0.),
    m_tma_met(0.),
    m_tma_met_ex(0.),
    m_tma_met_ey(0.),
    m_tma_met_phi(0.),
    m_tma_mlb_minavg(0.),
    m_tma_mlb_minavglow(0.),
    m_tma_mlb_minavghigh(0.),
    m_tma_mlb_minmax(0.),
    m_tma_mlb_minmaxlow(0.),
    m_tma_mlb_minmaxavg(0.),
    m_tma_pTlb_1(0.),
    m_tma_pTlb_2(0.),
    m_tma_dRlb_1(0.),
    m_tma_dRlb_2(0.),
    m_tma_mll(0.),
    m_tma_pTll(0.),
    m_tma_dRll(0.),
    m_tma_mbb(0.),
    m_tma_pTbb(0.),
    m_tma_dRbb(0.),
    m_tma_Rbq_avgLJ(0.),
    m_tma_Rbq_leadLJ(0.),
    m_klf_mtop_param(0.),
    m_klf_orig_mw(0.),
    m_klf_orig_rbq(0.),
    m_tma_matchingFlag(-1)
  {
  }
  
  ///-- initialize - done once at the start of a job before the loop over events --///
  void MassEventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches)
{
    ///-- Let the base class do all the hard work --///
    ///-- It will setup TTrees for each systematic with a standard set of variables --///
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches);

    m_config = config;

    ///-- Loop over the systematic TTrees and add the custom variables --///
    for (auto systematicTree : treeManagers()) {

      systematicTree->makeOutputVariable(m_tma_bjet_pt,        "tma_bjet_pt");
      systematicTree->makeOutputVariable(m_tma_bjet_eta,       "tma_bjet_eta");
      systematicTree->makeOutputVariable(m_tma_bjet_phi,       "tma_bjet_phi");
      systematicTree->makeOutputVariable(m_tma_bjet_e,         "tma_bjet_e");
      systematicTree->makeOutputVariable(m_tma_nbjets_85,      "tma_nbjets_85");
      systematicTree->makeOutputVariable(m_tma_nbjets_77,      "tma_nbjets_77");
      systematicTree->makeOutputVariable(m_tma_nbjets_70,      "tma_nbjets_70");
      systematicTree->makeOutputVariable(m_tma_nbjets_60,      "tma_nbjets_60");

      // plots for dilepton channel: reco-level                                                                                                                                                            
      systematicTree->makeOutputVariable(m_tma_etdr,           "tma_etdr");
      systematicTree->makeOutputVariable(m_tma_met,            "tma_met");
      systematicTree->makeOutputVariable(m_tma_met_ex,         "tma_met_ex");
      systematicTree->makeOutputVariable(m_tma_met_ey,         "tma_met_ey");
      systematicTree->makeOutputVariable(m_tma_met_phi,        "tma_met_phi");
      systematicTree->makeOutputVariable(m_tma_mtw,            "tma_mtw");
      systematicTree->makeOutputVariable(m_tma_njets,          "tma_njets");
      systematicTree->makeOutputVariable(m_tma_jet_pt,         "tma_jet_pt");
      systematicTree->makeOutputVariable(m_tma_jet_eta,        "tma_jet_eta");
      systematicTree->makeOutputVariable(m_tma_jet_phi,        "tma_jet_phi");
      systematicTree->makeOutputVariable(m_tma_jet_e,          "tma_jet_e");
      systematicTree->makeOutputVariable(m_tma_mlb_minavg,     "tma_mlb_minavg");
      systematicTree->makeOutputVariable(m_tma_mlb_minavglow,  "tma_mlb_minavglow");
      systematicTree->makeOutputVariable(m_tma_mlb_minavghigh, "tma_mlb_minavghigh");
      systematicTree->makeOutputVariable(m_tma_mlb_minmax,     "tma_mlb_minmax");
      systematicTree->makeOutputVariable(m_tma_mlb_minmaxlow,  "tma_mlb_minmaxlow");
      systematicTree->makeOutputVariable(m_tma_mlb_minmaxavg,  "tma_mlb_minmaxavg");
      systematicTree->makeOutputVariable(m_tma_pTlb_1,         "tma_pTlb_1");
      systematicTree->makeOutputVariable(m_tma_pTlb_2,         "tma_pTlb_2");
      systematicTree->makeOutputVariable(m_tma_dRlb_1,         "tma_dRlb_1");
      systematicTree->makeOutputVariable(m_tma_dRlb_2,         "tma_dRlb_2");
      systematicTree->makeOutputVariable(m_tma_mll,            "tma_mll");
      systematicTree->makeOutputVariable(m_tma_pTll,           "tma_pTll");
      systematicTree->makeOutputVariable(m_tma_dRll,           "tma_dRll");
      systematicTree->makeOutputVariable(m_tma_mbb,            "tma_mbb");
      systematicTree->makeOutputVariable(m_tma_pTbb,           "tma_pTbb"); 
      systematicTree->makeOutputVariable(m_tma_dRbb,           "tma_dRbb");
      systematicTree->makeOutputVariable(m_tma_Rbq_avgLJ,      "tma_Rbq_avgLJ");
      systematicTree->makeOutputVariable(m_tma_Rbq_leadLJ,     "tma_Rbq_leadLJ");

      // for lepton + jets channel
      systematicTree->makeOutputVariable(m_klf_mtop_param,       "tma_klf_mtop_param");
      systematicTree->makeOutputVariable(m_klf_orig_mw,          "tma_klf_orig_mw");
      systematicTree->makeOutputVariable(m_klf_orig_rbq,         "tma_klf_orig_rbq");

      systematicTree->makeOutputVariable(m_klf_orig_ttbar_pt,    "klf_orig_ttbar_pt");
      systematicTree->makeOutputVariable(m_klf_orig_ttbar_eta,   "klf_orig_ttbar_eta");
      systematicTree->makeOutputVariable(m_klf_orig_ttbar_phi,   "klf_orig_ttbar_phi");
      systematicTree->makeOutputVariable(m_klf_orig_ttbar_e,     "klf_orig_ttbar_e");

      systematicTree->makeOutputVariable(m_klf_orig_tophad_pt,   "klf_orig_tophad_pt");
      systematicTree->makeOutputVariable(m_klf_orig_tophad_eta,  "klf_orig_tophad_eta");
      systematicTree->makeOutputVariable(m_klf_orig_tophad_phi,  "klf_orig_tophad_phi");
      systematicTree->makeOutputVariable(m_klf_orig_tophad_e,    "klf_orig_tophad_e");
      
      systematicTree->makeOutputVariable(m_klf_orig_toplep_pt,   "klf_orig_toplep_pt");
      systematicTree->makeOutputVariable(m_klf_orig_toplep_eta,  "klf_orig_toplep_eta");
      systematicTree->makeOutputVariable(m_klf_orig_toplep_phi,  "klf_orig_toplep_phi");
      systematicTree->makeOutputVariable(m_klf_orig_toplep_e,    "klf_orig_toplep_e");

      systematicTree->makeOutputVariable(m_klf_orig_Whad_pt,     "klf_orig_Whad_pt");
      systematicTree->makeOutputVariable(m_klf_orig_Whad_eta,    "klf_orig_Whad_eta");
      systematicTree->makeOutputVariable(m_klf_orig_Whad_phi,    "klf_orig_Whad_phi");
      systematicTree->makeOutputVariable(m_klf_orig_Whad_e,      "klf_orig_Whad_e");

      systematicTree->makeOutputVariable(m_klf_orig_Wlep_pt,     "klf_orig_Wlep_pt");
      systematicTree->makeOutputVariable(m_klf_orig_Wlep_eta,    "klf_orig_Wlep_eta");
      systematicTree->makeOutputVariable(m_klf_orig_Wlep_phi,    "klf_orig_Wlep_phi");
      systematicTree->makeOutputVariable(m_klf_orig_Wlep_e,      "klf_orig_Wlep_e");      
      
      systematicTree->makeOutputVariable(m_klf_orig_bhad_pt,     "klf_orig_bhad_pt");
      systematicTree->makeOutputVariable(m_klf_orig_bhad_eta,    "klf_orig_bhad_eta");
      systematicTree->makeOutputVariable(m_klf_orig_bhad_phi,    "klf_orig_bhad_phi");
      systematicTree->makeOutputVariable(m_klf_orig_bhad_e,      "klf_orig_bhad_e");

      systematicTree->makeOutputVariable(m_klf_orig_blep_pt,     "klf_orig_blep_pt");
      systematicTree->makeOutputVariable(m_klf_orig_blep_eta,    "klf_orig_blep_eta");
      systematicTree->makeOutputVariable(m_klf_orig_blep_phi,    "klf_orig_blep_phi");
      systematicTree->makeOutputVariable(m_klf_orig_blep_e,      "klf_orig_blep_e");

      systematicTree->makeOutputVariable(m_klf_orig_dRbb,        "klf_orig_dR_bb");
      systematicTree->makeOutputVariable(m_klf_orig_dRqqW,       "klf_orig_dR_qq_W");
      systematicTree->makeOutputVariable(m_klf_orig_dPHIbb,      "klf_orig_dPhi_bb");
      systematicTree->makeOutputVariable(m_klf_orig_dPHIqqW,     "klf_orig_dPhi_qq_W");
      systematicTree->makeOutputVariable(m_klf_orig_dETAbb,      "klf_orig_dEta_bb");
      systematicTree->makeOutputVariable(m_klf_orig_dETAqqW,     "klf_orig_dEta_qq_W");
      
      systematicTree->makeOutputVariable(m_klf_orig_dR_ttbar,    "klf_orig_dR_ttbar");
      systematicTree->makeOutputVariable(m_klf_orig_dPhi_ttbar,  "klf_orig_dPhi_ttbar");
      systematicTree->makeOutputVariable(m_klf_orig_dEta_ttbar,  "klf_orig_dEta_ttbar");
      
      systematicTree->makeOutputVariable(m_klf_orig_dR_Wb_had,   "klf_orig_dR_Wb_had");
      systematicTree->makeOutputVariable(m_klf_orig_dPhi_Wb_had, "klf_orig_dPhi_Wb_had");
      systematicTree->makeOutputVariable(m_klf_orig_dEta_Wb_had, "klf_orig_dEta_Wb_had");

      systematicTree->makeOutputVariable(m_klf_orig_dR_Wb_lep,   "klf_orig_dR_Wb_lep");
      systematicTree->makeOutputVariable(m_klf_orig_dPhi_Wb_lep, "klf_orig_dPhi_Wb_lep");
      systematicTree->makeOutputVariable(m_klf_orig_dEta_Wb_lep, "klf_orig_dEta_Wb_lep");

      systematicTree->makeOutputVariable(m_klf_orig_mlb,         "klf_orig_mlb");
      systematicTree->makeOutputVariable(m_klf_orig_ptlb,        "klf_orig_ptlb");

      systematicTree->makeOutputVariable(m_tma_matchingFlag,     "tma_matchingFlag");
      systematicTree->makeOutputVariable(m_tma_isDilepton,       "tma_isDilepton");

    }

}
  
  ///-- saveEvent - run for every systematic and every event --///
  void MassEventSaver::saveEvent(const top::Event& event) 
  {
    
    // calculate here now the flat variables neccessary for the top mass analysis, want to avoid to recalculate them every time offline!
    m_tma_njets = 0; 

    m_tma_mlb_minavg = 0.;

    m_tma_bjet_pt.clear();
    m_tma_bjet_eta.clear();
    m_tma_bjet_phi.clear();
    m_tma_bjet_e.clear();

    m_tma_jet_pt.clear();
    m_tma_jet_eta.clear();
    m_tma_jet_phi.clear();
    m_tma_jet_e.clear();

    int tma_nbjets = 0;

    m_tma_nbjets_85 = 0;
    m_tma_nbjets_77 = 0;
    m_tma_nbjets_70 = 0;
    m_tma_nbjets_60 = 0;

    

    // get vector of b-tagged jets
    for (const auto* const jetPtr : event.m_jets) {
      
      m_tma_njets++;

      const xAOD::BTagging* btag(nullptr);
      btag = jetPtr->btagging();	
      double mvx = -999;
      if (btag) btag->MVx_discriminant("MV2c10", mvx);

      if(mvx > 0.11)
	m_tma_nbjets_85++;
      if(mvx > 0.64)
        m_tma_nbjets_77++;
      if(mvx > 0.83)
        m_tma_nbjets_70++;
      if(mvx > 0.94)
        m_tma_nbjets_60++;


      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_85"))
	tma_nbjets = m_tma_nbjets_85;
      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_77"))
	tma_nbjets = m_tma_nbjets_77;
      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_70"))
	tma_nbjets = m_tma_nbjets_70;
      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_60"))
	tma_nbjets = m_tma_nbjets_60;
     

    
    }

    //    std::cout << m_tma_nbjets_60 << "\t" << m_tma_nbjets_70 << "\t" << m_tma_nbjets_77 << "\t" << m_tma_nbjets_85 << std::endl;
  
    // UGLY HACK!!!
    // tma_nbjets = m_tma_nbjets_70;

    //    std::cout << tma_nbjets << "\t" << m_tma_nbjets_77 << "\t" << m_tma_nbjets_70 << "\t" << m_tma_nbjets_60 << std::endl;

    m_tma_bjet_pt.resize(tma_nbjets);
    m_tma_bjet_eta.resize(tma_nbjets);
    m_tma_bjet_phi.resize(tma_nbjets);
    m_tma_bjet_e.resize(tma_nbjets);

    m_tma_jet_pt.resize(m_tma_njets);
    m_tma_jet_eta.resize(m_tma_njets);
    m_tma_jet_phi.resize(m_tma_njets);
    m_tma_jet_e.resize(m_tma_njets);

    int i = 0;
    int j = 0;

    //    std::cout << tma_nbjets << std::endl;

    std::vector<TLorentzVector> bJets;
    std::vector<TLorentzVector> LJets;
    std::vector<double> LJets_mvx;
    for (const auto* const jetPtr : event.m_jets) {

      m_tma_jet_pt[j]	= jetPtr->pt();
      m_tma_jet_eta[j]	= jetPtr->eta();
      m_tma_jet_phi[j]	= jetPtr->phi();
      m_tma_jet_e[j]	= jetPtr->e();

      ++j;

      const xAOD::BTagging* btag(nullptr);
      btag = jetPtr->btagging();
      double mvx = -999;
      if(btag) btag->MVx_discriminant("MV2c10", mvx);

      // will just run over one btagging WP for now at least
      // bool isTagged = (jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_85") || jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_77") || jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_70") || jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_60"));
      
      const auto& tagWP = m_config -> bTagWP_available().at(0); 
      bool isTagged = jetPtr->auxdataConst<char>("isbtagged_"+tagWP);

      if(isTagged){
	  
	m_tma_bjet_pt[i]  = jetPtr->pt();
	m_tma_bjet_eta[i] = jetPtr->eta();
	m_tma_bjet_phi[i] = jetPtr->phi();
	m_tma_bjet_e[i]   = jetPtr->e(); 
	   
	TLorentzVector help;
	help.SetPtEtaPhiE(jetPtr->pt(), jetPtr->eta(), jetPtr->phi(), jetPtr->e());
 
	bJets.push_back(help);

       

	++i;
      
      }
      else{
	
	TLorentzVector help;
	help.SetPtEtaPhiE(jetPtr->pt(), jetPtr->eta(), jetPtr->phi(), jetPtr->e());
 
	LJets.push_back(help);	
	LJets_mvx.push_back(mvx);	
	
      }

    }

    TLorentzVector blep_original;;
    TLorentzVector bhad_original;;
    TLorentzVector lq1_original;
    TLorentzVector lq2_original;
    TLorentzVector Whad_original;
    TLorentzVector Wlep_original;
    TLorentzVector tophad_original;
    TLorentzVector toplep_original;
    TLorentzVector lep_original;
    TLorentzVector nu_original;   
    TLorentzVector ttbar_original;

    int nPermutations  = 0; 
    bool validKLFitter = false;

    m_tma_matchingFlag = -1;

    if (event.m_KLFitterResults != nullptr) {
      
      validKLFitter = true;
      nPermutations = event.m_KLFitterResults->size();
      
    }

    // m_klf_mtop_param.resize(nPermutations);
    // m_klf_orig_mw.resize(nPermutations);
    // m_klf_orig_rbq.resize(nPermutations);
    // int iPerm = 0;

    if (validKLFitter && event.m_KLFitterResults -> size() > 0) {
      
      //      for (const auto* const klPtr : *event.m_KLFitterResults) {
      // only store best permutation for now, ignore the rest
      
      const auto* const klPtr = event.m_KLFitterResults -> at(0);
      
      int blep_index = klPtr->model_blep_jetIndex();
      int bhad_index = klPtr->model_bhad_jetIndex();
      int lq1_index  = klPtr->model_lq1_jetIndex();
      int lq2_index  = klPtr->model_lq2_jetIndex();
      
      blep_original.SetPtEtaPhiE(event.m_jets.at(blep_index) -> pt()/1000.0,
				 event.m_jets.at(blep_index) -> eta(),
				 event.m_jets.at(blep_index) -> phi(),
				 event.m_jets.at(blep_index) -> e()/1000.0);
      
      bhad_original.SetPtEtaPhiE(event.m_jets.at(bhad_index) -> pt()/1000.0,
				 event.m_jets.at(bhad_index) -> eta(),
				 event.m_jets.at(bhad_index) -> phi(),
				 event.m_jets.at(bhad_index) -> e()/1000.0);
      
      lq1_original.SetPtEtaPhiE(event.m_jets.at(lq1_index) -> pt()/1000.0,
				event.m_jets.at(lq1_index) -> eta(),
				event.m_jets.at(lq1_index) -> phi(),
				event.m_jets.at(lq1_index) -> e()/1000.0);
      
      lq2_original.SetPtEtaPhiE(event.m_jets.at(lq2_index) -> pt()/1000.0,
				event.m_jets.at(lq2_index) -> eta(),
				event.m_jets.at(lq2_index) -> phi(),
				event.m_jets.at(lq2_index) -> e()/1000.0);
      
      
      if(event.m_muons.size() == 1)
	lep_original.SetPtEtaPhiE(event.m_muons.at(0) -> pt()/1000.0, event.m_muons.at(0) -> eta(), event.m_muons.at(0) -> phi(), event.m_muons.at(0) -> e()/1000.0);
      else
	lep_original.SetPtEtaPhiE(event.m_electrons.at(0) -> pt()/1000.0, event.m_electrons.at(0) -> eta(), event.m_electrons.at(0) -> phi(), event.m_electrons.at(0) -> e()/1000.0);
      
      nu_original.SetPtEtaPhiE(klPtr->model_nu_pt(), klPtr->model_nu_eta(), klPtr->model_nu_phi(), klPtr->model_nu_E());
      
      Whad_original   = lq1_original    + lq2_original;
      Wlep_original   = lep_original    + nu_original;
      tophad_original = Whad_original   + bhad_original;
      toplep_original = Wlep_original   + blep_original;
      ttbar_original  = tophad_original + toplep_original;
      
      m_klf_orig_mw = Whad_original.M();
      
      //if(tma_nbjets == 1){/
      //m_klf_orig_rbq = m_tma_bjet_pt[0]/1000.0/((lq1_original.Pt()+lq2_original.Pt())*0.5);
      //}
      if(tma_nbjets >= 2){
	m_klf_orig_rbq = (blep_original.Pt() + bhad_original.Pt())/(lq1_original.Pt()+lq2_original.Pt());
      }
      
      int nr_param = klPtr->parameters().size();
      m_klf_mtop_param = klPtr->parameters().at(nr_param-1);
      
      m_klf_orig_ttbar_pt  = ttbar_original.Pt();
      m_klf_orig_ttbar_eta = ttbar_original.Eta();
      m_klf_orig_ttbar_phi = ttbar_original.Phi();
      m_klf_orig_ttbar_e   = ttbar_original.E();
      
      m_klf_orig_tophad_pt  = tophad_original.Pt();
      m_klf_orig_tophad_eta = tophad_original.Eta();
      m_klf_orig_tophad_phi = tophad_original.Phi();
      m_klf_orig_tophad_e   = tophad_original.E();
      
      m_klf_orig_toplep_pt  = toplep_original.Pt();
      m_klf_orig_toplep_eta = toplep_original.Eta();
      m_klf_orig_toplep_phi = toplep_original.Phi();
      m_klf_orig_toplep_e   = toplep_original.E();
      
      m_klf_orig_Whad_pt  = Whad_original.Pt();
      m_klf_orig_Whad_eta = Whad_original.Eta();
      m_klf_orig_Whad_phi = Whad_original.Phi();
      m_klf_orig_Whad_e   = Whad_original.E();
      
      m_klf_orig_Wlep_pt  = Wlep_original.Pt();
      m_klf_orig_Wlep_eta = Wlep_original.Eta();
      m_klf_orig_Wlep_phi = Wlep_original.Phi();
      m_klf_orig_Wlep_e   = Wlep_original.E();
      
      m_klf_orig_bhad_pt  = bhad_original.Pt();
      m_klf_orig_bhad_eta = bhad_original.Eta();
      m_klf_orig_bhad_phi = bhad_original.Phi();
      m_klf_orig_bhad_e   = bhad_original.E();
      
      m_klf_orig_blep_pt  = blep_original.Pt();
      m_klf_orig_blep_eta = blep_original.Eta();
      m_klf_orig_blep_phi = blep_original.Phi();
      m_klf_orig_blep_e   = blep_original.E();
      
      m_klf_orig_dRbb   = blep_original.DeltaR(bhad_original);
      m_klf_orig_dPHIbb = blep_original.DeltaPhi(bhad_original);
      m_klf_orig_dETAbb = blep_original.Eta() - bhad_original.Eta();
      
      m_klf_orig_dRqqW   = lq1_original.DeltaR(lq2_original);
      m_klf_orig_dPHIqqW = lq1_original.DeltaPhi(lq2_original);
      m_klf_orig_dETAqqW = lq1_original.Eta() - lq2_original.Eta();
      
      m_klf_orig_dR_ttbar   = tophad_original.DeltaR(toplep_original);
      m_klf_orig_dPhi_ttbar = tophad_original.DeltaPhi(toplep_original);
      m_klf_orig_dEta_ttbar = tophad_original.Eta() - toplep_original.Eta();

      m_klf_orig_dR_Wb_had   = Whad_original.DeltaR(bhad_original);
      m_klf_orig_dPhi_Wb_had = Whad_original.DeltaPhi(bhad_original);
      m_klf_orig_dEta_Wb_had = Whad_original.Eta() - bhad_original.Eta();
      
      m_klf_orig_dR_Wb_lep   = Wlep_original.DeltaR(blep_original);
      m_klf_orig_dPhi_Wb_lep = Wlep_original.DeltaPhi(blep_original);
      m_klf_orig_dEta_Wb_lep = Wlep_original.Eta() - blep_original.Eta();

      TLorentzVector vec_lb = blep_original + lep_original;

      m_klf_orig_mlb  = vec_lb.M();
      m_klf_orig_ptlb = vec_lb.Pt();
      
      const xAOD::IParticle* lepton = 0;
      if (!event.m_electrons.empty())
	lepton = event.m_electrons.front();
      else if (!event.m_muons.empty())
	lepton = event.m_muons.front();
      else {
	std::cout << "MET+MWT Tool: Not got a charged lepton" << std::endl;
	exit(1);
      }
      
      m_tma_mtw = top::mwt(*lepton, *event.m_met);
      
      //	++iPerm;
      // just running over the best permuation anyways, so in principle the loop is obsolete
      
      //      }
      
      // std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;
      
      if (m_config->isMC() && evtStore()->contains<xAOD::PartonHistoryContainer>("TopPartonHistory")){
      	m_tma_matchingFlag = this -> getMatchingFlag(event);
      }
    }

    m_tma_isDilepton = -1;
    if (m_config->isMC() && evtStore()->contains<xAOD::PartonHistoryContainer>("TopPartonHistory")){
      m_tma_isDilepton = this -> isDilepton(event);
    }
    
    std::vector<TLorentzVector> goodLeptons;
    std::vector<TLorentzVector> goodElectrons;
    std::vector<TLorentzVector> goodMuons;

    TLorentzVector lep_pos, lep_neg, top, tbar, ttbar, nu, nubar;
    bool lep_pos_set = false;
    bool lep_neg_set = false;

    for (const auto* const elPtr : event.m_electrons) {

      TLorentzVector help;
      help.SetPtEtaPhiE(elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());

      if (elPtr->charge() > 0) {
	lep_pos.SetPtEtaPhiE(elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());
	lep_pos_set = true; }

      else if (elPtr->charge() < 0) {
	lep_neg.SetPtEtaPhiE(elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());
	lep_neg_set = true; }

      goodLeptons.push_back(help);
      goodElectrons.push_back(help);

    }
    for (const auto* const muPtr : event.m_muons) {

      TLorentzVector help;
      help.SetPtEtaPhiE(muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());

      if (muPtr->charge() > 0) {
	lep_pos.SetPtEtaPhiE(muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());
	lep_pos_set = true; }

      else if (muPtr->charge() < 0) {
	lep_neg.SetPtEtaPhiE(muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());
	lep_neg_set = true; }

      goodLeptons.push_back(help);
      goodMuons.push_back(help);

    }

    m_tma_met	    = event.m_met->met();
    m_tma_met_ex    = event.m_met->mpx();
    m_tma_met_ey    = event.m_met->mpy();
    m_tma_met_phi   = event.m_met->phi();

    if(tma_nbjets >= 2 && goodLeptons.size() > 1){ 
      
      // Sort b-tagged jets by pT (*BP* or by MV2)  
      TLorentzVector b1;
      TLorentzVector b2;
      if(bJets[0].Pt() >= bJets[1].Pt()){
	b1 = bJets[0];
	b2 = bJets[1];
      }
      else{
	b1 = bJets[1];
	b2 = bJets[0];
      }
      
      m_tma_mbb  = (b1 + b2).M();
      m_tma_pTbb = (b1 + b2).Pt();
      m_tma_dRbb = b1.DeltaR(b2);
      
      // Sort leptons by pT  
      TLorentzVector L1;
      TLorentzVector L2;
      if(goodLeptons.at(0).Pt() >= goodLeptons.at(1).Pt()){
	L1 = goodLeptons.at(0);
	L2 = goodLeptons.at(1);
      }
      else{
	L1 = goodLeptons.at(1);
	L2 = goodLeptons.at(0);
      }

      //Pairing decision             
      TLorentzVector L1b1 = L1 + b1;
      TLorentzVector L2b2 = L2 + b2;
      TLorentzVector L1b2 = L1 + b2;
      TLorentzVector L2b1 = L2 + b1;
      double avgMass1 = (L1b1.M() + L2b2.M())/2 ;
      double avgMass2 = (L1b2.M() + L2b1.M())/2 ;
      
      TLorentzVector LBpair1;
      TLorentzVector LBpair2;
      TLorentzVector LBpair1_reject;
      TLorentzVector LBpair2_reject;
      double LBpair_avgMass = -1.0;
      double LBpair1_dR = -1.0;
      double LBpair2_dR = -1.0;
      
      if( avgMass1 <= avgMass2 ){
	LBpair1 = L1b1;
	LBpair2 = L2b2;
	LBpair1_reject = L1b2;
	LBpair2_reject = L2b1;
	LBpair_avgMass = avgMass1;
	LBpair1_dR = b1.DeltaR(L1);
	LBpair2_dR = b2.DeltaR(L2);
      }
      else{
	LBpair1 = L1b2;
	LBpair2 = L2b1;
	LBpair1_reject = L1b1;
	LBpair2_reject = L2b2;
	LBpair_avgMass = avgMass2;
	LBpair1_dR = b2.DeltaR(L1);
	LBpair2_dR = b1.DeltaR(L2);
      }

      m_tma_etdr = (L1.Et()*LBpair1_dR + L2.Et()*LBpair2_dR)/2.;
      m_tma_mlb_minavg     = LBpair_avgMass; 
      
      if(LBpair1.M() < LBpair2.M()){
	m_tma_mlb_minavglow   = LBpair1.M();
	m_tma_mlb_minavghigh  = LBpair2.M();
      }
      else{
	m_tma_mlb_minavglow   = LBpair2.M();
	m_tma_mlb_minavghigh  = LBpair1.M();
      }
      
      m_tma_pTlb_1 = LBpair1.Pt();
      m_tma_pTlb_2 = LBpair2.Pt();
      
      m_tma_dRlb_1 = LBpair1_dR;
      m_tma_dRlb_2 = LBpair2_dR;
      
      m_tma_mll    = (L1 + L2).M();
      m_tma_pTll   = (L1 + L2).Pt();
      m_tma_dRll   = L1.DeltaR(L2);
      
      double Rbq_avgLJ  = -1;
      double Rbq_leadLJ = -1;
      if(LJets.size() >= 1){
	double bJets_sumPt = 0;
	double LJets_sumPt = 0;
	for(int i = 0; i < (int)bJets.size(); ++i)
	  bJets_sumPt += bJets.at(i).Pt();
	for(int i = 0; i < (int)LJets.size(); ++i)
	  LJets_sumPt += LJets.at(i).Pt();
	
	Rbq_avgLJ  = (bJets_sumPt/bJets.size())/(LJets_sumPt/LJets.size());
	Rbq_leadLJ = (bJets_sumPt/bJets.size())/LJets.at(0).Pt();
      }
      m_tma_Rbq_avgLJ  = Rbq_avgLJ;
      m_tma_Rbq_leadLJ = Rbq_leadLJ;
      
      
      //Alternate Pairing decision min(max)       
      TLorentzVector LBpair1_maxMass;
      TLorentzVector LBpair1_minMass;
      TLorentzVector LBpair2_maxMass;
      TLorentzVector LBpair2_minMass;
      if(L1b1.M() > L2b2.M()){
	LBpair1_maxMass = L1b1;
	LBpair1_minMass = L2b2;
      }
      else{
	LBpair1_maxMass = L2b2;
	LBpair1_minMass = L1b1;
      }
      if(L1b2.M() > L2b1.M()){
	LBpair2_maxMass = L1b2;
	LBpair2_minMass = L2b1;
      }
      else{
	LBpair2_maxMass = L2b1;
	LBpair2_minMass = L1b2;
      }	
      
      if(LBpair1_maxMass.M() < LBpair2_maxMass.M())
	m_tma_mlb_minmax = LBpair1_maxMass.M();
      else
	m_tma_mlb_minmax = LBpair2_maxMass.M();
      
      if(LBpair1_maxMass.M() < LBpair2_maxMass.M()){
	m_tma_mlb_minmaxlow = LBpair1_minMass.M();
      }
      else{
	m_tma_mlb_minmaxlow = LBpair2_minMass.M();
      }
      
      if(LBpair1_maxMass.M() < LBpair2_maxMass.M()){
	m_tma_mlb_minmaxavg = (LBpair1_maxMass.M() + LBpair1_minMass.M())/2;
      }
      else{
	m_tma_mlb_minmaxavg = (LBpair2_maxMass.M() + LBpair2_minMass.M())/2;
      }
      
    }

    ///-- Let the base class do all the hard work --///
    if(nPermutations > 0)
      top::EventSaverFlatNtuple::saveEvent(event);
    
  
  } 


  float MassEventSaver::calculatePout(TLorentzVector t, TLorentzVector tbar){
    
    TVector3 t3(t.X(),t.Y(),t.Z());
    TVector3 tbar3(tbar.X(),tbar.Y(),tbar.Z());
    TVector3 z(0,0,1);
    TVector3 vec_temp=tbar3.Cross(z);
    
    vec_temp*=1/vec_temp.Mag();
    float pout=t3.Dot(vec_temp);
    
    return pout;
  }

  
  int MassEventSaver::isDilepton(const top::Event& event){
    
    // now retrieve top parton history                                                                                                                                                                     
    const xAOD::PartonHistoryContainer* partonHistoryContainer(nullptr);
    const xAOD::PartonHistory* partonHistory(nullptr);
    if (evtStore()->contains<xAOD::PartonHistoryContainer>("TopPartonHistory")) {
      top::check(evtStore()->retrieve(partonHistoryContainer, "TopPartonHistory"), "Failed to retrieve Top Parton History");
      if (partonHistoryContainer->size() == 1) {
        partonHistory = partonHistoryContainer->at(0);
      }
    }
    if (partonHistory != nullptr) {
      
      int MC_Wdecay1_from_tbar_pdgId = fabs(partonHistory->auxdataConst<int>("MC_Wdecay1_from_tbar_pdgId"));
      int MC_Wdecay1_from_t_pdgId    = fabs(partonHistory->auxdataConst<int>("MC_Wdecay1_from_t_pdgId"));
      
      // return 0 means a dilepton event!                                                                                                                                                                   
      if(MC_Wdecay1_from_tbar_pdgId > 6 && MC_Wdecay1_from_t_pdgId > 6)
	return 1;
      else
	return 0;
    

    }

    return -1;

  }


  int MassEventSaver::getMatchingFlag(const top::Event& event){

    TLorentzVector lep_original;

    int best_perm = -1;
    int iPerm = 0;

    for (const auto* const klPtr : *event.m_KLFitterResults) {
      
      /// Global result                                                                                                                                                                       
      //   m_klfitter_bestPermutation[iPerm] = klPtr->bestPermutation();
      if (klPtr->bestPermutation() == 1){
	best_perm = iPerm;
      }
      iPerm++;

    }

    //    int best_perm = m_klfitter_bestPermutation[0] = klPtr->bestPermutation();
    
    // first get the original vectors with the chosen permutation from klfitter
    const auto* const klPtr = event.m_KLFitterResults -> at(best_perm);

    //    std::cout << "------------------------------------------------------> BEST PERM = " << best_perm << std::endl;

    int blep_index = klPtr->model_blep_jetIndex();
    int bhad_index = klPtr->model_bhad_jetIndex();
    int lq1_index  = klPtr->model_lq1_jetIndex();
    int lq2_index  = klPtr->model_lq2_jetIndex();

    // if(event.m_KLFitterResults -> size() == 0)
    //  std::cout << blep_index << "\t" << bhad_index << std::endl;
    
    // always store: blep, bhad, lq1, lq2                                                                                                                                                                  
    int    MatchVector[4] = {-1, -1, -1, -1};
    double MatchDeltaR[4] = {-1.0, -1.0, -1.0, -1.0};
    int    CombiVector[4] = {blep_index, bhad_index, lq1_index, lq2_index};

    TLorentzVector blep_original;
    TLorentzVector bhad_original;
    TLorentzVector lq1_original;
    TLorentzVector lq2_original;

    const auto* const jetPtr = event.m_jets.at(blep_index);
    
    TLorentzVector help_jet;
    help_jet.SetPtEtaPhiE(jetPtr->pt(), jetPtr->eta(), jetPtr->phi(), jetPtr->e());
    blep_original = help_jet;

    const auto* const jetPtr2 = event.m_jets.at(bhad_index);
    help_jet.SetPtEtaPhiE(jetPtr2->pt(), jetPtr2->eta(), jetPtr2->phi(), jetPtr2->e());
    bhad_original = help_jet;

    const auto* const jetPtr3 = event.m_jets.at(lq1_index);
    help_jet.SetPtEtaPhiE(jetPtr3->pt(), jetPtr3->eta(), jetPtr3->phi(), jetPtr3->e());
    lq1_original = help_jet;

    const auto* const jetPtr4 = event.m_jets.at(lq2_index);
    help_jet.SetPtEtaPhiE(jetPtr4->pt(), jetPtr4->eta(), jetPtr4->phi(), jetPtr4->e());
    lq2_original = help_jet;

    if(event.m_muons.size() == 1)
      lep_original.SetPtEtaPhiE(event.m_muons.at(0) -> pt()/1000.0, event.m_muons.at(0) -> eta(), event.m_muons.at(0) -> phi(), event.m_muons.at(0) -> e()/1000.0);
    else
      lep_original.SetPtEtaPhiE(event.m_electrons.at(0) -> pt()/1000.0, event.m_electrons.at(0) -> eta(), event.m_electrons.at(0) -> phi(), event.m_electrons.at(0) -> e()/1000.0);

    // now retrieve top parton history
    const xAOD::PartonHistoryContainer* partonHistoryContainer(nullptr);
    const xAOD::PartonHistory* partonHistory(nullptr);
    if (evtStore()->contains<xAOD::PartonHistoryContainer>("TopPartonHistory")) {
      top::check(evtStore()->retrieve(partonHistoryContainer, "TopPartonHistory"), "Failed to retrieve Top Parton History");
      if (partonHistoryContainer->size() == 1) {
	partonHistory = partonHistoryContainer->at(0);
      }
    }
    if (partonHistory != nullptr) {
      // now get the mc truth four-momenta

      TLorentzVector blep_truth;
      TLorentzVector bhad_truth;
      TLorentzVector lq1_truth;
      TLorentzVector lq2_truth;
      TLorentzVector lep_truth;

      // ok write this out here, to avoid chaos
      float MC_Wdecay1_from_tbar_pt  = partonHistory->auxdataConst<float>("MC_Wdecay1_from_tbar_pt");
      float MC_Wdecay1_from_tbar_eta = partonHistory->auxdataConst<float>("MC_Wdecay1_from_tbar_eta");
      float MC_Wdecay1_from_tbar_phi = partonHistory->auxdataConst<float>("MC_Wdecay1_from_tbar_phi");
      float MC_Wdecay1_from_tbar_m   = partonHistory->auxdataConst<float>("MC_Wdecay1_from_tbar_m");
      float MC_Wdecay2_from_tbar_pt  = partonHistory->auxdataConst<float>("MC_Wdecay2_from_tbar_pt");
      float MC_Wdecay2_from_tbar_eta = partonHistory->auxdataConst<float>("MC_Wdecay2_from_tbar_eta");
      float MC_Wdecay2_from_tbar_phi = partonHistory->auxdataConst<float>("MC_Wdecay2_from_tbar_phi");
      float MC_Wdecay2_from_tbar_m   = partonHistory->auxdataConst<float>("MC_Wdecay2_from_tbar_m");
      float MC_b_from_tbar_pt        = partonHistory->auxdataConst<float>("MC_b_from_tbar_pt");
      float MC_b_from_tbar_eta       = partonHistory->auxdataConst<float>("MC_b_from_tbar_eta");
      float MC_b_from_tbar_phi       = partonHistory->auxdataConst<float>("MC_b_from_tbar_phi");
      float MC_b_from_tbar_m         = partonHistory->auxdataConst<float>("MC_b_from_tbar_m");
      // do the same for the top
      float MC_Wdecay1_from_t_pt  = partonHistory->auxdataConst<float>("MC_Wdecay1_from_t_pt");
      float MC_Wdecay1_from_t_eta = partonHistory->auxdataConst<float>("MC_Wdecay1_from_t_eta");
      float MC_Wdecay1_from_t_phi = partonHistory->auxdataConst<float>("MC_Wdecay1_from_t_phi");
      float MC_Wdecay1_from_t_m   = partonHistory->auxdataConst<float>("MC_Wdecay1_from_t_m");
      float MC_Wdecay2_from_t_pt  = partonHistory->auxdataConst<float>("MC_Wdecay2_from_t_pt");
      float MC_Wdecay2_from_t_eta = partonHistory->auxdataConst<float>("MC_Wdecay2_from_t_eta");
      float MC_Wdecay2_from_t_phi = partonHistory->auxdataConst<float>("MC_Wdecay2_from_t_phi");
      float MC_Wdecay2_from_t_m   = partonHistory->auxdataConst<float>("MC_Wdecay2_from_t_m");
      float MC_b_from_t_pt        = partonHistory->auxdataConst<float>("MC_b_from_t_pt");
      float MC_b_from_t_eta       = partonHistory->auxdataConst<float>("MC_b_from_t_eta");
      float MC_b_from_t_phi       = partonHistory->auxdataConst<float>("MC_b_from_t_phi");
      float MC_b_from_t_m         = partonHistory->auxdataConst<float>("MC_b_from_t_m");
      // and the corresponding pdgId
      int MC_Wdecay1_from_tbar_pdgId = fabs(partonHistory->auxdataConst<int>("MC_Wdecay1_from_tbar_pdgId"));
      int MC_Wdecay1_from_t_pdgId    = fabs(partonHistory->auxdataConst<int>("MC_Wdecay1_from_t_pdgId"));

      // return 0 means a dilepton event!
      if(MC_Wdecay1_from_tbar_pdgId > 6 && MC_Wdecay1_from_t_pdgId > 6)
	return 0;


      // Need to check first which W decayed into quarks                                                                                                                                               
      if(MC_Wdecay1_from_tbar_pdgId < 6){
	// Now we know that the tbar is decaying hadronically                                                                                                                                        
	lq1_truth.SetPtEtaPhiM(MC_Wdecay1_from_tbar_pt, MC_Wdecay1_from_tbar_eta, MC_Wdecay1_from_tbar_phi, MC_Wdecay1_from_tbar_m);
	lq2_truth.SetPtEtaPhiM(MC_Wdecay2_from_tbar_pt, MC_Wdecay2_from_tbar_eta, MC_Wdecay2_from_tbar_phi, MC_Wdecay2_from_tbar_m);
	bhad_truth.SetPtEtaPhiM(MC_b_from_tbar_pt,      MC_b_from_tbar_eta,       MC_b_from_tbar_phi,       MC_b_from_tbar_m);
	blep_truth.SetPtEtaPhiM(MC_b_from_t_pt,         MC_b_from_t_eta,          MC_b_from_t_phi,          MC_b_from_t_m);
	
	if(MC_Wdecay1_from_t_pdgId == 11 || MC_Wdecay1_from_t_pdgId == 13 || MC_Wdecay1_from_t_pdgId == 15)
	  lep_truth.SetPtEtaPhiM(MC_Wdecay1_from_t_pt, MC_Wdecay1_from_t_eta, MC_Wdecay1_from_t_phi, MC_Wdecay1_from_t_m);
	else
	  lep_truth.SetPtEtaPhiM(MC_Wdecay2_from_t_pt, MC_Wdecay2_from_t_eta, MC_Wdecay2_from_t_phi, MC_Wdecay2_from_t_m);
	
	// std::cout << "Hier 1  " << lq1_truth.Pt() << "\t" << lq2_truth.Pt() << "\t" << blep_truth.Pt() << "\t" << bhad_truth.Pt()  << std::endl;

	/*
	std::cout << "First: tbar is decaying hadronically!" << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay1_from_tbar_pdgId") << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay2_from_tbar_pdgId") << std::endl;
	//std::cout << partonHistory->auxdataConst<int>("MC_b_from_tbar_pdgId")       << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay1_from_t_pdgId")    << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay2_from_t_pdgId")    << std::endl;
	//std::cout << partonHistory->auxdataConst<int>("MC_b_from_t_pdgId")          << std::endl;
	*/

      }
      else{
	// Now we know that the tbar is decaying leptonically                                                                                                                                        
	lq1_truth.SetPtEtaPhiM(MC_Wdecay1_from_t_pt, MC_Wdecay1_from_t_eta, MC_Wdecay1_from_t_phi, MC_Wdecay1_from_t_m);
	lq2_truth.SetPtEtaPhiM(MC_Wdecay2_from_t_pt, MC_Wdecay2_from_t_eta, MC_Wdecay2_from_t_phi, MC_Wdecay2_from_t_m);
	bhad_truth.SetPtEtaPhiM(MC_b_from_t_pt,      MC_b_from_t_eta,       MC_b_from_t_phi,       MC_b_from_t_m);
	blep_truth.SetPtEtaPhiM(MC_b_from_tbar_pt,   MC_b_from_tbar_eta,    MC_b_from_tbar_phi,    MC_b_from_tbar_m);
	
	if(MC_Wdecay1_from_tbar_pdgId == 11 || MC_Wdecay1_from_tbar_pdgId == 13 || MC_Wdecay1_from_tbar_pdgId == 15)
	  lep_truth.SetPtEtaPhiM(MC_Wdecay1_from_tbar_pt, MC_Wdecay1_from_tbar_eta, MC_Wdecay1_from_tbar_phi, MC_Wdecay1_from_tbar_m);
	else
	  lep_truth.SetPtEtaPhiM(MC_Wdecay2_from_tbar_pt, MC_Wdecay2_from_tbar_eta, MC_Wdecay2_from_tbar_phi, MC_Wdecay2_from_tbar_m);
	

	/*std::cout << "First: tbar is decaying leptonically!" <<std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay1_from_t_pdgId")    << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay2_from_t_pdgId")    << std::endl;
	//std::cout << partonHistory->auxdataConst<int>("MC_b_from_t_pdgId")          << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay1_from_tbar_pdgId") << std::endl;
	std::cout << partonHistory->auxdataConst<int>("MC_Wdecay2_from_tbar_pdgId") << std::endl;
	//std::cout << partonHistory->auxdataConst<int>("MC_b_from_tbar_pdgId")       << std::endl;
	*/

      }

      // now: save ids from original four-vectors, and check which jets from original four vectors are matched to the truth --> is there any kind of sorting? also do give KLFitter only a subset of jets, how do they know??? ...

      int counter = 0;
      
      bool print = false;

      // std::cout << "=====>   " << "counter" << "\t" << "blep truth" << "\t" << "bhad truth" << "\t" << "lq1 truth" << "\t" << "lq2 truth" << std::endl;

      // now: loop over all available jets, and check if they are matched to the truth particles
      for (const auto* const jetPtr : event.m_jets) {
	
	TLorentzVector help_jet;
	help_jet.SetPtEtaPhiE(jetPtr->pt(), jetPtr->eta(), jetPtr->phi(), jetPtr->e());
	
	// each jet is allowed to be only matched once, and each parton is allowed to be only matched once

	// std::cout << "=====>   " << counter << "\t" << help_jet.DeltaR(blep_truth) << "\t" << help_jet.DeltaR(bhad_truth) << "\t" << help_jet.DeltaR(lq1_truth) << "\t" << help_jet.DeltaR(lq2_truth) << "\t" << help_jet.Pt() << std::endl; 
	
	
	
	if(help_jet.DeltaR(blep_truth) < 0.3){

	  if(MatchVector[0] != -1){
	    //std::cout << "Entry 0 , " << MatchVector[0] << "\t" << counter << "\t" << MatchDeltaR[0] << "\t" << help_jet.DeltaR(blep_truth)  << std::endl;
	    //print = true;
	    if(help_jet.DeltaR(blep_truth) < MatchDeltaR[0]){
	      MatchVector[0] = counter;
              MatchDeltaR[0] = help_jet.DeltaR(blep_truth);
            }
	  }
	  else{
	    MatchVector[0] = counter;
	    MatchDeltaR[0] = help_jet.DeltaR(blep_truth);
	  }
	}
	if(help_jet.DeltaR(bhad_truth) < 0.3){
	  if(MatchVector[1] != -1){
	    if(help_jet.DeltaR(bhad_truth) < MatchDeltaR[1]){
	      MatchVector[1] = counter;
	      MatchDeltaR[1] = help_jet.DeltaR(bhad_truth);
	    }
	    //std::cout << "Entry 1 , " << MatchVector[1] << "\t" << counter << "\t" << MatchDeltaR[1] << "\t" << help_jet.DeltaR(bhad_truth)  << std::endl;
	    //print = true;
	  }
	  else{
	    MatchVector[1] = counter;
	    MatchDeltaR[1] = help_jet.DeltaR(bhad_truth);
	  }
	}
	if(help_jet.DeltaR(lq1_truth)  < 0.3){
	  if(MatchVector[2] != -1){
	    if(help_jet.DeltaR(lq1_truth) < MatchDeltaR[2]){
	      MatchVector[2] = counter;
              MatchDeltaR[2] = help_jet.DeltaR(lq1_truth);
            }
	    //std::cout << "Entry 2 , " << MatchVector[2] << "\t" << counter << "\t" << MatchDeltaR[2] << "\t" << help_jet.DeltaR(lq1_truth)  << std::endl;
	    //print = true;
	  }
	  else{
	    MatchVector[2] = counter;
	    MatchDeltaR[2] = help_jet.DeltaR(lq1_truth);
	  }
	}
	if(help_jet.DeltaR(lq2_truth)  < 0.3){
	  if(MatchVector[3] != -1){
	    if(help_jet.DeltaR(lq2_truth) < MatchDeltaR[3]){
              MatchVector[3] = counter;
              MatchDeltaR[3] = help_jet.DeltaR(lq2_truth);
            }
	    //std::cout << "Entry 3 , " << MatchVector[3] << "\t" << counter << "\t" << MatchDeltaR[3] << "\t" << help_jet.DeltaR(lq2_truth)  << std::endl;
	    //print = true;
	  }
	  else{
	    MatchVector[3] = counter;
	    MatchDeltaR[3] = help_jet.DeltaR(lq2_truth);
	  }
	}	

	// std::cout << help_jet.Eta() << "\t" << blep_truth.Eta() << "\t" << bhad_truth.Eta() << std::endl;

	// std::cout << help_jet.Pt() << "\t" << help_jet.DeltaR(blep_truth) << "\t" << help_jet.DeltaR(bhad_truth) << "\t" << help_jet.DeltaR(lq1_truth) << "\t" << help_jet.DeltaR(lq2_truth) << std::endl;
	
	counter++;
	
      }    

      // how to define now "wrongly" matched? check if true jet 1-4 is matched to reco jet 1-4 in any other way? or check only if there is a reco jet for each truth jet? or check which jets were handed to KLFitter also?
      // or could there be a problem in the truth (parton level) code?
      // do we call something unmatched if the right four jets are not selected at all?

      /*      std::cout << "====================================================================" << std::endl; */

      if(print){
	std::cout << MatchVector[0] << "\t" << MatchVector[1] << "\t" << MatchVector[2] << "\t" << MatchVector[3] << std::endl; 
	std::cout << CombiVector[0] << "\t" << CombiVector[1] << "\t" << CombiVector[2] << "\t" << CombiVector[3] << std::endl;
      }
      /*
      std::cout << blep_truth.DeltaR(blep_original) << "\t" << bhad_truth.DeltaR(bhad_original) << "\t" << lq1_truth.DeltaR(lq1_original) << "\t" << lq2_truth.DeltaR(lq2_original) << "\t" << lq1_truth.DeltaR(lq2_original) << "\t" << lq2_truth.DeltaR(lq1_original)   << std::endl;
      */
      
      // make now sure that all partons are matched
      for (int i=0; i<4; i++) {
	if (MatchVector[i] == -1)
	  return 3;
      }
      
      // now make sure that they are matched to different jets
      for (int i=0; i<4; i++) {
	for (int j=i+1; j<4; j++) {
	  if (MatchVector[i] == MatchVector[j])
	    return 3;
	}
      }

      if(lep_original.DeltaR(lep_truth) > 0.1)
	return 3;
      
      // if we arrive here, all partons are matched to different jets, now need to check if they are correctly matched
      if(MatchVector[0] == CombiVector[0] && MatchVector[1] == CombiVector[1] && ((MatchVector[2] == CombiVector[2] and MatchVector[3] == CombiVector[3]) or (MatchVector[2] == CombiVector[3] and MatchVector[3] == CombiVector[2]))){
	return 1; // 1: matched with correct combination
      }
      else{
	return 2;
      }
      
    }

    return -1;

  }

  
}

