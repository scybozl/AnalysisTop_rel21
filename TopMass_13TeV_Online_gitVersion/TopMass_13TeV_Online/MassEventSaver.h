/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
*/

#ifndef TOPMASS_13TEV_ONLINE_MASSEVENTSAVER_H
#define TOPMASS_13TEV_ONLINE_MASSEVENTSAVER_H

#include "TopAnalysis/EventSaverFlatNtuple.h"

/**
 * 
 * This class inherits from top::EventSaverFlatNtuple, which will be doing all the hard work 
 * 
 */

namespace top{
  class MassEventSaver : public top::EventSaverFlatNtuple {
    public:
      ///-- Default constrcutor with no arguments - needed for ROOT --///
      MassEventSaver();
      ///-- Destructor does nothing --///
      virtual ~MassEventSaver(){}
      
      ///-- initialize function for top::EventSaverFlatNtuple --///
      ///-- We will be setting up out custom variables here --///
      virtual void initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches) override;
      
      ///-- Keep the asg::AsgTool happy --///
      virtual StatusCode initialize() override {return StatusCode::SUCCESS;}      
      
      ///-- saveEvent function for top::EventSaverFlatNtuple --///
      ///-- We will be setting our custom variables on a per-event basis --///
      virtual void saveEvent(const top::Event& event) override;


      int getMatchingFlag(const top::Event& event);
      int isDilepton(const top::Event& event);

      float calculateDphi_ttbar(TLorentzVector t, TLorentzVector tbar);
      float calculatePout(TLorentzVector t, TLorentzVector tbar);
      
    private:
      ///-- Some additional custom variables for the output --///
      //float m_randomNumber;
      //float m_someOtherVariable;
      
      std::shared_ptr<top::TopConfig> m_config;

      // "tma" always stands for "top mass analysis"

      double m_klf_mtop_param;
      double m_klf_orig_mw;
      double m_klf_orig_rbq;

      int m_tma_nbjets_85;
      int m_tma_nbjets_77;
      int m_tma_nbjets_70;
      int m_tma_nbjets_60;
      std::vector<double> m_tma_bjet_pt;
      std::vector<double> m_tma_bjet_eta;
      std::vector<double> m_tma_bjet_phi;
      std::vector<double> m_tma_bjet_e;
      int m_tma_njets;
      std::vector<double> m_tma_jet_pt;
      std::vector<double> m_tma_jet_eta;
      std::vector<double> m_tma_jet_phi;
      std::vector<double> m_tma_jet_e;

      int m_tma_matchingFlag;
      int m_tma_isDilepton;

      // plots for dilepton channel
      double m_tma_etdr;
      double m_tma_met;
      double m_tma_met_ex;
      double m_tma_met_ey;
      double m_tma_met_phi;
      double m_tma_mtw;

      double m_tma_mlb_minavg;
      double m_tma_mlb_minavglow;
      double m_tma_mlb_minavghigh;
      double m_tma_mlb_minmax;
      double m_tma_mlb_minmaxlow;
      double m_tma_mlb_minmaxavg;
      double m_tma_pTlb_1;
      double m_tma_pTlb_2;
      double m_tma_dRlb_1;
      double m_tma_dRlb_2;
      double m_tma_mll;
      double m_tma_pTll;
      double m_tma_dRll;
      double m_tma_mbb;
      double m_tma_pTbb;
      double m_tma_dRbb;
      double m_tma_Rbq_avgLJ;
      double m_tma_Rbq_leadLJ;

      float m_klf_orig_ttbar_pt;
      float m_klf_orig_ttbar_eta;
      float m_klf_orig_ttbar_phi;
      float m_klf_orig_ttbar_e;

      float m_klf_orig_tophad_pt;
      float m_klf_orig_tophad_eta;
      float m_klf_orig_tophad_phi;
      float m_klf_orig_tophad_e;

      float m_klf_orig_toplep_pt;
      float m_klf_orig_toplep_eta;
      float m_klf_orig_toplep_phi;
      float m_klf_orig_toplep_e;

      float m_klf_orig_Whad_pt;
      float m_klf_orig_Whad_eta;
      float m_klf_orig_Whad_phi;
      float m_klf_orig_Whad_e;

      float m_klf_orig_Wlep_pt;
      float m_klf_orig_Wlep_eta;
      float m_klf_orig_Wlep_phi;
      float m_klf_orig_Wlep_e;

      float m_klf_orig_bhad_pt;
      float m_klf_orig_bhad_eta;
      float m_klf_orig_bhad_phi;
      float m_klf_orig_bhad_e;

      float m_klf_orig_blep_pt;
      float m_klf_orig_blep_eta;
      float m_klf_orig_blep_phi;
      float m_klf_orig_blep_e;

      float m_klf_orig_dRbb;
      float m_klf_orig_dPHIbb;
      float m_klf_orig_dETAbb;

      float m_klf_orig_dRqqW;
      float m_klf_orig_dPHIqqW;
      float m_klf_orig_dETAqqW;

      float m_klf_orig_dR_ttbar;
      float m_klf_orig_dPhi_ttbar;
      float m_klf_orig_dEta_ttbar;

      float m_klf_orig_dR_Wb_had;
      float m_klf_orig_dPhi_Wb_had;
      float m_klf_orig_dEta_Wb_had;
      
      float m_klf_orig_dR_Wb_lep;
      float m_klf_orig_dPhi_Wb_lep;
      float m_klf_orig_dEta_Wb_lep;

      float m_klf_orig_mlb;
      float m_klf_orig_ptlb;

      ///-- Tell RootCore to build a dictionary (we need this) --///
      ClassDef(top::MassEventSaver, 0);
  };
}

#endif
