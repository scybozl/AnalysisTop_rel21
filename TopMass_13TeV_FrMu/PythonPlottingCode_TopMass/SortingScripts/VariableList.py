#! /usr/bin/python                                                                                                                                                                                         

import os
import sys
import glob

def ReturnVariableListTemplate(Flag, Channel):
    VariableList = []
    if Channel != "dilepton":
        VariableList.append(["tma_klfitter_mtop_param[0]",  75, 125.0, 200.0,  True, "h_mtop_param",   "m_{top}^{reco} [GeV] (KLFitter)"])
        VariableList.append(["tma_original_mw[0]",          55, 55.0,  110.0,  True, "h_mw_orig",      "m_{W}^{reco} [GeV]"])
        VariableList.append(["tma_original_rbq[0]",         54,  0.3,    3.0,  True, "h_rbq_orig",     "R_{bq}^{reco}"])
    else:
        VariableList.append(["tma_mlb_minmaxavg/1000.0",    70, 30.0,  170.0,  True, "h_mlb",          "m_{lb}^{reco} [GeV]"])        

    return VariableList

def ReturnVariableListSimple(Flag, Channel):
    #Pi    = math.pi
    VariableList = []

    VariableList.append(["el_pt[0]/1000.0",         25,    0.0, 250.0,  True, "h_el_pt",       "Electron E_{T} [GeV]"])
    VariableList.append(["el_eta[0]",               22,  -2.75,  2.75,  True, "h_el_eta",      "Electron #eta"])
    VariableList.append(["el_phi[0]",               20, -3.141, 3.141,  True, "h_el_phi",      "Electron #phi"])
    VariableList.append(["mu_pt[0]/1000.0",         25,    0.0, 250.0,  True, "h_mu_pt",       "Muon p_{T} [GeV]"])
    VariableList.append(["mu_eta[0]",               22,  -2.75,  2.75,  True, "h_mu_eta",      "Muon #eta"])
    VariableList.append(["mu_phi[0]",               20, -3.141, 3.141,  True, "h_mu_phi",      "Muon #phi"])
    VariableList.append(["jet_pt[0]/1000.0",        50,    0.0, 500.0,  True, "h_jet0_pt",     "Leading jet p_{T} [GeV]"])
    VariableList.append(["jet_eta[0]",              22,  -2.75,  2.75,  True, "h_jet0_eta",    "Leading jet #eta"])
    VariableList.append(["jet_phi[0]",              20, -3.141, 3.141,  True, "h_jet0_phi",    "Leading jet #phi"])
    VariableList.append(["jet_pt[1]/1000.0",        33,    0.0, 330.0,  True, "h_jet1_pt",     "Second jet p_{T} [GeV]"])
    VariableList.append(["jet_eta[1]",              22,  -2.75,  2.75,  True, "h_jet1_eta",    "Second jet #eta"])
    VariableList.append(["jet_phi[1]",              20, -3.141, 3.141,  True, "h_jet1_phi",    "Second jet #phi"])
    VariableList.append(["jet_pt[2]/1000.0",        30,    0.0, 300.0,  True, "h_jet2_pt",     "Third jet p_{T} [GeV]"])
    VariableList.append(["jet_eta[2]",              22,  -2.75,  2.75,  True, "h_jet2_eta",    "Third jet #eta"])
    VariableList.append(["jet_phi[2]",              20, -3.141, 3.141,  True, "h_jet2_phi",    "Third jet #phi"])
    VariableList.append(["jet_pt/1000.0",           30,    0.0, 300.0,  True, "h_jet_pt",      "All jets p_{T} [GeV]"])
    VariableList.append(["jet_eta",                 22,  -2.75,  2.75,  True, "h_jet_eta",     "All jets #eta"])
    VariableList.append(["jet_phi",                 20, -3.141,  3.141, True, "h_jet_phi",     "All jets #phi"])
    VariableList.append(["tma_njets",                7,  1.5,    8.5,   True, "h_jet_n",       "Number of jets"])
    VariableList.append(["tma_nbjets",               4,  0.5,    4.5,   True, "h_bjet_n",      "Number of b-tagged jets (77% WP)"])
    VariableList.append(["tma_met/1000.0",          40,  0.0,  400.0,   True, "h_met",         "Missing E_T [GeV]"])
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
        VariableList.append(["tma_klfitter_mtop_param[0]",  100, 50.0,  550.0,  True, "h_mtop_param_moreBins",   "m_{top}^{reco} [GeV] (KLFitter)"])
        VariableList.append(["tma_original_mw[0]",           60,  0.0,  300.0,  True, "h_mw_orig_moreBins",      "m_{W}^{reco} [GeV]"])
        VariableList.append(["tma_original_rbq[0]",          70,  0.0,    3.5,  True, "h_rbq_orig_moreBins",     "R_{bq}^{reco}"])
        VariableList.append(["tma_klfitter_mtop_param[0]",  75, 125.0, 200.0,  True, "h_mtop_param",   "m_{top}^{reco} [GeV] (KLFitter)"])
        VariableList.append(["tma_original_mw[0]",          55, 55.0,  110.0,  True, "h_mw_orig",      "m_{W}^{reco} [GeV]"])
        VariableList.append(["tma_original_rbq[0]",         54,  0.3,    3.0,  True, "h_rbq_orig",     "R_{bq}^{reco}"])
        VariableList.append(["klfitter_logLikelihood[0]",   22, -60.0, -38.0,   True, "h_logLH",   "--log-LH (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_topLep_pt",              45,  0.0,  450.0,   True, "h_topLep_pt",   "Leptonic top quark p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_topLep_eta",             56, -5.6,    5.6,   True, "h_topLep_eta",  "Leptonic top quark #eta (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_topLep_phi",             20, -3.141,  3.141, True, "h_topLep_phi",  "Leptonic top quark #phi (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_topHad_pt",              45,  0.0,  450.0,   True, "h_topHad_pt",   "Hadronic top quark p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_topHad_eta",             56, -5.6,    5.6,   True, "h_topHad_eta",  "Hadronic top quark #eta (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_topHad_phi",             20, -3.141,  3.141, True, "h_topHad_phi",  "Hadronic quark #phi (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_ttbar_pt",               35,  0.0,  350.0,   True, "h_ttbar_pt",    "t#bar{t} p_{T} [GeV] (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_ttbar_eta",              56, -5.6,    5.6,   True, "h_ttbar_eta",   "t#bar{t} #eta (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_ttbar_phi",              20, -3.141,  3.141, True, "h_ttbar_phi",   "t#bar{t} #phi (KLFitter)"])
        VariableList.append(["klfitter_bestPerm_ttbar_m",                90,  200.0, 1200.0, True, "h_ttbar_m",     "t#bar{t} mass [GeV] (KLFitter)"])
        
    return VariableList


#def ReturnVariableListTemplate(Flag, Channel):
def ReturnVariableList_2D():
    VariableList = []
    
    VariableList.append(["tma_klfitter_mtop_param[0]", "tma_original_mw[0]",         75, 125.0, 200.0, 55,  55.0, 110.0, True, "h_2D_mtop_mw",  "m_{top}^{reco} [GeV] (KLFitter)", "m_{W}^{reco} [GeV]"])
    VariableList.append(["tma_original_rbq[0]",        "tma_klfitter_mtop_param[0]", 54,   0.3,   3.0, 75, 125.0, 200.0, True, "h_2D_rbq_mtop", "R_{bq}^{reco}", "m_{top}^{reco} [GeV] (KLFitter)"])
    VariableList.append(["tma_original_rbq[0]",        "tma_original_mw[0]",         54,   0.3,   3.0, 55,  55.0, 110.0, True, "h_2D_rbq_mw",   "R_{bq}^{reco}", "m_{W}^{reco} [GeV]"])
    
    return VariableList


def ReturnVariablesKLFPerf():
    VariableList = []
    VariableList.append(["klfitter_minuitDidNotConverge[0]",                 2, -0.5, 1.5, True, "h_klf_notConverged",      "Minuit not converged (KLFitter)"])
    VariableList.append(["klfitter_fitAbortedDueToNaN[0]",                   2, -0.5, 1.5, True, "h_klf_fitAborted",        "Fit aborted due to nan (KLFitter)"])
    VariableList.append(["klfitter_atLeastOneFitParameterAtItsLimit[0]",     2, -0.5, 1.5, True, "h_klf_paramAtLimit",      "Parameter at limit (KLFitter)"])
    VariableList.append(["klfitter_invalidTransferFunctionAtConvergence[0]", 2, -0.5, 1.5, True, "h_klf_invalTransferFunc", "Invalid transfer function at convergance (KLFitter)"])
    VariableList.append(["klfitter_logLikelihood[0]",   22, -60.0, -38.0,  True, "h_logLH",         "--log-LH (KLFitter)"])
    VariableList.append(["tma_klfitter_mtop_param[0]",  75, 125.0, 200.0,  True, "h_mtop_param",   "m_{top}^{reco} [GeV] (KLFitter)"])
    VariableList.append(["tma_original_mw[0]",          55, 55.0,  110.0,  True, "h_mw_orig",      "m_{W}^{reco} [GeV]"])
    VariableList.append(["tma_original_rbq[0]",         54,  0.3,    3.0,  True, "h_rbq_orig",     "R_{bq}^{reco}"])

    return VariableList







# to add at some point but will make runtime longer

#VariableList.append(["tma_bjet_pt[0]/1000.0",   50,    0.0, 500.0, True, "h_bjet0_pt",    "Leading b-jet p_{T} [GeV]"])                                                                                
#VariableList.append(["tma_bjet_eta[0]",         22,  -2.75,  2.75, True, "h_bjet0_eta",   "Leading b-jet #eta"])                                                                                       
#VariableList.append(["tma_bjet_phi[0]",         20, -3.141, 3.141, True, "h_bjet0_phi",   "Leading b-jet #phi"])                                                                                       
#VariableList.append(["tma_bjet_pt[1]/1000.0",   33,    0.0, 330.0, True, "h_bjet1_pt",    "Second b-jet p_{T} [GeV]"])                                                                                 
#VariableList.append(["tma_bjet_eta[1]",         22,  -2.75,  2.75, True, "h_bjet1_eta",   "Second b-jet #eta"])                                                                                   
##VariableList.append(["tma_bjet_phi[1]",         20, -3.141, 3.141, True, "h_bjet1_phi",   "Second b-jet #phi"])                                                                                       
#VariableList.append(["tma_bjet_pt/1000.0",      40,    0.0, 400.0, True, "h_bjet_pt",     "All b-jets p_{T} [GeV]"])                                                                                   
#VariableList.append(["tma_bjet_eta",            22,  -2.75,  2.75, True, "h_bjet_eta",    "All b-jets #eta"])                                                                                          
#VariableList.append(["tma_bjet_phi",            20, -3.141, 3.141, True, "h_bjet_phi",    "All b-jets #phi"])   
#VariableList.append(["tma_met_phi",                 20, -3.141, 3.141, True, "h_met_phi",      "#phi (Missing E_T)"])
