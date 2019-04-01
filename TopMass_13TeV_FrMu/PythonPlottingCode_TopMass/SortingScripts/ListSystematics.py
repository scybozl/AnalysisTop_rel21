#! /usr/bin/python 

import os
import sys
import glob


def ReturnSFSystList():
    List = []
    List += ReturnTagSFList()
    List += ReturnJVTList()
    List += ReturnPileupList()
    List += ReturnLeptonSFList()
    List += ReturnNominalList()
    return List

# for all tagging SF
def ReturnTagSFList():
    List = []
    List += ReturnBtagSFList()
    List += ReturnCtagSFList()
    List += ReturnMistagSFList()
    List += ReturnTagExtrapolationList()
    return List

def ReturnNominalList():
    List = []
    List.append(["nominal_SYST", "nominal_SYST", "nominal", "nominal"])
    return List

# only b-tagging SF
def ReturnBtagSFList():
    List = []
    List.append(["bTagSF_77_B_0", "weight_bTagSF_MV2c10_77_eigenvars_B_up_0", "weight_bTagSF_MV2c10_77_eigenvars_B_down_0", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_1", "weight_bTagSF_MV2c10_77_eigenvars_B_up_1", "weight_bTagSF_MV2c10_77_eigenvars_B_down_1", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_2", "weight_bTagSF_MV2c10_77_eigenvars_B_up_2", "weight_bTagSF_MV2c10_77_eigenvars_B_down_2", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_3", "weight_bTagSF_MV2c10_77_eigenvars_B_up_3", "weight_bTagSF_MV2c10_77_eigenvars_B_down_3", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_4", "weight_bTagSF_MV2c10_77_eigenvars_B_up_4", "weight_bTagSF_MV2c10_77_eigenvars_B_down_4", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_5", "weight_bTagSF_MV2c10_77_eigenvars_B_up_5", "weight_bTagSF_MV2c10_77_eigenvars_B_down_5", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_6", "weight_bTagSF_MV2c10_77_eigenvars_B_up_6", "weight_bTagSF_MV2c10_77_eigenvars_B_down_6", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_7", "weight_bTagSF_MV2c10_77_eigenvars_B_up_7", "weight_bTagSF_MV2c10_77_eigenvars_B_down_7", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_B_8", "weight_bTagSF_MV2c10_77_eigenvars_B_up_8", "weight_bTagSF_MV2c10_77_eigenvars_B_down_8", "weight_bTagSF_MV2c10_77"])

    return List

# only c-tagging SF
def ReturnCtagSFList():
    List = []
    List.append(["bTagSF_77_C_0", "weight_bTagSF_MV2c10_77_eigenvars_C_up_0", "weight_bTagSF_MV2c10_77_eigenvars_C_down_0", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_C_1", "weight_bTagSF_MV2c10_77_eigenvars_C_up_1", "weight_bTagSF_MV2c10_77_eigenvars_C_down_1", "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_C_2", "weight_bTagSF_MV2c10_77_eigenvars_C_up_2", "weight_bTagSF_MV2c10_77_eigenvars_C_down_2", "weight_bTagSF_MV2c10_77"])
    return List

# only mistagging SF
def ReturnMistagSFList():
    List = []
    List.append(["bTagSF_77_Light_0",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_0",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_0",  "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_Light_1",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_1",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_1",  "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_Light_2",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_2",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_2",  "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_Light_3",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_3",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_3",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_4",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_4",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_4",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_5",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_5",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_5",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_6",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_6",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_6",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_7",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_7",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_7",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_8",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_8",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_8",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_9",  "weight_bTagSF_MV2c10_77_eigenvars_Light_up_9",  "weight_bTagSF_MV2c10_77_eigenvars_Light_down_9",  "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_10", "weight_bTagSF_MV2c10_77_eigenvars_Light_up_10", "weight_bTagSF_MV2c10_77_eigenvars_Light_down_10", "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_11", "weight_bTagSF_MV2c10_77_eigenvars_Light_up_11", "weight_bTagSF_MV2c10_77_eigenvars_Light_down_11", "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_12", "weight_bTagSF_MV2c10_77_eigenvars_Light_up_12", "weight_bTagSF_MV2c10_77_eigenvars_Light_down_12", "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_13", "weight_bTagSF_MV2c10_77_eigenvars_Light_up_13", "weight_bTagSF_MV2c10_77_eigenvars_Light_down_13", "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_14", "weight_bTagSF_MV2c10_77_eigenvars_Light_up_14", "weight_bTagSF_MV2c10_77_eigenvars_Light_down_14", "weight_bTagSF_MV2c10_77"])
    #List.append(["bTagSF_77_Light_15", "weight_bTagSF_MV2c10_77_eigenvars_Light_up_15", "weight_bTagSF_MV2c10_77_eigenvars_Light_down_15", "weight_bTagSF_MV2c10_77"])
    return List

def ReturnTagExtrapolationList():
    List = []
    List.append(["bTagSF_77_Extrap",       "weight_bTagSF_MV2c10_77_extrapolation_up",            "weight_bTagSF_MV2c10_77_extrapolation_down",            "weight_bTagSF_MV2c10_77"])
    List.append(["bTagSF_77_Extrap_charm", "weight_bTagSF_MV2c10_77_extrapolation_from_charm_up", "weight_bTagSF_MV2c10_77_extrapolation_from_charm_down", "weight_bTagSF_MV2c10_77"])
    return List

#
def ReturnJVTList():
    List = []
    List.append(["weight_jvt", "weight_jvt_UP", "weight_jvt_DOWN", "weight_jvt"])
    return List

#
def ReturnPileupList():
    List = []
    List.append(["weight_pileup", "weight_pileup_UP", "weight_pileup_DOWN", "weight_pileup"])
    return List

#
def ReturnElectronSFList():
    List = []
    List.append(["EL_SF_Trigger", "weight_leptonSF_EL_SF_Trigger_UP",  "weight_leptonSF_EL_SF_Trigger_DOWN",  "weight_leptonSF"])
    List.append(["EL_SF_Reco",    "weight_leptonSF_EL_SF_Reco_UP",     "weight_leptonSF_EL_SF_Reco_DOWN",     "weight_leptonSF"])
    List.append(["EL_SF_ID",      "weight_leptonSF_EL_SF_ID_UP",       "weight_leptonSF_EL_SF_ID_DOWN",       "weight_leptonSF"])
    List.append(["EL_SF_Isol",    "weight_leptonSF_EL_SF_Isol_UP",     "weight_leptonSF_EL_SF_Isol_DOWN",     "weight_leptonSF"])
    return List

#
def ReturnMuonSFList():
    List = []
    List.append(["MU_SF_Trigger_STAT", "weight_leptonSF_MU_SF_Trigger_STAT_UP",  "weight_leptonSF_MU_SF_Trigger_STAT_DOWN",  "weight_leptonSF"])
    List.append(["MU_SF_Trigger_SYST", "weight_leptonSF_MU_SF_Trigger_SYST_UP",  "weight_leptonSF_MU_SF_Trigger_SYST_DOWN",  "weight_leptonSF"])
    List.append(["MU_SF_TTVA_STAT",    "weight_leptonSF_MU_SF_TTVA_STAT_UP",     "weight_leptonSF_MU_SF_TTVA_STAT_DOWN",     "weight_leptonSF"])
    List.append(["MU_SF_TTVA_SYST",    "weight_leptonSF_MU_SF_TTVA_SYST_UP",     "weight_leptonSF_MU_SF_TTVA_SYST_DOWN",     "weight_leptonSF"])
    List.append(["MU_SF_ID_STAT",      "weight_leptonSF_MU_SF_ID_STAT_UP",       "weight_leptonSF_MU_SF_ID_STAT_DOWN",       "weight_leptonSF"])
    List.append(["MU_SF_ID_SYST",      "weight_leptonSF_MU_SF_ID_SYST_UP",       "weight_leptonSF_MU_SF_ID_SYST_DOWN",       "weight_leptonSF"])
    List.append(["MU_SF_Isol_STAT",    "weight_leptonSF_MU_SF_Isol_STAT_UP",     "weight_leptonSF_MU_SF_Isol_STAT_DOWN",     "weight_leptonSF"])
    List.append(["MU_SF_Isol_SYST",    "weight_leptonSF_MU_SF_Isol_SYST_UP",     "weight_leptonSF_MU_SF_Isol_SYST_DOWN",     "weight_leptonSF"])
    return List

#
def ReturnLeptonSFList():
    List = []
    List += ReturnElectronSFList()
    List += ReturnMuonSFList()
    return List


#####################################################################################################################################################################
#####################################################################################################################################################################
#####################################################################################################################################################################


def ReturnTreeList():
    List = []
    List += ReturnLeptonResList()
    List += ReturnJESList_noBJES()
    List += ReturnBJESList()
    List += ReturnJERList()
    List += ReturnMETList()
    List += ReturnNominalList()
    #return List

    TreeList = []
    
    for entry in List:
        for i in range(1, len(entry)):
            TreeList.append(entry[i])
        

    return TreeList

def ReturnLeptonResList():
    List = []
    #"EG_SCALE_AF2__1up", "EG_SCALE_AF2__1down",
    List.append(["EL_RESO",              "EG_RESOLUTION_ALL__1up",    "EG_RESOLUTION_ALL__1down"])
    List.append(["EL_SCALE",             "EG_SCALE_ALL__1up",         "EG_SCALE_ALL__1down"])
    List.append(["MUON_ID",              "MUON_ID__1up",              "MUON_ID__1down"])
    List.append(["MUON_MS",              "MUON_MS__1up",              "MUON_MS__1down"])
    List.append(["MUON_SAGITTA_RESBIAS", "MUON_SAGITTA_RESBIAS__1up", "MUON_SAGITTA_RESBIAS__1down"])
    List.append(["MUON_SAGITTA_RHO",     "MUON_SAGITTA_RHO__1up",     "MUON_SAGITTA_RHO__1down"])
    List.append(["MUON_SCALE",           "MUON_SCALE__1up",           "MUON_SCALE__1down"])
    return List

def ReturnJESList_noBJES():
    List = []
    List.append(["JES_EffNP_Det1",               "JET_CategoryReduction_JET_EffectiveNP_Detector1__1up",                 "JET_CategoryReduction_JET_EffectiveNP_Detector1__1down"])
    List.append(["JES_EffNP_Mix1",               "JET_CategoryReduction_JET_EffectiveNP_Mixed1__1up",                    "JET_CategoryReduction_JET_EffectiveNP_Mixed1__1down"])
    List.append(["JES_EffNP_Mix2",               "JET_CategoryReduction_JET_EffectiveNP_Mixed2__1up",                    "JET_CategoryReduction_JET_EffectiveNP_Mixed2__1down"])
    List.append(["JES_EffNP_Mix3",               "JET_CategoryReduction_JET_EffectiveNP_Mixed3__1up",                    "JET_CategoryReduction_JET_EffectiveNP_Mixed3__1down"])
    List.append(["JES_EffNP_Model1",             "JET_CategoryReduction_JET_EffectiveNP_Modelling1__1up",                "JET_CategoryReduction_JET_EffectiveNP_Modelling1__1down"])
    List.append(["JES_EffNP_Model2",             "JET_CategoryReduction_JET_EffectiveNP_Modelling2__1up",                "JET_CategoryReduction_JET_EffectiveNP_Modelling2__1down"])
    List.append(["JES_EffNP_Model3",             "JET_CategoryReduction_JET_EffectiveNP_Modelling3__1up",                "JET_CategoryReduction_JET_EffectiveNP_Modelling3__1down"])
    List.append(["JES_EffNP_Model4",             "JET_CategoryReduction_JET_EffectiveNP_Modelling4__1up",                "JET_CategoryReduction_JET_EffectiveNP_Modelling4__1down"])
    List.append(["JES_EffNP_Stat1",              "JET_CategoryReduction_JET_EffectiveNP_Statistical1__1up",              "JET_CategoryReduction_JET_EffectiveNP_Statistical1__1down"])
    List.append(["JES_EffNP_Stat2",              "JET_CategoryReduction_JET_EffectiveNP_Statistical2__1up",              "JET_CategoryReduction_JET_EffectiveNP_Statistical2__1down"])
    List.append(["JES_EffNP_Stat3",              "JET_CategoryReduction_JET_EffectiveNP_Statistical3__1up",              "JET_CategoryReduction_JET_EffectiveNP_Statistical3__1down"])
    List.append(["JES_EffNP_Stat4",              "JET_CategoryReduction_JET_EffectiveNP_Statistical4__1up",              "JET_CategoryReduction_JET_EffectiveNP_Statistical4__1down"])
    List.append(["JES_EffNP_Stat5",              "JET_CategoryReduction_JET_EffectiveNP_Statistical5__1up",              "JET_CategoryReduction_JET_EffectiveNP_Statistical5__1down"])
    List.append(["JES_EffNP_Stat6",              "JET_CategoryReduction_JET_EffectiveNP_Statistical6__1up",              "JET_CategoryReduction_JET_EffectiveNP_Statistical6__1down"])
    List.append(["JES_EtaInt_Modelling",         "JET_CategoryReduction_JET_EtaIntercalibration_Modelling__1up",         "JET_CategoryReduction_JET_EtaIntercalibration_Modelling__1down"])
    List.append(["JES_EtaInt_NonClosure_highE",  "JET_CategoryReduction_JET_EtaIntercalibration_NonClosure_highE__1up",  "JET_CategoryReduction_JET_EtaIntercalibration_NonClosure_highE__1down"])
    List.append(["JES_EtaInt_NonClosure_negEta", "JET_CategoryReduction_JET_EtaIntercalibration_NonClosure_negEta__1up", "JET_CategoryReduction_JET_EtaIntercalibration_NonClosure_negEta__1down"])
    List.append(["JES_EtaInt_NonClosure_posEta", "JET_CategoryReduction_JET_EtaIntercalibration_NonClosure_posEta__1up", "JET_CategoryReduction_JET_EtaIntercalibration_NonClosure_posEta__1down"])
    List.append(["JES_EtaInt_TotalStat",         "JET_CategoryReduction_JET_EtaIntercalibration_TotalStat__1up",         "JET_CategoryReduction_JET_EtaIntercalibration_TotalStat__1down"])
    List.append(["JES_Flavor_Composition",       "JET_CategoryReduction_JET_Flavor_Composition__1up",                    "JET_CategoryReduction_JET_Flavor_Composition__1down"])
    List.append(["JES_Flavor_Response",          "JET_CategoryReduction_JET_Flavor_Response__1up",                       "JET_CategoryReduction_JET_Flavor_Response__1down"])
    List.append(["JES_Pileup_OffsetMu",          "JET_CategoryReduction_JET_Pileup_OffsetMu__1up",                       "JET_CategoryReduction_JET_Pileup_OffsetMu__1down"])
    List.append(["JES_Pileup_OffsetNPV",         "JET_CategoryReduction_JET_Pileup_OffsetNPV__1up",                      "JET_CategoryReduction_JET_Pileup_OffsetNPV__1down"])
    List.append(["JES_Pileup_PtTerm",            "JET_CategoryReduction_JET_Pileup_PtTerm__1up",                         "JET_CategoryReduction_JET_Pileup_PtTerm__1down"])
    List.append(["JES_Pileup_RhoTopology",       "JET_CategoryReduction_JET_Pileup_RhoTopology__1up",                    "JET_CategoryReduction_JET_Pileup_RhoTopology__1down"])
    List.append(["JES_PunchThrough",             "JET_CategoryReduction_JET_PunchThrough_MC16__1up",                     "JET_CategoryReduction_JET_PunchThrough_MC16__1down"])
    List.append(["JES_SingleParticle",           "JET_CategoryReduction_JET_SingleParticle_HighPt__1up",                 "JET_CategoryReduction_JET_SingleParticle_HighPt__1down"])
    return List
    

def ReturnBJESList():
    List = []
    List.append(["JES_BJES", "JET_CategoryReduction_JET_BJES_Response__1up", "JET_CategoryReduction_JET_BJES_Response__1down"])    
    return List

def ReturnJERList():
    List = []         
    List.append(["JER", "JET_JER_SINGLE_NP__1up"])
    return List

def ReturnMETList():
    List = []
    List.append(["MET_SoftTrk_ResoPara", "MET_SoftTrk_ResoPara"])
    List.append(["MET_SoftTrk_ResoPerp", "MET_SoftTrk_ResoPerp"])
    List.append(["MET_SoftTrk_Scale",    "MET_SoftTrk_ScaleUp", "MET_SoftTrk_ScaleDown"])
    return List

    


#####################################################################################################################################################################                                     
#####################################################################################################################################################################     
##################################################################################################################################################################### 

# Systematics for MC Generators

def ReturnNamesSignalModelling():
    List = []
    List += ReturnRadiationSyst()
    List += ReturnGeneratorSyst()
    List += ReturnHadronisationSyst()
    return List

def ReturnRadiationSyst():
    List = []
    List.append(["ISR", "ISRup", "ISRdown"])
    List.append(["FSR", "FSRup", "FSRdown"])
    return List

def ReturnGeneratorSyst():
    List = []
    List.append(["MCGenerator",   "aMCatNLO_P8"])
    return List

def ReturnHadronisationSyst():
    List = []
    List.append(["Hadronisation", "PowhegHerwig7"])
    return List
