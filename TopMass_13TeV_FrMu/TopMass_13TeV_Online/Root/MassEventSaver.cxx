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
    m_tma_nbjets_85(-99.),
    m_tma_nbjets_77(-99.),
    m_tma_nbjets_70(-99.),
    m_tma_nbjets_60(-99.),
    pseudotop(true),
    m_tma_pseudotop_mtop_param(-99.),
    m_tma_pseudotop1_mtop_param(-99.),
    m_tma_pseudotop2_mtop_param(-99.),
    m_tma_pseudotop3_mtop_param(-99.),
    m_tma_pseudotop_mw(-99.),
    m_tma_pseudotop_rbq(-99.),
    m_tma_njets(0.),
    m_tma_etdr(-99.),
    m_tma_met(-99.),
    m_tma_met_ex(-99.),
    m_tma_met_ey(-99.),
    m_tma_met_phi(-99.),
    m_tma_mlb_minavg(-99.),
    m_tma_mlb_minavglow(-99.),
    m_tma_mlb_minavghigh(-99.),
    m_tma_mlb_minmax(-99.),
    m_tma_mlb_minmaxlow(-99.),
    m_tma_mlb_minmaxavg(-99.),
    m_tma_lead_jet_pt(-99.),
    m_tma_lead_bjet_pt(-99.),
    m_tma_lead_el_pt(-99.),
    m_tma_lead_mu_pt(-99.),
    m_tma_pTlb_1(-99.),
    m_tma_pTlb_2(-99.),
    m_tma_dRlb_1(-99.),
    m_tma_dRlb_2(-99.),
    m_tma_mll(-99.),
    m_tma_pTll(-99.),
    m_tma_dRll(-99.),
    m_tma_mbb(-99.),
    m_tma_pTbb(-99.),
    m_tma_dRbb(-99.),
    m_tma_Rbq_avgLJ(-99.),
    m_tma_Rbq_leadLJ(-99.),
    m_klf_mtop_param(0.),
    m_klf_orig_mw(0.),
    m_klf_orig_rbq(0.),
    m_tma_matchingFlag(-1),
    m_tma_top_pt(-99.),
    m_tma_top_eta(-99.),
    m_tma_top_phi(-99.),
    m_tma_top_m(-99.),
    m_tma_top_e(-99.),
    m_tma_top_y(-99.),
    m_tma_tbar_pt(-99.),
    m_tma_tbar_eta(-99.),
    m_tma_tbar_phi(-99.),
    m_tma_tbar_m(-99.),
    m_tma_tbar_e(-99.),
    m_tma_tbar_y(-99.),
    m_tma_av_top_pt (-99.),
    m_tma_av_top_eta(-99.),
    m_tma_av_top_phi(-99.),
    m_tma_av_top_m(-99.),
    m_tma_av_top_e(-99.),
    m_tma_av_top_y(-99.),
    m_tma_ttbar_pt(-99.),
    m_tma_ttbar_eta(-99.),
    m_tma_ttbar_phi(-99.),
    m_tma_ttbar_m(-99.),
    m_tma_ttbar_e(-99.),
    m_tma_ttbar_y(-99.),
    m_tma_ttbar_pout(-99.),
    m_tma_nu_pt(-99.),
    m_tma_nu_eta(-99.),
    m_tma_nu_phi(-99.),
    m_tma_nu_m(-99.),
    m_tma_nu_e(-99.),
    m_tma_nu_y(-99.),
    m_tma_nubar_pt(-99.),
    m_tma_nubar_eta(-99.),
    m_tma_nubar_phi(-99.),
    m_tma_nubar_m(-99.),
    m_tma_nubar_e(-99.),
    m_tma_nubar_y(-99.),
    m_tma_Wp_pt(-99.),
    m_tma_Wp_eta(-99.),
    m_tma_Wp_phi(-99.),
    m_tma_Wp_m(-99.),
    m_tma_Wp_e(-99.),
    m_tma_Wp_y(-99.),
    m_tma_Wm_pt(-99.),
    m_tma_Wm_eta(-99.),
    m_tma_Wm_phi(-99.),
    m_tma_Wm_m(-99.),
    m_tma_Wm_e(-99.),
    m_tma_Wm_y(-99.),

    m_tma_particle_pseudotop_mtop_param(-99.),
    m_tma_particle_pseudotop1_mtop_param(-99.),
    m_tma_particle_pseudotop2_mtop_param(-99.),
    m_tma_particle_pseudotop3_mtop_param(-99.),
    m_tma_particle_pseudotop_mw(-99.),
    m_tma_particle_pseudotop_rbq(-99.),
    m_tma_particle_nbjets(-99.),
    m_tma_particle_njets(0.),
    m_tma_particle_etdr(-99.),
    m_tma_particle_met(-99.),
    m_tma_particle_met_ex(-99.),
    m_tma_particle_met_ey(-99.),
    m_tma_particle_met_phi(-99.),
    m_tma_particle_mlb_minavg(-99.),
    m_tma_particle_mlb_minavglow(-99.),
    m_tma_particle_mlb_minavghigh(-99.),
    m_tma_particle_mlb_minmax(-99.),
    m_tma_particle_mlb_minmaxlow(-99.),
    m_tma_particle_mlb_minmaxavg(-99.),
    m_tma_particle_lead_jet_pt(-99.),
    m_tma_particle_lead_bjet_pt(-99.),
    m_tma_particle_lead_el_pt(-99.),
    m_tma_particle_lead_mu_pt(-99.),
    m_tma_particle_pTlb_1(-99.),
    m_tma_particle_pTlb_2(-99.),
    m_tma_particle_dRlb_1(-99.),
    m_tma_particle_dRlb_2(-99.),
    m_tma_particle_mll(-99.),
    m_tma_particle_pTll(-99.),
    m_tma_particle_dRll(-99.),
    m_tma_particle_mbb(-99.),
    m_tma_particle_pTbb(-99.),
    m_tma_particle_dRbb(-99.),
    m_tma_particle_top_pt(-99.),
    m_tma_particle_top_eta(-99.),
    m_tma_particle_top_phi(-99.),
    m_tma_particle_top_m(-99.),
    m_tma_particle_top_e(-99.),
    m_tma_particle_top_y(-99.),
    m_tma_particle_tbar_pt(-99.),
    m_tma_particle_tbar_eta(-99.),
    m_tma_particle_tbar_phi(-99.),
    m_tma_particle_tbar_m(-99.),
    m_tma_particle_tbar_e(-99.),
    m_tma_particle_tbar_y(-99.),
    m_tma_particle_av_top_pt (-99.),
    m_tma_particle_av_top_eta(-99.),
    m_tma_particle_av_top_phi(-99.),
    m_tma_particle_av_top_m(-99.),
    m_tma_particle_av_top_e(-99.),
    m_tma_particle_av_top_y(-99.),
    m_tma_particle_ttbar_pt(-99.),
    m_tma_particle_ttbar_eta(-99.),
    m_tma_particle_ttbar_phi(-99.),
    m_tma_particle_ttbar_m(-99.),
    m_tma_particle_ttbar_e(-99.),
    m_tma_particle_ttbar_y(-99.),
    m_tma_particle_ttbar_pout(-99.),
    m_tma_particle_nu_pt(-99.),
    m_tma_particle_nu_eta(-99.),
    m_tma_particle_nu_phi(-99.),
    m_tma_particle_nu_m(-99.),
    m_tma_particle_nu_e(-99.),
    m_tma_particle_nu_y(-99.),
    m_tma_particle_nubar_pt(-99.),
    m_tma_particle_nubar_eta(-99.),
    m_tma_particle_nubar_phi(-99.),
    m_tma_particle_nubar_m(-99.),
    m_tma_particle_nubar_e(-99.),
    m_tma_particle_nubar_y(-99.),
    m_tma_particle_Wp_pt(-99.),
    m_tma_particle_Wp_eta(-99.),
    m_tma_particle_Wp_phi(-99.),
    m_tma_particle_Wp_m(-99.),
    m_tma_particle_Wp_e(-99.),
    m_tma_particle_Wp_y(-99.),
    m_tma_particle_Wm_pt(-99.),
    m_tma_particle_Wm_eta(-99.),
    m_tma_particle_Wm_phi(-99.),
    m_tma_particle_Wm_m(-99.),
    m_tma_particle_Wm_e(-99.),
    m_tma_particle_Wm_y(-99.)
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

      // "tma" stands here for "top mass analysis"
      systematicTree->makeOutputVariable(m_tma_klfitter_mtop_param, "tma_klfitter_mtop_param");
      systematicTree->makeOutputVariable(m_tma_original_mw,         "tma_original_mw");
      systematicTree->makeOutputVariable(m_tma_original_rbq,        "tma_original_rbq");
      systematicTree->makeOutputVariable(m_tma_pseudotop_mtop_param, "tma_pseudotop_mtop_param");
      systematicTree->makeOutputVariable(m_tma_pseudotop1_mtop_param, "tma_pseudotop1_mtop_param");
      systematicTree->makeOutputVariable(m_tma_pseudotop2_mtop_param, "tma_pseudotop2_mtop_param");
      systematicTree->makeOutputVariable(m_tma_pseudotop3_mtop_param, "tma_pseudotop3_mtop_param");
      systematicTree->makeOutputVariable(m_tma_nbjets,         "tma_nbjets");
      systematicTree->makeOutputVariable(m_tma_nbjets_85,      "tma_nbjets_85");
      systematicTree->makeOutputVariable(m_tma_nbjets_77,      "tma_nbjets_77");
      systematicTree->makeOutputVariable(m_tma_nbjets_70,      "tma_nbjets_70");
      systematicTree->makeOutputVariable(m_tma_nbjets_60,      "tma_nbjets_60");
      systematicTree->makeOutputVariable(m_tma_pseudotop_mw,         "tma_pseudotop_mw");
      systematicTree->makeOutputVariable(m_tma_pseudotop_rbq,        "tma_pseudotop_rbq");
      systematicTree->makeOutputVariable(m_tma_bjet_pt,             "tma_bjet_pt");
      systematicTree->makeOutputVariable(m_tma_bjet_eta,            "tma_bjet_eta");
      systematicTree->makeOutputVariable(m_tma_bjet_phi,            "tma_bjet_phi");
      systematicTree->makeOutputVariable(m_tma_bjet_e,              "tma_bjet_e");
      systematicTree->makeOutputVariable(m_tma_lead_jet_pt,         "tma_lead_jet_pt");
      systematicTree->makeOutputVariable(m_tma_lead_bjet_pt,         "tma_lead_bjet_pt");
      systematicTree->makeOutputVariable(m_tma_lead_el_pt,         "tma_lead_el_pt");
      systematicTree->makeOutputVariable(m_tma_lead_mu_pt,         "tma_lead_mu_pt");


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

      // Leptons

      systematicTree->makeOutputVariable(m_tma_el_e,		"tma_el_e");
      systematicTree->makeOutputVariable(m_tma_el_pt,		"tma_el_pt");
      systematicTree->makeOutputVariable(m_tma_el_eta,		"tma_el_eta");
      systematicTree->makeOutputVariable(m_tma_el_phi,		"tma_el_phi");
      systematicTree->makeOutputVariable(m_tma_mu_e,		"tma_mu_e");
      systematicTree->makeOutputVariable(m_tma_mu_pt,		"tma_mu_pt");
      systematicTree->makeOutputVariable(m_tma_mu_eta,		"tma_mu_eta");
      systematicTree->makeOutputVariable(m_tma_mu_phi,		"tma_mu_phi");

      // top reco level

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
      systematicTree->makeOutputVariable(m_weight_max,                        "m_weight_max");

      systematicTree->makeOutputVariable(m_tma_top_pt,                        "tma_top_pt");
      systematicTree->makeOutputVariable(m_tma_top_eta,                       "tma_top_eta");
      systematicTree->makeOutputVariable(m_tma_top_phi,                       "tma_top_phi");
      systematicTree->makeOutputVariable(m_tma_top_e,                         "tma_top_e");
      systematicTree->makeOutputVariable(m_tma_top_m,                         "tma_top_m");
      systematicTree->makeOutputVariable(m_tma_top_y,                         "tma_top_y");

      systematicTree->makeOutputVariable(m_tma_tbar_pt,                       "tma_tbar_pt");
      systematicTree->makeOutputVariable(m_tma_tbar_eta,                      "tma_tbar_eta");
      systematicTree->makeOutputVariable(m_tma_tbar_phi,                      "tma_tbar_phi");
      systematicTree->makeOutputVariable(m_tma_tbar_e,                        "tma_tbar_e");
      systematicTree->makeOutputVariable(m_tma_tbar_m,                        "tma_tbar_m");
      systematicTree->makeOutputVariable(m_tma_tbar_y,                        "tma_tbar_y");

      systematicTree->makeOutputVariable(m_tma_av_top_pt,                        "tma_av_top_pt");
      systematicTree->makeOutputVariable(m_tma_av_top_eta,                       "tma_av_top_eta");
      systematicTree->makeOutputVariable(m_tma_av_top_phi,                       "tma_av_top_phi");
      systematicTree->makeOutputVariable(m_tma_av_top_e,                         "tma_av_top_e");
      systematicTree->makeOutputVariable(m_tma_av_top_m,                         "tma_av_top_m");
      systematicTree->makeOutputVariable(m_tma_av_top_y,                         "tma_av_top_y");

      systematicTree->makeOutputVariable(m_tma_ttbar_pt,                      "tma_ttbar_pt");
      systematicTree->makeOutputVariable(m_tma_ttbar_eta,                     "tma_ttbar_eta");
      systematicTree->makeOutputVariable(m_tma_ttbar_phi,                     "tma_ttbar_phi");
      systematicTree->makeOutputVariable(m_tma_ttbar_e,                       "tma_ttbar_e");
      systematicTree->makeOutputVariable(m_tma_ttbar_m,                       "tma_ttbar_m");
      systematicTree->makeOutputVariable(m_tma_ttbar_y,                       "tma_ttbar_y");
      systematicTree->makeOutputVariable(m_tma_ttbar_pout,                    "tma_ttbar_pout");

      systematicTree->makeOutputVariable(m_tma_nu_pt,                         "tma_nu_pt");
      systematicTree->makeOutputVariable(m_tma_nu_eta,                        "tma_nu_eta");
      systematicTree->makeOutputVariable(m_tma_nu_phi,                        "tma_nu_phi");
      systematicTree->makeOutputVariable(m_tma_nu_e,                          "tma_nu_e");
      systematicTree->makeOutputVariable(m_tma_nu_m,                          "tma_nu_m");
      systematicTree->makeOutputVariable(m_tma_nu_y,                          "tma_nu_y");

      systematicTree->makeOutputVariable(m_tma_nubar_pt,                      "tma_nubar_pt");
      systematicTree->makeOutputVariable(m_tma_nubar_eta,                     "tma_nubar_eta");
      systematicTree->makeOutputVariable(m_tma_nubar_phi,                     "tma_nubar_phi");
      systematicTree->makeOutputVariable(m_tma_nubar_e,                       "tma_nubar_e");
      systematicTree->makeOutputVariable(m_tma_nubar_m,                       "tma_nubar_m");
      systematicTree->makeOutputVariable(m_tma_nubar_y,                       "tma_nubar_y");

      systematicTree->makeOutputVariable(m_tma_Wp_pt,                         "tma_Wp_pt");
      systematicTree->makeOutputVariable(m_tma_Wp_eta,                        "tma_Wp_eta");
      systematicTree->makeOutputVariable(m_tma_Wp_phi,                        "tma_Wp_phi");
      systematicTree->makeOutputVariable(m_tma_Wp_e,                          "tma_Wp_e");
      systematicTree->makeOutputVariable(m_tma_Wp_m,                          "tma_Wp_m");
      systematicTree->makeOutputVariable(m_tma_Wp_y,                          "tma_Wp_y");

      systematicTree->makeOutputVariable(m_tma_Wm_pt,                         "tma_Wm_pt");
      systematicTree->makeOutputVariable(m_tma_Wm_eta,                        "tma_Wm_eta");
      systematicTree->makeOutputVariable(m_tma_Wm_phi,                        "tma_Wm_phi");
      systematicTree->makeOutputVariable(m_tma_Wm_e,                          "tma_Wm_e");
      systematicTree->makeOutputVariable(m_tma_Wm_m,                          "tma_Wm_m");
      systematicTree->makeOutputVariable(m_tma_Wm_y,                          "tma_Wm_y");

    }

  if ( topConfig()->doTopParticleLevel() ){

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pseudotop_mtop_param, "tma_pseudotop_mtop_param");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pseudotop1_mtop_param, "tma_pseudotop1_mtop_param");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pseudotop2_mtop_param, "tma_pseudotop2_mtop_param");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pseudotop3_mtop_param, "tma_pseudotop3_mtop_param");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pseudotop_mw,         "tma_pseudotop_mw");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pseudotop_rbq,        "tma_pseudotop_rbq");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_etdr,                 "tma_etdr");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_met,                  "tma_met");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_met_ex,               "tma_met_ex");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_met_ey,               "tma_met_ey");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_met_phi,              "tma_met_phi");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nbjets,                  "tma_nbjets");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_bjet_pt,              "tma_bjet_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_bjet_eta,             "tma_bjet_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_bjet_phi,             "tma_bjet_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_bjet_e,               "tma_bjet_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_njets,                "tma_njets");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_lead_jet_pt,          "tma_lead_jet_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_lead_bjet_pt,         "tma_lead_bjet_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_lead_el_pt,           "tma_lead_el_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_lead_mu_pt,           "tma_lead_mu_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_jet_pt,               "tma_jet_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_jet_eta,              "tma_jet_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_jet_phi,              "tma_jet_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_jet_e,                "tma_jet_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mlb_minavg,           "tma_mlb_minavg");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mlb_minavglow,        "tma_mlb_minavglow");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mlb_minavghigh,       "tma_mlb_minavghigh");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mlb_minmax,           "tma_mlb_minmax");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mlb_minmaxlow,        "tma_mlb_minmaxlow");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mlb_minmaxavg,        "tma_mlb_minmaxavg");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pTlb_1,               "tma_pTlb_1");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pTlb_2,               "tma_pTlb_2");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_dRlb_1,               "tma_dRlb_1");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_dRlb_2,               "tma_dRlb_2");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mll,                  "tma_mll");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pTll,                 "tma_pTll");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_dRll,                 "tma_dRll");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_mbb,                  "tma_mbb");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_pTbb,                 "tma_pTbb");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_dRbb,                 "tma_dRbb");

      // Leptons

      particleLevelTreeManager()->makeOutputVariable(m_tma_el_e,			  "tma_el_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_el_pt,			  "tma_el_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_el_eta,			  "tma_el_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_el_phi,			  "tma_el_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_mu_e,			  "tma_mu_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_mu_pt,			  "tma_mu_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_mu_eta,			  "tma_mu_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_mu_phi,			  "tma_mu_phi");


      // Pseudo-top

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_top_pt,               "tma_top_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_top_eta,              "tma_top_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_top_phi,              "tma_top_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_top_e,                "tma_top_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_top_m,                "tma_top_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_top_y,                "tma_top_y");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_tbar_pt,              "tma_tbar_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_tbar_eta,             "tma_tbar_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_tbar_phi,             "tma_tbar_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_tbar_e,               "tma_tbar_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_tbar_m,               "tma_tbar_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_tbar_y,               "tma_tbar_y");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_av_top_pt,            "tma_av_top_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_av_top_eta,           "tma_av_top_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_av_top_phi,           "tma_av_top_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_av_top_e,             "tma_av_top_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_av_top_m,             "tma_av_top_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_av_top_y,             "tma_av_top_y");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_pt,             "tma_ttbar_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_eta,            "tma_ttbar_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_phi,            "tma_ttbar_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_e,              "tma_ttbar_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_m,              "tma_ttbar_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_y,              "tma_ttbar_y");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_ttbar_pout,           "tma_ttbar_pout");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_n,                 "tma_nu_n");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_pt,                "tma_nu_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_eta,               "tma_nu_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_phi,               "tma_nu_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_e,                 "tma_nu_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_m,                 "tma_nu_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nu_y,                 "tma_nu_y");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nubar_pt,             "tma_nubar_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nubar_eta,            "tma_nubar_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nubar_phi,            "tma_nubar_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nubar_e,              "tma_nubar_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nubar_m,              "tma_nubar_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_nubar_y,              "tma_nubar_y");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wp_pt,                "tma_Wp_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wp_eta,               "tma_Wp_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wp_phi,               "tma_Wp_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wp_e,                 "tma_Wp_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wp_m,                 "tma_Wp_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wp_y,                 "tma_Wp_y");

      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wm_pt,                "tma_Wm_pt");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wm_eta,               "tma_Wm_eta");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wm_phi,               "tma_Wm_phi");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wm_e,                 "tma_Wm_e");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wm_m,                 "tma_Wm_m");
      particleLevelTreeManager()->makeOutputVariable(m_tma_particle_Wm_y,                 "tma_Wm_y");


  }
}
  
  ///-- saveEvent - run for every systematic and every event --///
  void MassEventSaver::saveEvent(const top::Event& event) 
  {
    // calculate here now the flat variables neccessary for the top mass analysis, want to avoid to recalculate them every time offline!
    m_tma_pseudotop_mtop_param=-99.;
    m_tma_pseudotop1_mtop_param=-99.;
    m_tma_pseudotop2_mtop_param=-99.;
    m_tma_pseudotop3_mtop_param=-99.;
    m_tma_pseudotop_mw=-99.;
    m_tma_pseudotop_rbq=-99.;
    m_tma_nbjets=0.;
    m_tma_njets=0.;
    m_tma_etdr=-99.;
    m_tma_met=-99.;
    m_tma_met_ex=-99.;
    m_tma_met_ey=-99.;
    m_tma_met_phi=-99.;
    m_tma_mlb_minavg=-99.;
    m_tma_mlb_minavglow=-99.;
    m_tma_mlb_minavghigh=-99.;
    m_tma_mlb_minmax=-99.;
    m_tma_mlb_minmaxlow=-99.;
    m_tma_mlb_minmaxavg=-99.;
    m_tma_lead_jet_pt=-99.;
    m_tma_lead_bjet_pt=-99.;
    m_tma_lead_el_pt=-99.;
    m_tma_lead_mu_pt=-99.;
    m_tma_pTlb_1=-99.;
    m_tma_pTlb_2=-99.;
    m_tma_dRlb_1=-99.;
    m_tma_dRlb_2=-99.;
    m_tma_mll=-99.;
    m_tma_pTll=-99.;
    m_tma_dRll=-99.;
    m_tma_mbb=-99.;
    m_tma_pTbb=-99.;
    m_tma_dRbb=-99.;
    m_tma_Rbq_avgLJ=-99.;
    m_tma_Rbq_leadLJ=-99.;
    m_tma_top_pt=-99.;
    m_tma_top_eta=-99.;
    m_tma_top_phi=-99.;
    m_tma_top_m=-99.;
    m_tma_top_e=-99.;
    m_tma_top_y=-99.;
    m_tma_tbar_pt=-99.;
    m_tma_tbar_eta=-99.;
    m_tma_tbar_phi=-99.;
    m_tma_tbar_m=-99.;
    m_tma_tbar_e=-99.;
    m_tma_tbar_y=-99.;
    m_tma_av_top_pt =-99.;
    m_tma_av_top_eta=-99.;
    m_tma_av_top_phi=-99.;
    m_tma_av_top_m=-99.;
    m_tma_av_top_e=-99.;
    m_tma_av_top_y=-99.;
    m_tma_ttbar_pt=-99.;
    m_tma_ttbar_eta=-99.;
    m_tma_ttbar_phi=-99.;
    m_tma_ttbar_m=-99.;
    m_tma_ttbar_e=-99.;
    m_tma_ttbar_y=-99.;
    m_tma_ttbar_pout=-99.;
    m_tma_nu_pt=-99.;
    m_tma_nu_eta=-99.;
    m_tma_nu_phi=-99.;
    m_tma_nu_m=-99.;
    m_tma_nu_e=-99.;
    m_tma_nu_y=-99.;
    m_tma_nubar_pt=-99.;
    m_tma_nubar_eta=-99.;
    m_tma_nubar_phi=-99.;
    m_tma_nubar_m=-99.;
    m_tma_nubar_e=-99.;
    m_tma_nubar_y=-99.;
    m_tma_Wp_pt=-99.;
    m_tma_Wp_eta=-99.;
    m_tma_Wp_phi=-99.;
    m_tma_Wp_m=-99.;
    m_tma_Wp_e=-99.;
    m_tma_Wp_y=-99.;
    m_tma_Wm_pt=-99.;
    m_tma_Wm_eta=-99.;
    m_tma_Wm_phi=-99.;
    m_tma_Wm_m=-99.;
    m_tma_Wm_e=-99.;
    m_tma_Wm_y=-99.;

    m_tma_bjet_pt.clear();
    m_tma_bjet_eta.clear();
    m_tma_bjet_phi.clear();
    m_tma_bjet_e.clear();

    m_tma_jet_pt.clear();
    m_tma_jet_eta.clear();
    m_tma_jet_phi.clear();
    m_tma_jet_e.clear();

    // Masses for pseudo-top definitions
    double mW  = 80.309e+03;
    m_tma_nbjets_85 = 0;
    m_tma_nbjets_77 = 0;
    m_tma_nbjets_70 = 0;
    m_tma_nbjets_60 = 0;

    // get vector of b-tagged jets
    for (const auto* const jetPtr : event.m_jets) {
      
      //if(jetPtr->isAvailable<char>("isbtagged_FixedCutBEff_77"))

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
	m_tma_nbjets = m_tma_nbjets_85;
      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_77"))
	m_tma_nbjets = m_tma_nbjets_77;
      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_70"))
	m_tma_nbjets = m_tma_nbjets_70;
      if(jetPtr->isAvailable<char>("isbtagged_MV2c10_FixedCutBEff_60"))
	m_tma_nbjets = m_tma_nbjets_60;
     

    
    }

    m_tma_bjet_pt.resize(m_tma_nbjets);
    m_tma_bjet_eta.resize(m_tma_nbjets);
    m_tma_bjet_phi.resize(m_tma_nbjets);
    m_tma_bjet_e.resize(m_tma_nbjets);

    m_tma_jet_pt.resize(m_tma_njets);
    m_tma_jet_eta.resize(m_tma_njets);
    m_tma_jet_phi.resize(m_tma_njets);
    m_tma_jet_e.resize(m_tma_njets);

    int i = 0;
    int j = 0;

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
      if(m_tma_nbjets >= 2){
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

    m_tma_el_e.clear();
    m_tma_el_pt.clear();
    m_tma_el_eta.clear();
    m_tma_el_phi.clear();

    m_tma_mu_e.clear();
    m_tma_mu_pt.clear();
    m_tma_mu_eta.clear();
    m_tma_mu_phi.clear();

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

      m_tma_el_e.push_back(elPtr->e());
      m_tma_el_pt.push_back(elPtr->pt());
      m_tma_el_eta.push_back(elPtr->eta());
      m_tma_el_phi.push_back(elPtr->phi());
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

      m_tma_mu_e.push_back(muPtr->e());
      m_tma_mu_pt.push_back(muPtr->pt());
      m_tma_mu_eta.push_back(muPtr->eta());
      m_tma_mu_phi.push_back(muPtr->phi());
    }

    m_tma_met	    = event.m_met->met();
    m_tma_met_ex    = event.m_met->mpx();
    m_tma_met_ey    = event.m_met->mpy();
    m_tma_met_phi   = event.m_met->phi();


    if(goodLeptons.size() == 1 && LJets.size() >= 2 && bJets.size() >= 2){ 
      
         if (goodElectrons.size() >= 1) m_tma_lead_el_pt = goodElectrons[0].Pt();
         if (goodMuons.size() >= 1)     m_tma_lead_mu_pt = goodMuons[0].Pt();
         m_tma_lead_bjet_pt = bJets[0].Pt();
         m_tma_lead_jet_pt = LJets[0].Pt();

         TLorentzVector lep = goodLeptons.at(0);
         TLorentzVector pb_lep, pb_had;
         if (bJets[0].DeltaR(lep) < bJets[1].DeltaR(lep)){
           pb_lep = bJets[0];
           pb_had = bJets[1];
         }
         else {
           pb_lep = bJets[1];
           pb_had = bJets[0];
         }

	 // Pseudo-top definitions

         TLorentzVector miss, t_lep, t_had;
         t_had = pb_had + LJets[0] + LJets[1];
         m_tma_pseudotop_mw = (LJets[0] + LJets[1]).M();
         m_tma_pseudotop_rbq = (pb_lep.Pt() + pb_had.Pt())/(LJets[0].Pt() + LJets[1].Pt());

         Double_t lE = lep.E();
         Double_t lX = lep.Px();
         Double_t lY = lep.Py();
         Double_t lZ = lep.Pz();

         Double_t nuE = event.m_met->met();
         Double_t nuX = event.m_met->mpx();
         Double_t nuY = event.m_met->mpy();

         Double_t wPz2 = pow(lE + nuE,2) - pow(lX + nuX,2) - pow(lY + nuY,2) - pow(mW,2);
         Double_t nuZ = 0.;

	 // Pseudo-top def. 0 (default)
         if (wPz2 >= 0.) nuZ = abs(sqrt(wPz2) - lZ) <= abs(-sqrt(wPz2) - lZ) ? (sqrt(wPz2) - lZ) : (-sqrt(wPz2) - lZ);
         else nuZ = -lZ;

         miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
         t_lep = pb_lep + lep + miss;
         m_tma_pseudotop_mtop_param = 0.5*(t_lep.M() + t_had.M());

	 if ( pseudotop == true ) {

	   // Pseudo-top def. 1

	   if (wPz2 >= 0.) nuZ = abs(sqrt(wPz2) - lZ) >= abs(-sqrt(wPz2) - lZ) ? (sqrt(wPz2) - lZ) : (-sqrt(wPz2) - lZ);
           else nuZ = -lZ;

           miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
           t_lep = pb_lep + lep + miss;
           m_tma_pseudotop1_mtop_param = 0.5*(t_lep.M() + t_had.M());

	   // Pseudo-top def. 2

	   Double_t nuZ_1 = sqrt(wPz2) - lZ;
	   Double_t nuZ_2 = -sqrt(wPz2) - lZ;
	   TLorentzVector miss_1, miss_2;
	   miss_1.SetPxPyPzE(nuX, nuY, nuZ_1, nuE);
	   miss_2.SetPxPyPzE(nuX, nuY, nuZ_2, nuE);
	   TLorentzVector tlep_1 = pb_lep + lep + miss_1;
	   TLorentzVector tlep_2 = pb_lep + lep + miss_2;

	   nuZ = abs(tlep_1.M() - t_had.M()) <= abs(tlep_2.M() - t_had.M()) ? nuZ_1 : nuZ_2;

           miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
           t_lep = pb_lep + lep + miss;
           m_tma_pseudotop2_mtop_param = 0.5*(t_lep.M() + t_had.M());

	   // Pseudo-top def. 3

	   Double_t bE = pb_lep.E();
	   Double_t bX = pb_lep.Px();
	   Double_t bY = pb_lep.Py();
	   Double_t bZ = pb_lep.Pz();

	   Double_t tPz2 = pow(bZ,2) - pow(pb_lep.M(),2) - pow(t_had.M(),2)
		+ pow(lE + nuE,2) - pow(lX + nuX,2) - pow(lY + nuY,2)
		+ 2*( (lE + nuE)*bE - (lX + nuX)*bX - (lY + nuY)*bY );
	   if (tPz2 >= 0.) nuZ = abs(sqrt(tPz2) - (lZ + bZ)) <= abs(-sqrt(tPz2) - (lZ + bZ)) ? (sqrt(tPz2) - (lZ + bZ)) : (-sqrt(tPz2) - (lZ + bZ));
	   else nuZ = - (lZ + bZ);

           miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
           t_lep = pb_lep + lep + miss;
           m_tma_pseudotop3_mtop_param = 0.5*(t_lep.M() + t_had.M());
	 //std::cout << pb_lep.Pt() << "\n" << pb_had.Pt() << "\n" << LJets[0].Pt() << "\n" << LJets[1].Pt() << "\n\n";
	 }
//       else if (m_tma_nbjets == 1){
//         m_tma_pseudotop_rbq = bJets[0].Pt()/((LJets[0].Pt() + LJets[1].Pt())*0.5);
//       }
      }

      // Dilepton
      if(m_tma_nbjets >= 2 && goodLeptons.size() > 1){ 
      
      m_tma_mbb  = -99.;
      m_tma_pTbb = -99.;
      m_tma_dRbb = -99.;

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
      double LBpair_avgMass = -99.;
      double LBpair1_dR = -99.;
      double LBpair2_dR = -99.;

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

      double Rbq_avgLJ  = -99.;
      double Rbq_leadLJ = -99.;
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
	
	
        // for dilepton channel only

	// Top reconstruction
	// Neutrino weighting, like in TopDileptonAnalysis

	if(lep_pos_set && lep_neg_set){

	  TLorentzVector b, bbar;
	  double deltaR_lep_pos_jet_1 = lep_pos.DeltaR(b1);
	  double deltaR_lep_neg_jet_2 = lep_neg.DeltaR(b2);
	  double distance_a = fabs(deltaR_lep_pos_jet_1 + deltaR_lep_neg_jet_2);

	  double deltaR_lep_pos_jet_2 = lep_pos.DeltaR(b2);
	  double deltaR_lep_neg_jet_1 = lep_neg.DeltaR(b1);
	  double distance_b = fabs(deltaR_lep_pos_jet_2 + deltaR_lep_neg_jet_1);

	  if( distance_a < distance_b){
	    b    = b1;
	    bbar = b2; }
	  else if (distance_b < distance_a){
	    b    = b2;
	    bbar = b1; }
	  else {
	    std::cout << "WARNING: Could not determine lepton-b pairings" <<  std::endl;
	    lep_pos.Print();
	    lep_neg.Print();
	    b2.Print();
	    b2.Print();
	    b    = b1;
	    bbar = b2; }

	  m_weight_max = 0.;
	  double m_weight_max_alt = 0.;

	  NeutrinoWeighter nuW     = NeutrinoWeighter(1, lep_pos.Pt() + lep_pos.Phi());// Ingnore the second argument,it's just a random string
	  NeutrinoWeighter nuW_alt = NeutrinoWeighter(1, lep_pos.Pt() + lep_pos.Eta() + m_tma_nbjets);//2
	  m_weight_max  = nuW.Reconstruct(lep_pos, lep_neg, b, bbar, m_tma_met_ex, m_tma_met_ey, m_tma_met_phi);
	  m_weight_max_alt = nuW_alt.Reconstruct(lep_neg, lep_pos, bbar, b, m_tma_met_ex, m_tma_met_ey, m_tma_met_phi);

	  if( m_weight_max_alt > m_weight_max){
	    nuW = nuW_alt;
	    m_weight_max = m_weight_max_alt; }

	  if(m_weight_max > 0.){

	    top   = nuW.GetTop();
	    tbar  = nuW.GetTbar();
            ttbar = nuW.GetTtbar();
            b     = nuW.GetB();
            bbar  = nuW.GetBbar();
            nu    = nuW.GetNu();
            nubar = nuW.GetNubar();

            TLorentzVector Wp, Wm;
            Wp = lep_pos + nu;
            Wm = lep_neg + nubar;

            m_tma_Wp_pt   = Wp.Pt();
            m_tma_Wp_eta  = Wp.Eta();
            m_tma_Wp_phi  = Wp.Phi();
            m_tma_Wp_m    = Wp.M();
            m_tma_Wp_e    = Wp.E();
            m_tma_Wp_y    = Wp.Rapidity();

            m_tma_Wm_pt   = Wm.Pt();
            m_tma_Wm_eta  = Wm.Eta();
            m_tma_Wm_phi  = Wm.Phi();
            m_tma_Wm_m    = Wm.M();
            m_tma_Wm_e    = Wm.E();
            m_tma_Wm_y    = Wm.Rapidity();

            m_tma_top_pt    = top.Pt();
            m_tma_top_eta   = top.Eta();
            m_tma_top_phi   = top.Phi();
            m_tma_top_m     = top.M();
            m_tma_top_e     = top.E();
            m_tma_top_y     = top.Rapidity();

            m_tma_tbar_pt   = tbar.Pt();
            m_tma_tbar_eta  = tbar.Eta();
            m_tma_tbar_phi  = tbar.Phi();
            m_tma_tbar_m    = tbar.M();
            m_tma_tbar_e    = tbar.E();
            m_tma_tbar_y    = tbar.Rapidity();

            m_tma_av_top_pt    = (m_tma_top_pt  + m_tma_tbar_pt)/2.;
            m_tma_av_top_eta   = (m_tma_top_eta + m_tma_tbar_eta)/2.;
            m_tma_av_top_phi   = (m_tma_top_phi + m_tma_tbar_phi)/2.;
            m_tma_av_top_m     = (m_tma_top_m   + m_tma_tbar_m)/2.;
            m_tma_av_top_e     = (m_tma_top_e   + m_tma_tbar_e)/2.;
            m_tma_av_top_y     = (m_tma_top_y   + m_tma_tbar_y)/2.;

            m_tma_ttbar_pt   = ttbar.Pt();
            m_tma_ttbar_eta  = ttbar.Eta();
            m_tma_ttbar_phi  = ttbar.Phi();
            m_tma_ttbar_m    = ttbar.M();
            m_tma_ttbar_e    = ttbar.E();
            m_tma_ttbar_y    = ttbar.Rapidity();
            m_tma_ttbar_pout = calculatePout( top, tbar );

            m_tma_nu_pt     = nu.Pt();
            m_tma_nu_eta    = nu.Eta();
            m_tma_nu_phi    = nu.Phi();
            m_tma_nu_m      = nu.M();
            m_tma_nu_e      = nu.E();
            m_tma_nu_y      = nu.Rapidity();

            m_tma_nubar_pt  = nubar.Pt();
            m_tma_nubar_eta = nubar.Eta();
            m_tma_nubar_phi = nubar.Phi();
            m_tma_nubar_m   = nubar.M();
            m_tma_nubar_e   = nubar.E();
            m_tma_nubar_y   = nubar.Rapidity();

	  }
//	  else { std::cout << "No top reconstruction" << std::endl; }
	}
      }
      
    ///-- Let the base class do all the hard work --///
    top::EventSaverFlatNtuple::saveEvent(event);

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

void MassEventSaver::saveParticleLevelEvent(const top::ParticleLevelEvent& plEvent){

  if( !topConfig()->doTopParticleLevel() ){
	return;
  }

  // Masses for pseudo-top definitions
  double mW  = 80.309e+03;
  double mZ  = 91.1876e+03;
  double mt  = 172.44e+03;

  std::vector<TLorentzVector> particle_bJets;
  std::vector<TLorentzVector> particle_LJets;
  std::vector<TLorentzVector> particle_goodLeptons;
  TLorentzVector lep_pos, lep_neg, nu, nubar, b, bbar, top, tbar, jet1, jet2;
  bool lep_pos_set = false;
  bool lep_neg_set = false;

  m_tma_particle_pseudotop_mtop_param=-99.;
  m_tma_particle_pseudotop1_mtop_param=-99.;
  m_tma_particle_pseudotop2_mtop_param=-99.;
  m_tma_particle_pseudotop3_mtop_param=-99.;
  m_tma_particle_pseudotop_mw=-99.;
  m_tma_particle_pseudotop_rbq=-99.;
  m_tma_particle_nbjets=0.;
  m_tma_particle_njets=0.;
  m_tma_particle_etdr=-99.;
  m_tma_particle_met=-99.;
  m_tma_particle_met_ex=-99.;
  m_tma_particle_met_ey=-99.;
  m_tma_particle_met_phi=-99.;
  m_tma_particle_mlb_minavg=-99.;
  m_tma_particle_mlb_minavglow=-99.;
  m_tma_particle_mlb_minavghigh=-99.;
  m_tma_particle_mlb_minmax=-99.;
  m_tma_particle_mlb_minmaxlow=-99.;
  m_tma_particle_mlb_minmaxavg=-99.;
  m_tma_particle_lead_jet_pt=-99.;
  m_tma_particle_lead_bjet_pt=-99.;
  m_tma_particle_lead_el_pt=-99.;
  m_tma_particle_lead_mu_pt=-99.;
  m_tma_particle_pTlb_1=-99.;
  m_tma_particle_pTlb_2=-99.;
  m_tma_particle_dRlb_1=-99.;
  m_tma_particle_dRlb_2=-99.;
  m_tma_particle_mll=-99.;
  m_tma_particle_pTll=-99.;
  m_tma_particle_dRll=-99.;
  m_tma_particle_mbb=-99.;
  m_tma_particle_pTbb=-99.;
  m_tma_particle_dRbb=-99.;
  m_tma_particle_top_pt=-99.;
  m_tma_particle_top_eta=-99.;
  m_tma_particle_top_phi=-99.;
  m_tma_particle_top_m=-99.;
  m_tma_particle_top_e=-99.;
  m_tma_particle_top_y=-99.;
  m_tma_particle_tbar_pt=-99.;
  m_tma_particle_tbar_eta=-99.;
  m_tma_particle_tbar_phi=-99.;
  m_tma_particle_tbar_m=-99.;
  m_tma_particle_tbar_e=-99.;
  m_tma_particle_tbar_y=-99.;
  m_tma_particle_av_top_pt =-99.;
  m_tma_particle_av_top_eta=-99.;
  m_tma_particle_av_top_phi=-99.;
  m_tma_particle_av_top_m=-99.;
  m_tma_particle_av_top_e=-99.;
  m_tma_particle_av_top_y=-99.;
  m_tma_particle_ttbar_pt=-99.;
  m_tma_particle_ttbar_eta=-99.;
  m_tma_particle_ttbar_phi=-99.;
  m_tma_particle_ttbar_m=-99.;
  m_tma_particle_ttbar_e=-99.;
  m_tma_particle_ttbar_y=-99.;
  m_tma_particle_ttbar_pout=-99.;
  m_tma_particle_nu_pt=-99.;
  m_tma_particle_nu_eta=-99.;
  m_tma_particle_nu_phi=-99.;
  m_tma_particle_nu_m=-99.;
  m_tma_particle_nu_e=-99.;
  m_tma_particle_nu_y=-99.;
  m_tma_particle_nubar_pt=-99.;
  m_tma_particle_nubar_eta=-99.;
  m_tma_particle_nubar_phi=-99.;
  m_tma_particle_nubar_m=-99.;
  m_tma_particle_nubar_e=-99.;
  m_tma_particle_nubar_y=-99;
  m_tma_particle_Wp_pt=-99.;
  m_tma_particle_Wp_eta=-99.;
  m_tma_particle_Wp_phi=-99.;
  m_tma_particle_Wp_m=-99.;
  m_tma_particle_Wp_e=-99.;
  m_tma_particle_Wp_y=-99.;
  m_tma_particle_Wm_pt=-99.;
  m_tma_particle_Wm_eta=-99.;
  m_tma_particle_Wm_phi=-99.;
  m_tma_particle_Wm_m=-99.;
  m_tma_particle_Wm_e=-99.;
  m_tma_particle_Wm_y=-99.;

  m_tma_particle_bjet_pt.clear();
  m_tma_particle_bjet_eta.clear();
  m_tma_particle_bjet_phi.clear();
  m_tma_particle_bjet_e.clear();

  m_tma_particle_jet_pt.clear();
  m_tma_particle_jet_eta.clear();
  m_tma_particle_jet_phi.clear();
  m_tma_particle_jet_e.clear();

  for (const auto & jetPtr : * plEvent.m_jets) {
    m_tma_particle_jet_pt.push_back(jetPtr->pt());
    m_tma_particle_jet_eta.push_back(jetPtr->eta());
    m_tma_particle_jet_phi.push_back(jetPtr->phi());
    m_tma_particle_jet_e.push_back(jetPtr->e());
    ++m_tma_particle_njets;

    if( jetPtr->auxdata<int>( "GhostBHadronsFinalCount" ) > 0){
      m_tma_particle_bjet_pt.push_back(jetPtr->pt());
      m_tma_particle_bjet_eta.push_back(jetPtr->eta());
      m_tma_particle_bjet_phi.push_back(jetPtr->phi());
      m_tma_particle_bjet_e.push_back(jetPtr->e());
      ++m_tma_particle_nbjets;

      TLorentzVector help;
      help.SetPtEtaPhiE(jetPtr->pt(), jetPtr->eta(), jetPtr->phi(), jetPtr->e());

      particle_bJets.push_back(help);
    }
    else {
      TLorentzVector help;
      help.SetPtEtaPhiE(jetPtr->pt(), jetPtr->eta(), jetPtr->phi(), jetPtr->e());

      particle_LJets.push_back(help);	
    }
  }

  m_tma_particle_bjet_pt.resize(m_tma_particle_nbjets);
  m_tma_particle_bjet_eta.resize(m_tma_particle_nbjets);
  m_tma_particle_bjet_phi.resize(m_tma_particle_nbjets);
  m_tma_particle_bjet_e.resize(m_tma_particle_nbjets);

  m_tma_particle_jet_pt.resize(m_tma_particle_njets);
  m_tma_particle_jet_eta.resize(m_tma_particle_njets);
  m_tma_particle_jet_phi.resize(m_tma_particle_njets);
  m_tma_particle_jet_e.resize(m_tma_particle_njets);

  std::vector<TLorentzVector> particle_goodElectrons, particle_goodMuons;

  m_tma_particle_el_e.clear();
  m_tma_particle_el_pt.clear();
  m_tma_particle_el_eta.clear();
  m_tma_particle_el_phi.clear();

  m_tma_particle_mu_e.clear();
  m_tma_particle_mu_pt.clear();
  m_tma_particle_mu_eta.clear();
  m_tma_particle_mu_phi.clear();

  for (const auto & elPtr : * plEvent.m_electrons) {

    if (elPtr->charge() > 0) {
        lep_pos.SetPtEtaPhiE(elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());
        lep_pos_set = true; }

    else if (elPtr->charge() < 0) {
        lep_neg.SetPtEtaPhiE(elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());
        lep_neg_set = true; }

    TLorentzVector help;
    help.SetPtEtaPhiE(elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());
    particle_goodLeptons.push_back(help);
    particle_goodElectrons.push_back(help);

    m_tma_particle_el_e.push_back(elPtr->e());
    m_tma_particle_el_pt.push_back(elPtr->pt());
    m_tma_particle_el_eta.push_back(elPtr->eta());
    m_tma_particle_el_phi.push_back(elPtr->phi());
  }

  for (const auto & muPtr : * plEvent.m_muons) {

    if (muPtr->charge() > 0) {
        lep_pos.SetPtEtaPhiE(muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());
        lep_pos_set = true; }

    else if (muPtr->charge() < 0) {
        lep_neg.SetPtEtaPhiE(muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());
        lep_neg_set = true; }

    TLorentzVector help;
    help.SetPtEtaPhiE(muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());
    particle_goodLeptons.push_back(help);
    particle_goodMuons.push_back(help);

    m_tma_particle_mu_e.push_back(muPtr->e());
    m_tma_particle_mu_pt.push_back(muPtr->pt());
    m_tma_particle_mu_eta.push_back(muPtr->eta());
    m_tma_particle_mu_phi.push_back(muPtr->phi());
  }

  m_tma_particle_met 	   = plEvent.m_met->met();
  m_tma_particle_met_ex    = plEvent.m_met->mpx();
  m_tma_particle_met_ey    = plEvent.m_met->mpy();
  m_tma_particle_met_phi   = plEvent.m_met->phi();


  /// ----------------------------------------//
  ///-- Pseudo Top Reconstruction: lepton+j --//
  /// ----------------------------------------//


  if (particle_goodLeptons.size() == 1 && particle_LJets.size() >= 2 && particle_bJets.size() >= 2) {

       if (particle_goodElectrons.size() >= 1) m_tma_particle_lead_el_pt = particle_goodElectrons[0].Pt();
       if (particle_goodMuons.size() >= 1)     m_tma_particle_lead_mu_pt = particle_goodMuons[0].Pt();
       m_tma_particle_lead_bjet_pt = particle_bJets[0].Pt();
       m_tma_particle_lead_jet_pt = particle_LJets[0].Pt();

       if (m_tma_particle_nbjets >= 2){
         TLorentzVector p_lep = particle_goodLeptons.at(0);
         TLorentzVector p_b_lep, p_b_had;
         if (particle_bJets[0].DeltaR(p_lep) < particle_bJets[1].DeltaR(p_lep)){
           p_b_lep = particle_bJets[0];
           p_b_had = particle_bJets[1];
         }
         else {
           p_b_lep = particle_bJets[1];
           p_b_had = particle_bJets[0];
         }

         TLorentzVector p_miss, p_t_lep, p_t_had;
         p_t_had = p_b_had + particle_LJets[0] + particle_LJets[1];
         m_tma_particle_pseudotop_mw = (particle_LJets[0] + particle_LJets[1]).M();
         m_tma_particle_pseudotop_rbq = (p_b_lep.Pt() + p_b_had.Pt())/(particle_LJets[0].Pt() + particle_LJets[1].Pt());

         Double_t lE = p_lep.E();
         Double_t lX = p_lep.Px();
         Double_t lY = p_lep.Py();
         Double_t lZ = p_lep.Pz();

         Double_t nuE = plEvent.m_met->met();
         Double_t nuX = plEvent.m_met->mpx();
         Double_t nuY = plEvent.m_met->mpy();

         Double_t wPz2 = pow(lE + nuE,2) - pow(lX + nuX,2) - pow(lY + nuY,2) - pow(mW,2);
         Double_t nuZ = 0.;

	 // Pseudo-top def. 0 (default)

         if (wPz2 >= 0.) nuZ = abs(sqrt(wPz2) - lZ) <= abs(-sqrt(wPz2) - lZ) ? (sqrt(wPz2) - lZ) : (-sqrt(wPz2) - lZ);
         else nuZ = -lZ;

         p_miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
         p_t_lep = p_b_lep + p_lep + p_miss;
         m_tma_particle_pseudotop_mtop_param = 0.5*(p_t_lep.M() + p_t_had.M());
         
	 if ( pseudotop == true ) {

	   // Pseudo-top def. 1

           if (wPz2 >= 0.) nuZ = abs(sqrt(wPz2) - lZ) >= abs(-sqrt(wPz2) - lZ) ? (sqrt(wPz2) - lZ) : (-sqrt(wPz2) - lZ);
           else nuZ = -lZ;

           p_miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
           p_t_lep = p_b_lep + p_lep + p_miss;
           m_tma_particle_pseudotop1_mtop_param = 0.5*(p_t_lep.M() + p_t_had.M());

	   // Pseudo-top def. 2

           Double_t nuZ_1 = sqrt(wPz2) - lZ;
           Double_t nuZ_2 = -sqrt(wPz2) - lZ;
           TLorentzVector miss_1, miss_2;
           miss_1.SetPxPyPzE(nuX, nuY, nuZ_1, nuE);
           miss_2.SetPxPyPzE(nuX, nuY, nuZ_2, nuE);
           TLorentzVector tlep_1 = p_b_lep + p_lep + miss_1;
           TLorentzVector tlep_2 = p_b_lep + p_lep + miss_2;

           nuZ = abs(tlep_1.M() - p_t_had.M()) <= abs(tlep_2.M() - p_t_had.M()) ? nuZ_1 : nuZ_2;

           p_miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
           p_t_lep = p_b_lep + p_lep + p_miss;
           m_tma_particle_pseudotop2_mtop_param = 0.5*(p_t_lep.M() + p_t_had.M());

	   // Pseudo-top def. 3

           Double_t bE = p_b_lep.E();
           Double_t bX = p_b_lep.Px();
           Double_t bY = p_b_lep.Py();
           Double_t bZ = p_b_lep.Pz();

           Double_t tPz2 = pow(bZ,2) - pow(p_b_lep.M(),2) - pow(p_t_had.M(),2)
                + pow(lE + nuE,2) - pow(lX + nuX,2) - pow(lY + nuY,2)
                + 2*( (lE + nuE)*bE - (lX + nuX)*bX - (lY + nuY)*bY );
           if (tPz2 >= 0.) nuZ = abs(sqrt(tPz2) - (lZ + bZ)) <= abs(-sqrt(tPz2) - (lZ + bZ)) ? (sqrt(tPz2) - (lZ + bZ)) : (-sqrt(tPz2) - (lZ + bZ));
           else nuZ = - (lZ + bZ);

           p_miss.SetPxPyPzE(nuX, nuY, nuZ, nuE);
           p_t_lep = p_b_lep + p_lep + p_miss;
           m_tma_particle_pseudotop3_mtop_param = 0.5*(p_t_lep.M() + p_t_had.M());
         }
       }

//       else if (m_tma_particle_nbjets == 1){
//         m_tma_particle_pseudotop_rbq = particle_bJets[0].Pt()/(particle_LJets[0].Pt() + particle_LJets[1].Pt())/2.;
//       }

  }

  if(m_tma_particle_nbjets >= 2 && particle_goodLeptons.size() == 2){ 

      m_tma_particle_mbb  = -99.;
      m_tma_particle_pTbb = -99.;
      m_tma_particle_dRbb = -99.;

      // Sort b-tagged jets by pT (*BP* or by MV2)  
      TLorentzVector pb1;
      TLorentzVector pb2;
      if(particle_bJets[0].Pt() >= particle_bJets[1].Pt()){
	pb1 = particle_bJets[0];
	pb2 = particle_bJets[1];
      }
      else{
	pb1 = particle_bJets[1];
	pb2 = particle_bJets[0];
      }
      
      m_tma_particle_mbb  = (pb1 + pb2).M();
      m_tma_particle_pTbb = (pb1 + pb2).Pt();
      m_tma_particle_dRbb = pb1.DeltaR(pb2);

      // Sort leptons by pT  
      TLorentzVector pL1;
      TLorentzVector pL2;
      if(particle_goodLeptons.at(0).Pt() >= particle_goodLeptons.at(1).Pt()){
	pL1 = particle_goodLeptons.at(0);
	pL2 = particle_goodLeptons.at(1);
      }
      else{
	pL1 = particle_goodLeptons.at(1);
	pL2 = particle_goodLeptons.at(0);
      }

	//Pairing decision             
	TLorentzVector pL1b1 = pL1 + pb1;
	TLorentzVector pL2b2 = pL2 + pb2;
	TLorentzVector pL1b2 = pL1 + pb2;
	TLorentzVector pL2b1 = pL2 + pb1;
	double pavgMass1 = (pL1b1.M() + pL2b2.M())/2 ;
	double pavgMass2 = (pL1b2.M() + pL2b1.M())/2 ;
	
	TLorentzVector pLBpair1;
	TLorentzVector pLBpair2;
	TLorentzVector pLBpair1_reject;
	TLorentzVector pLBpair2_reject;
	double pLBpair_avgMass = -99.;
	double pLBpair1_dR = -99;
	double pLBpair2_dR = -99;
	
	if( pavgMass1 <= pavgMass2 ){
	  pLBpair1 = pL1b1;
	  pLBpair2 = pL2b2;
	  pLBpair1_reject = pL1b2;
	  pLBpair2_reject = pL2b1;
	  pLBpair_avgMass = pavgMass1;
	  pLBpair1_dR = pb1.DeltaR(pL1);
	  pLBpair2_dR = pb2.DeltaR(pL2);
	}
	else{
	  pLBpair1 = pL1b2;
	  pLBpair2 = pL2b1;
	  pLBpair1_reject = pL1b1;
	  pLBpair2_reject = pL2b2;
	  pLBpair_avgMass = pavgMass2;
	  pLBpair1_dR = pb2.DeltaR(pL1);
	  pLBpair2_dR = pb1.DeltaR(pL2);
	}

        m_tma_particle_etdr = (pL1.Et()*pLBpair1_dR + pL2.Et()*pLBpair2_dR)/2.;
	m_tma_particle_mlb_minavg     = pLBpair_avgMass; 
	
	if(pLBpair1.M() < pLBpair2.M()){
	  m_tma_particle_mlb_minavglow   = pLBpair1.M();
	  m_tma_particle_mlb_minavghigh  = pLBpair2.M();
	}
	else{
	  m_tma_particle_mlb_minavglow   = pLBpair2.M();
	  m_tma_particle_mlb_minavghigh  = pLBpair1.M();
	}
	
	m_tma_particle_pTlb_1 = pLBpair1.Pt();
	m_tma_particle_pTlb_2 = pLBpair2.Pt();
	
	m_tma_particle_dRlb_1 = pLBpair1_dR;
	m_tma_particle_dRlb_2 = pLBpair2_dR;
	
	m_tma_particle_mll    = (pL1 + pL2).M();
	m_tma_particle_pTll   = (pL1 + pL2).Pt();
	m_tma_particle_dRll   = pL1.DeltaR(pL2);


       if( lep_pos_set && lep_neg_set ) { 				// OS
	// Neutrinos

	const xAOD::TruthParticleContainer* neutrinos{nullptr};
	top::check(evtStore()->retrieve(neutrinos, "TruthNeutrinos"), "Failed to retrieve Truth Neutrinos");

	bool nu_set     = false;
        bool nubar_set  = false;
        int number_of_tau_neutrinos = 0;
        if (neutrinos != nullptr) {
           for (const auto& neutrino : *neutrinos) {
                ++m_tma_particle_nu_n;
                if( abs(neutrino->pdgId()) == 16) ++number_of_tau_neutrinos;
                   if(!nu_set || !nubar_set){
                      if( neutrino->pdgId() > 0 && !nu_set){
                         nu.SetPtEtaPhiE(neutrino->pt(), neutrino->eta(), neutrino->phi(), neutrino->e());
                         m_tma_particle_nu_pt   = nu.Pt();
                         m_tma_particle_nu_eta  = nu.Eta();
                         m_tma_particle_nu_phi  = nu.Phi();
                         m_tma_particle_nu_e    = nu.E();
                         m_tma_particle_nu_m    = nu.M();
                         m_tma_particle_nu_y    = nu.Rapidity();
                         nu_set = true; }
                      if( neutrino->pdgId() < 0 && !nubar_set){
                         nubar.SetPtEtaPhiE(neutrino->pt(), neutrino->eta(), neutrino->phi(), neutrino->e());
                         m_tma_particle_nubar_pt  = nubar.Pt();
                         m_tma_particle_nubar_eta = nubar.Eta();
                         m_tma_particle_nubar_phi = nubar.Phi();
                         m_tma_particle_nubar_e   = nubar.E();
                         m_tma_particle_nubar_m   = nubar.M();
                         m_tma_particle_nubar_y   = nubar.Rapidity();

                         nubar_set = true; }
                   }
            }
        }

	/// ----------------------------------------//
	///-- Pseudo Top Reconstruction: dilepton --//
	/// ----------------------------------------//

	if(m_tma_particle_nbjets > 0 && m_tma_particle_njets > 1){

	  if(m_tma_particle_nbjets > 1){
	     jet1.SetPtEtaPhiE(m_tma_particle_bjet_pt[0], m_tma_particle_bjet_eta[0], m_tma_particle_bjet_phi[0], m_tma_particle_bjet_e[0]);
	     jet2.SetPtEtaPhiE(m_tma_particle_bjet_pt[1], m_tma_particle_bjet_eta[1], m_tma_particle_bjet_phi[1], m_tma_particle_bjet_e[1]); }
	  else {
	     jet1.SetPtEtaPhiE(m_tma_particle_bjet_pt[0], m_tma_particle_bjet_eta[0], m_tma_particle_bjet_phi[0], m_tma_particle_bjet_e[0]);
	     if (m_tma_particle_jet_pt[0] != m_tma_particle_bjet_pt[0]){
	        jet2.SetPtEtaPhiE(m_tma_particle_jet_pt[0], m_tma_particle_jet_eta[0], m_tma_particle_jet_phi[0], m_tma_particle_jet_e[0]);}
	     else {
	        jet2.SetPtEtaPhiE(m_tma_particle_jet_pt[1], m_tma_particle_jet_eta[1], m_tma_particle_jet_phi[1], m_tma_particle_jet_e[1]);}
	   }

	
        TLorentzVector Wp, Wm, top_a, tbar_a, top_b, tbar_b;

        Wp = lep_pos + nu;
        Wm = lep_neg + nubar;

        top_a  = Wp + jet1;
        top_b  = Wp + jet2;

        tbar_a = Wm + jet2;
        tbar_b = Wm + jet1;

        double diff_a = fabs(top_a.M() - mt) + fabs(tbar_a.M() - mt);
        double diff_b = fabs(top_b.M() - mt) + fabs(tbar_b.M() - mt);
        if(diff_a < diff_b){ // A is the correct combination
          top  = top_a;
          tbar = tbar_a;
        } else if (diff_a > diff_b){ // B is the right combination
          top  = top_b;
          tbar = tbar_b;
        } else {
          top  = top_a;
          tbar = tbar_a;
        }

        TLorentzVector ttbar = top + tbar;

        m_tma_particle_Wp_pt   = Wp.Pt();
        m_tma_particle_Wp_eta  = Wp.Eta();
        m_tma_particle_Wp_phi  = Wp.Phi();
        m_tma_particle_Wp_m    = Wp.M();
        m_tma_particle_Wp_e    = Wp.E();
        m_tma_particle_Wp_y    = Wp.Rapidity();

        m_tma_particle_Wm_pt   = Wm.Pt();
        m_tma_particle_Wm_eta  = Wm.Eta();
        m_tma_particle_Wm_phi  = Wm.Phi();
        m_tma_particle_Wm_m    = Wm.M();
        m_tma_particle_Wm_e    = Wm.E();
        m_tma_particle_Wm_y    = Wm.Rapidity();

        m_tma_particle_top_pt        = top.Pt();
        m_tma_particle_top_eta      = top.Eta();
        m_tma_particle_top_phi      = top.Phi();
        m_tma_particle_top_m          = top.M();
        m_tma_particle_top_e          = top.E();
        m_tma_particle_top_y          = top.Rapidity();

        m_tma_particle_tbar_pt      = tbar.Pt();
        m_tma_particle_tbar_eta     = tbar.Eta();
        m_tma_particle_tbar_phi     = tbar.Phi();
        m_tma_particle_tbar_m        = tbar.M();
        m_tma_particle_tbar_e        = tbar.E();
        m_tma_particle_tbar_y        = tbar.Rapidity();

        m_tma_particle_av_top_pt    = (m_tma_particle_top_pt  + m_tma_particle_tbar_pt)/2.;
        m_tma_particle_av_top_eta   = (m_tma_particle_top_eta + m_tma_particle_tbar_eta)/2.;
        m_tma_particle_av_top_phi   = (m_tma_particle_top_phi + m_tma_particle_tbar_phi)/2.;
        m_tma_particle_av_top_m     = (m_tma_particle_top_m   + m_tma_particle_tbar_m)/2.;
        m_tma_particle_av_top_e     = (m_tma_particle_top_e   + m_tma_particle_tbar_e)/2.;
	m_tma_particle_av_top_y     = (m_tma_particle_top_y   + m_tma_particle_tbar_y)/2.;

        m_tma_particle_ttbar_pt     = ttbar.Pt();
        m_tma_particle_ttbar_eta    = ttbar.Eta();
        m_tma_particle_ttbar_phi    = ttbar.Phi();
        m_tma_particle_ttbar_m      = ttbar.M();
        m_tma_particle_ttbar_e      = ttbar.E();
        m_tma_particle_ttbar_y      = ttbar.Rapidity();
        m_tma_particle_ttbar_pout   = calculatePout( top, tbar );

	}

	if (m_tma_njets >=2 && m_tma_nbjets >= 2) {
          double mll = (particle_goodLeptons[0] + particle_goodLeptons[1]).M();
          if( lep_pos_set && lep_neg_set && 						// OS
 	    ((particle_goodElectrons.size() == 1 && particle_goodMuons.size() == 1) || 	// emu
	     (mll > 20e+03 && fabs(mll - mZ) > 10e+03)) ){				// mumu/ee

 	    TLorentzVector Wp_a, Wp_b, Wm_a, Wm_b, top_a, top_b, tbar_a, tbar_b;
	    TLorentzVector Wp, Wm, top, tbar;

	    // Try both combinations of nus and leps (knowing only the leptons sign)
	    Wp_a = nu + lep_pos;
	    Wm_a = nubar + lep_neg;
	    Wp_b = nubar + lep_pos;
	    Wm_b = nu + lep_neg;

            double diff_a = fabs(Wp_a.M() - mW) + fabs(Wm_a.M() - mW);
            double diff_b = fabs(Wp_b.M() - mW) + fabs(Wm_b.M() - mW);
            if(diff_a <= diff_b){ // A is the correct combination
              Wp  = Wp_a;
              Wm  = Wm_a;
            } else if (diff_a > diff_b){ // B is the right combination
              Wp  = Wp_b;
              Wm  = Wm_b;
            }

	    top_a  = Wp + particle_bJets[0];
	    tbar_a = Wm + particle_bJets[1];
	    top_b  = Wp + particle_bJets[1];
	    tbar_b = Wm + particle_bJets[0];
	    diff_a = fabs(top_a.M() - mt) + fabs(tbar_a.M() - mt);
            diff_b = fabs(top_b.M() - mt) + fabs(tbar_b.M() - mt);
            if(diff_a <= diff_b){ // A is the correct combination
              top  = top_a;
              tbar = tbar_a;
            } else if (diff_a > diff_b){ // B is the right combination
              top  = top_b;
              tbar = tbar_b;
            }

	    m_tma_particle_pseudotop_mtop_param = 0.5*(top.M() + tbar.M());

          }
	}

     }


  }


top::EventSaverFlatNtuple::saveParticleLevelEvent(plEvent);

}

}

