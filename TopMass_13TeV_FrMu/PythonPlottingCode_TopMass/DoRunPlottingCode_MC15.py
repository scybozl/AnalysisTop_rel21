#! /usr/bin/python

import glob,sys,subprocess,os
import SubmitFillCluster
import MassSuperScriptPlots

fLocal      = os.getcwd()
ReleaseFlag = "Rel20" 

FillHistos   = False
MergeHistos  = False
MakePlots    = True

TreeName     = "nominal"  # the _Loose is always added automatically                                                                                                                                    
WeightName   = "nominal"

MainFolder   =  "/ptmp/mpp/knand/TopMass_13TeV/Downloads_2.4.42/"

Cuts_Window_LJ = "\"*(tma_klfitter_mtop_param[0]>125.0 && tma_klfitter_mtop_param[0]<200.0)*(tma_original_mw[0]>55.0 && tma_original_mw[0]<110.0)*(tma_original_rbq[0]>0.3 && tma_original_rbq[0]<3.0)\""
Cuts_Window_DL = "\"*(tma_mlb_minmaxavg/1000.0>30.0&&tma_mlb_minmaxavg/1000.0<170.0)\""
Cuts_MET       = "\"*(met_met/1000.0 > 20.0)\""
Cuts_NBTAG     = "\"*(tma_nbjets == 2)\""
Cuts_NJETS     = "\"*(tma_njets  <= 6)\""
Cuts_NBTAG_1   = "\"*(tma_nbjets == 1)\""
Cuts_NJETS_2   = "\"*(tma_njets  == 2)\""
Cuts_KLF       = "\"*(klfitter_minuitDidNotConverge[0]==0&&klfitter_fitAbortedDueToNaN[0]==0&&klfitter_atLeastOneFitParameterAtItsLimit[0]==0&&klfitter_invalidTransferFunctionAtConvergence[0]==0)\""



PersonalOutputFolderPrefix = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_2.4.42/" # specify here the folder, where your output should be written to

# specify channel, additional cuts, name of the input folder, flag for the name of the output folder and flag (Template, ControlPlots)
# channel can be either lepjets or dilepton
List = []

List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_MC15",      "ControlPlots"])

'''
# dilepton, for different data taking campaigns, for 2-tag exclusive
List.append(["ee_2015_16",    Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_2tags_ee",   "ControlPlots"])
List.append(["emu_2015_16",   Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_2tags_emu",  "ControlPlots"])
List.append(["mumu_2015_16",  Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_2tags_mumu", "ControlPlots"])
List.append(["ee_2017",       Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2017/",    "Win_2tags_ee",   "ControlPlots"])
List.append(["emu_2017",      Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2017/",    "Win_2tags_emu",  "ControlPlots"])
List.append(["mumu_2017",     Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2017/",    "Win_2tags_mumu", "ControlPlots"])
List.append(["dilepton_2015", Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_2tags_2015", "ControlPlots"])
List.append(["dilepton_2016", Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_2tags_2016", "ControlPlots"])
List.append(["dilepton_2017", Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2017/",       "Win_2tags", "ControlPlots"])
List.append(["dilepton_2015_16", Cuts_Window_DL+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_2tags", "ControlPlots"])
# dilepton with exactly 1 b-tag
List.append(["dilepton_2015_16", Cuts_Window_DL+Cuts_NBTAG_1, MainFolder+"/Files_2015_16/", "Win_1tags", "ControlPlots"])
List.append(["dilepton_2017",    Cuts_Window_DL+Cuts_NBTAG_1, MainFolder+"/Files_2017/",    "Win_1tags", "ControlPlots"])
# dilepton without b-tag cut
List.append(["dilepton_2015_16", Cuts_Window_DL, MainFolder+"/Files_2015_16/", "Win", "ControlPlots"])
List.append(["dilepton_2017",    Cuts_Window_DL, MainFolder+"/Files_2017/",    "Win", "ControlPlots"])
# dilepton, for different data taking campaigns, for preselection
List.append(["dilepton_2015_16", "", MainFolder+"/Files_2015_16/", "noCuts", "ControlPlots"])
List.append(["dilepton_2017",    "", MainFolder+"/Files_2017/",    "noCuts", "ControlPlots"])


# lepton+jets, separately per year and lepton flavour
List.append(["ejets_2015",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_ejets_2015",  "ControlPlots"])
List.append(["mujets_2015",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_mujets_2015", "ControlPlots"])
List.append(["ejets_2016",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_ejets_2016",  "ControlPlots"])
List.append(["mujets_2016",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_mujets_2016", "ControlPlots"])
List.append(["ejets_2017",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2017/",    "Win_MET_2tags_ejets",       "ControlPlots"])
List.append(["mujets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2017/",    "Win_MET_2tags_mujets",      "ControlPlots"])
List.append(["ejets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_ejets",       "ControlPlots"])
List.append(["mujets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_mujets",      "ControlPlots"])
# lepton+jets, for different data taking campaigns, for 2-tags exclusive
List.append(["lepjets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2017/",    "Win_MET_2tags",      "ControlPlots"])
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags",      "ControlPlots"])
List.append(["lepjets_2015",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_2015", "ControlPlots"])
List.append(["lepjets_2016",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/", "Win_MET_2tags_2016", "ControlPlots"])

# lepton+jets, for different data taking campaigns, for preselection
List.append(["lepjets_2017",     "", MainFolder+"/Files_2017/",    "noCuts",  "ControlPlots"])
List.append(["lepjets_2015_16",  "", MainFolder+"/Files_2015_16/", "noCuts",  "ControlPlots"])
# lepton+jets, for different data taking campaigns, for 1-tags exclusive
List.append(["lepjets_2017",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG_1, MainFolder+"/Files_2017/",    "Win_MET_1tags",  "ControlPlots"])
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG_1, MainFolder+"/Files_2015_16/", "Win_MET_1tags",  "ControlPlots"])

List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_098_100_Template/", "Win_MET_2tags_098_100", "Template"])                                                 
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_099_100_Template/", "Win_MET_2tags_099_100", "Template"])                                                 
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_100_100_Template/", "Win_MET_2tags_100_100", "Template"])                                                 
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_101_100_Template/", "Win_MET_2tags_101_100", "Template"])                                                 
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_102_100_Template/", "Win_MET_2tags_102_100", "Template"])                                                 
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_100_098_Template/", "Win_MET_2tags_100_098", "Template"])                                                 
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_100_099_Template/", "Win_MET_2tags_100_099", "Template"])  
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_100_101_Template/", "Win_MET_2tags_100_101", "Template"])  
List.append(["lepjets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16_100_102_Template/", "Win_MET_2tags_100_102", "Template"]) 

List.append(["lepjets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2017/",    "Win_MET_2tags_KLF",      "ControlPlots"])                                                     
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "Win_MET_2tags_KLF",      "ControlPlots"]) 

List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_098_100/", "Win_MET_2tags_KLF_098_100_wTree", "Template"])
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_099_100/", "Win_MET_2tags_KLF_099_100_wTree", "Template"])                               
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_100/", "Win_MET_2tags_KLF_100_100_wTree", "Template"])                               
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_101_100/", "Win_MET_2tags_KLF_101_100_wTree", "Template"])                               
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_102_100/", "Win_MET_2tags_KLF_102_100_wTree", "Template"])                               
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_098/", "Win_MET_2tags_KLF_100_098_wTree", "Template"])                               
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_099/", "Win_MET_2tags_KLF_100_099_wTree", "Template"])                               
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_101/", "Win_MET_2tags_KLF_100_101_wTree", "Template"])                            
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_102/", "Win_MET_2tags_KLF_100_102_wTree", "Template"])

List.append(["ee_2015_16",    Cuts_Window_DL+Cuts_NBTAG+Cuts_NJETS_2, MainFolder+"/Files_2015_16/", "Win_2tags_2jets_ee",   "ControlPlots"])                                                           
List.append(["emu_2015_16",   Cuts_Window_DL+Cuts_NBTAG+Cuts_NJETS_2, MainFolder+"/Files_2015_16/", "Win_2tags_2jets_emu",  "ControlPlots"])                                                              
List.append(["mumu_2015_16",  Cuts_Window_DL+Cuts_NBTAG+Cuts_NJETS_2, MainFolder+"/Files_2015_16/", "Win_2tags_2jets_mumu", "ControlPlots"]) 

List.append(["ee_2015_16",    Cuts_Window_DL+Cuts_NBTAG_1+Cuts_NJETS_2, MainFolder+"/Files_2015_16/", "Win_1tags_2jets_ee",   "ControlPlots"])
List.append(["emu_2015_16",   Cuts_Window_DL+Cuts_NBTAG_1+Cuts_NJETS_2, MainFolder+"/Files_2015_16/", "Win_1tags_2jets_emu",  "ControlPlots"])
List.append(["mumu_2015_16",  Cuts_Window_DL+Cuts_NBTAG_1+Cuts_NJETS_2, MainFolder+"/Files_2015_16/", "Win_1tags_2jets_mumu", "ControlPlots"])
'''

# for KLFitter performance plots: KLFPerf flag
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG, MainFolder+"/Files_2015_16/",          "Win_MET_2tags_KLFPerf",        "KLFPerf"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "Win_MET_2tags_CutKLF_KLFPerf", "KLFPerf"])

for entry in List:

    Channel          = entry[0]
    Cuts             = entry[1]
    MainInputFolder  = entry[2]
    MainOutputFolder = PersonalOutputFolderPrefix+"/Output_"+entry[3]+"/"
    Flag             = entry[4]

    MainOutputFolderChannel = MainOutputFolder+"/Histograms_"+Channel+"_Unmerged/"

    # this code for now should just run over the files directly after production (so one folder per DSID), make histograms and plots
    #if ReleaseFlag != "Rel21":
    #    MainInputFolder  = "/work/ws/atlas/ak1148-ak1148/Downloads/FromGrid_AnalysisTop_2.4.33/Downloads_2.4.33/Downloads/"
    #    MainOutputFolder = MainInputFolder.replace("Downloads_2.4.33/Downloads/", "Histograms_Nominal_"+Channel+"_Unmerged/")

    SubmissionFolder = MainOutputFolder+"/SubmissionFolder/"

    os.system("mkdir -p "+MainOutputFolder)
    os.system("mkdir -p "+MainOutputFolderChannel)
    os.system("mkdir -p "+SubmissionFolder)

    if FillHistos:
        SubmitFillCluster.SubmitToCluster(MainInputFolder, MainOutputFolderChannel, SubmissionFolder, Channel, TreeName, WeightName, ReleaseFlag, Flag, Cuts)
    
    if MergeHistos:
        MassSuperScriptPlots.MergeAllHistos(MainOutputFolderChannel, ReleaseFlag)

    if Flag != "ControlPlots" and Flag != "KLFPerf":
        continue

    if MakePlots:
        ListDataPeriod = ["2015_16"] #, "2017", "Combined"]

        if "2017" in MainInputFolder:
            ListDataPeriod = ["2017"]

        if ReleaseFlag != "Rel21":
            ListDataPeriod = ["2015_16"]

        for DataPeriod in ListDataPeriod:
            NomFolder    = MainOutputFolderChannel.replace("Unmerged", "Merged")
            PlotFolder   = "CP_"+DataPeriod+"_"+Channel+"_"+entry[3]+"_Absolute_Rel21/"
            os.system("python MakeControlPlot_NominalOnly_MC15.py "+DataPeriod+" "+Channel+" "+NomFolder+" "+PlotFolder+" "+ReleaseFlag)
