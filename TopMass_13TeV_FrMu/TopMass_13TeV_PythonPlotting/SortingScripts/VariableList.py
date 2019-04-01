#! /usr/bin/python                                                                                                                                                                                         

import os
import sys
import glob

def ReturnVariableListTemplate(Flag, Channel):
    VariableList = []
    if Channel != "dilepton":
        VariableList.append(["tma_klf_mtop_param",  75, 125.0,  200.0,  True, "h_mtop_param",   "m_{top}^{reco} [GeV] (KLFitter)"])
        VariableList.append(["tma_klf_orig_mw",     55,  55.0,  110.0,  True, "h_mw_orig",      "m_{W}^{reco} [GeV]"])
        VariableList.append(["tma_klf_orig_rbq",    54,   0.3,    3.0,  True, "h_rbq_orig",     "R_{bq}^{reco}"])
    else:
        VariableList.append(["tma_mlb_minmaxavg/1000.0",    70, 30.0,  170.0,  True, "h_mlb",   "m_{lb}^{reco} [GeV]"])        

    return VariableList


def ReturnVariableListSimple(Flag, Channel, BDTFlag):
    #Pi    = math.pi
    VariableList = []

    VariableList.append(["el_pt[0]/1000.0",         25,    0.0, 250.0,  True, "h_el_pt",       "Electron E_{T} [GeV]"])
    VariableList.append(["el_eta[0]",               22,  -2.75,  2.75,  True, "h_el_eta",      "Electron #eta"])
    VariableList.append(["el_phi[0]",               20, -3.141, 3.141,  True, "h_el_phi",      "Electron #phi"])
    VariableList.append(["mu_pt[0]/1000.0",         25,    0.0, 250.0,  True, "h_mu_pt",       "Muon p_{T} [GeV]"])
    VariableList.append(["mu_eta[0]",               22,  -2.75,  2.75,  True, "h_mu_eta",      "Muon #eta"])
    VariableList.append(["mu_phi[0]",               20, -3.141, 3.141,  True, "h_mu_phi",      "Muon #phi"])
    VariableList.append(["jet_pt[0]/1000.0",        70,    0.0, 350.0,  True, "h_jet0_pt",     "Leading jet p_{T} [GeV]"])
    VariableList.append(["jet_eta[0]",              22,  -2.75,  2.75,  True, "h_jet0_eta",    "Leading jet #eta"])
    VariableList.append(["jet_phi[0]",              20, -3.141, 3.141,  True, "h_jet0_phi",    "Leading jet #phi"])
    VariableList.append(["jet_pt[1]/1000.0",        44,    0.0, 220.0,  True, "h_jet1_pt",     "Second jet p_{T} [GeV]"])
    VariableList.append(["jet_eta[1]",              22,  -2.75,  2.75,  True, "h_jet1_eta",    "Second jet #eta"])
    VariableList.append(["jet_phi[1]",              20, -3.141, 3.141,  True, "h_jet1_phi",    "Second jet #phi"])
    VariableList.append(["jet_pt[2]/1000.0",        40,    0.0, 200.0,  True, "h_jet2_pt",     "Third jet p_{T} [GeV]"])
    VariableList.append(["jet_eta[2]",              22,  -2.75,  2.75,  True, "h_jet2_eta",    "Third jet #eta"])
    VariableList.append(["jet_phi[2]",              20, -3.141, 3.141,  True, "h_jet2_phi",    "Third jet #phi"])
    VariableList.append(["jet_pt/1000.0",           30,    0.0, 300.0,  True, "h_jet_pt",      "All jets p_{T} [GeV]"])
    VariableList.append(["jet_eta",                 22,  -2.75,  2.75,  True, "h_jet_eta",     "All jets #eta"])
    VariableList.append(["jet_phi",                 20, -3.141,  3.141, True, "h_jet_phi",     "All jets #phi"])
    VariableList.append(["tma_njets",                7,  1.5,    8.5,   True, "h_jet_n",       "Number of jets"])
    VariableList.append(["tma_nbjets_70",            4,  0.5,    4.5,   True, "h_bjet_n",      "Number of b-tagged jets (70% WP)"])
    VariableList.append(["tma_met/1000.0",          60,  0.0,  300.0,   True, "h_met",         "Missing E_T [GeV]"])
    if Channel == "dilepton":
        VariableList.append(["tma_mlb_minmaxavg/1000.0",    70, 30.0,  170.0,  True, "h_mlb",          "m_{lb}^{reco} [GeV]"])
        VariableList.append(["tma_mlb_minmaxavg/1000.0",   150,  0.0,  300.0,  True, "h_mlb_moreBins", "m_{lb}^{reco} [GeV]"])
        # for assignment with smallest average mass:
        VariableList.append(["tma_pTlb_1/1000.0",           50,  0.0,  500.0,  True, "h_pTlb_1",  "p_{T}(lb) [GeV]"])
        #VariableList.append(["tma_pTlb_2/1000.0",           50,  0.0,  500.0,  True, "h_pTlb_2",  "p_{T}(lb) [GeV]"])
        VariableList.append(["tma_pTlb_2/1000.0",           50,  0.0,  500.0,  True, "h_pTlb_1",  "p_{T}(lb) [GeV]"])


        VariableList.append(["tma_pTlb_1/1000.0+tma_pTlb_2/1000.0", 50,  0.0,  500.0,  True, "h_pTlb",  "p_{T}(lb) [GeV]"]) # need to figure out how to fill two variables into project function
        VariableList.append(["tma_dRlb_1",                  45,  0.0,  4.5, True, "h_dRlb_1",  "#DeltaR (lb)"])
        VariableList.append(["tma_dRlb_2",                  45,  0.0,  4.5, True, "h_dRlb_2",  "#DeltaR (lb)"])
        
        VariableList.append(["tma_mll/1000.0",              60,  0.0,  600.0, True, "h_mll",     "m(ll) [GeV]"])
        VariableList.append(["tma_pTll/1000.0",             60,  0.0,  300.0, True, "h_pTll",    "p_{T}(ll) [GeV]"])
        VariableList.append(["tma_dRll",                    50,  0.0,    5.0, True, "h_dRll",    "#DeltaR (ll)"])
        VariableList.append(["tma_mbb/1000.0",              40,  0.0,  800.0, True, "h_mbb",     "m(bb) [GeV]"])
        VariableList.append(["tma_pTbb/1000.0",             40,  0.0,  400.0, True, "h_pTbb",    "p_{T}(bb) [GeV]"])
        VariableList.append(["tma_dRbb",                    50,  0.0,    5.0, True, "h_dRbb",    "#DeltaR (bb)"])
    else:
        VariableList.append(["tma_klf_mtop_param",        75, 125.0,  200.0,   True, "h_mtop_param",  "m_{top}^{reco} [GeV] (KLFitter)"])
        VariableList.append(["tma_klf_orig_mw",           55,  55.0,  110.0,   True, "h_mw_orig",     "m_{W}^{reco} [GeV]"])
        VariableList.append(["tma_klf_orig_rbq",          54,   0.3,    3.0,   True, "h_rbq_orig",    "R_{bq}^{reco}"])
        VariableList.append(["klfitter_logLikelihood[0]", 64, -70.0,  -38.0,   True, "h_logLH",       "--log-LH (KLFitter)"])
        VariableList.append(["klf_orig_toplep_pt",        45,   0.0,  450.0,   True, "h_topLep_pt",   "Leptonic top quark p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_toplep_eta",       56,  -5.6,    5.6,   True, "h_topLep_eta",  "Leptonic top quark #eta (KLFitter)"])
        #VariableList.append(["klf_orig_toplep_phi",       20,  -3.141,  3.141, True, "h_topLep_phi",  "Leptonic top quark #phi (KLFitter)"])
        VariableList.append(["klf_orig_tophad_pt",        45,   0.0,  450.0,   True, "h_topHad_pt",   "Hadronic top quark p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_tophad_eta",       56,  -5.6,    5.6,   True, "h_topHad_eta",  "Hadronic top quark #eta (KLFitter)"])
        #VariableList.append(["klf_orig_tophad_phi",       20,  -3.141,  3.141, True, "h_topHad_phi",  "Hadronic top quark #phi (KLFitter)"])
        VariableList.append(["klf_orig_ttbar_pt",         35,   0.0,  350.0,   True, "h_ttbar_pt",    "t#bar{t} p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_ttbar_eta",        56,  -5.6,    5.6,   True, "h_ttbar_eta",   "t#bar{t} #eta (KLFitter)"])
        #VariableList.append(["klf_orig_ttbar_phi",        20,  -3.141,  3.141, True, "h_ttbar_phi",   "t#bar{t} #phi (KLFitter)"])
        VariableList.append(["klf_orig_Wlep_pt",          35,   0.0,  350.0,   True, "h_WLep_pt",     "Leptonic W boson p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_Wlep_eta",         56,  -5.6,    5.6,   True, "h_WLep_eta",    "Leptonic W boson #eta (KLFitter)"])
        #VariableList.append(["klf_orig_Wlep_phi",         20,  -3.141,  3.141, True, "h_WLep_phi",    "Leptonic W boson #phi (KLFitter)"])
        VariableList.append(["klf_orig_Whad_pt",          35,   0.0,  350.0,   True, "h_WHad_pt",     "Hadronic W boson p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_Whad_eta",         56,  -5.6,    5.6,   True, "h_WHad_eta",    "Hadronic W boson #eta (KLFitter)"])
        #VariableList.append(["klf_orig_Whad_phi",         20,  -3.141,  3.141, True, "h_WHad_phi",    "Hadronic W boson #phi (KLFitter)"])
        VariableList.append(["klf_orig_dR_bb",            50,   0.0,    5.0,   True, "h_dRbb",        "#DeltaR (bb) (KLFitter)"])
        VariableList.append(["klf_orig_dR_qq_W",          50,   0.0,    5.0,   True, "h_dRqqW",       "#DeltaR (qq) (KLFitter)"])
        #VariableList.append(["klf_orig_ttbar_m",          90, 200.0, 1200.0,   True, "h_ttbar_m",     "t#bar{t} mass [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_mlb",             220,   0.0,  220.0,   True, "h_mlb",        "m_{lb}^{reco} [GeV] (KLFitter)"])
        VariableList.append(["klf_orig_ptlb",             35,   0.0,  350.0,   True, "h_ptlb",       "p_{T,lb}^{reco} [GeV] (KLFitter)"])

        if BDTFlag:
            VariableList.append(["bdtOutput_noWC",                              65, -0.76, 0.54,  True, "h_BDT_noWC",    "r_{BDT}"])
            VariableList.append(["bdtOutput_withWC",                            65, -0.76, 0.54,  True, "h_BDT_withWC",  "r_{BDT} (trained with window cuts)"])
            VariableList.append(["DNN_Olaf_4j_layer_36_128_256_128_64_8_1",     50,  0.0,  1.0,   True, "h_DNN_Olaf_4j", "r_{DNN} (4j training)"])
            VariableList.append(["DNN_Olaf_5j_layer_36_60_51_42_33_24_15_1_V2", 50,  0.0,  1.0,   True, "h_DNN_Olaf_5j", "r_{DNN} (5j training)"])


    return VariableList


