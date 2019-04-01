#! /usr/bin/python

import glob,sys,subprocess,os
import SubmitFillCluster
import MassSuperScriptPlots
sys.path.append('SortingScripts')
from ListSystematics import *

fLocal      = os.getcwd()
ReleaseFlag = "Rel21" 

FillHistos   = True
MergeHistos  = True
MakePlots    = True

TreeName     = "nominal"  # the _Loose is always added automatically                                                                                                                                    
WeightName   = "nominal"

MainFolder   =  "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.38/"

Cuts_Window_LJ = "\"*(tma_klfitter_mtop_param[0]>130.0 && tma_klfitter_mtop_param[0]<200.0)*(tma_original_mw[0]>55.0 && tma_original_mw[0]<110.0)*(tma_original_rbq[0]>0.5 && tma_original_rbq[0]<3.0)\""
Cuts_Window_DL = "\"*(tma_mlb_minmaxavg/1000.0>30.0&&tma_mlb_minmaxavg/1000.0<170.0)\""
Cuts_MET       = "\"*(met_met/1000.0 > 20.0)\""
Cuts_NBTAG     = "\"*(tma_nbjets >= 2)\""
Cuts_NJETS     = "\"*(tma_njets  <= 6)\""
Cuts_NBTAG_1   = "\"*(tma_nbjets == 1)\""
Cuts_NJETS_2   = "\"*(tma_njets  == 2)\""
Cuts_KLF       = "\"*(klfitter_minuitDidNotConverge[0]==0&&klfitter_fitAbortedDueToNaN[0]==0&&klfitter_atLeastOneFitParameterAtItsLimit[0]==0&&klfitter_invalidTransferFunctionAtConvergence[0]==0)\""
Cuts_LH        = "\"*(klfitter_logLikelihood[0]>-50.0)\""


PersonalOutputFolderPrefix = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.38/" # specify here the folder, where your output should be written to

# specify channel, additional cuts, name of the input folder, flag for the name of the output folder and flag (Template, ControlPlots)
# channel can be either lepjets or dilepton
List = []

'''
# lepton+jets, separately per year and lepton flavour
List.append(["ejets_2015",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF_ejets_2015",  "ControlPlots"])
List.append(["mujets_2015",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF_mujets_2015", "ControlPlots"])
List.append(["ejets_2016",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF_ejets_2016",  "ControlPlots"])
List.append(["mujets_2016",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF_mujets_2016", "ControlPlots"])
List.append(["ejets_2017",     Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2017/",    "ForMassWorkshop/Win2_MET_2tags_KLF_ejets",       "ControlPlots"])
List.append(["mujets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2017/",    "ForMassWorkshop/Win2_MET_2tags_KLF_mujets",      "ControlPlots"])
List.append(["ejets_2015_16",  Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF_ejets",       "ControlPlots"])
List.append(["mujets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF_mujets",      "ControlPlots"])

# lepton+jets, for different data taking campaigns, for 2-tags exclusive                                                                                                                                   
List.append(["lepjets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2017/",    "ForMassWorkshop/Win2_MET_KLF",      "ControlPlots"])
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_KLF",      "ControlPlots"])

# lepton+jets, for different data taking campaigns, for 2-tags exclusive
List.append(["lepjets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2017/",    "ForMassWorkshop/Win2_MET_2tags_KLF",      "ControlPlots"])
'''
                                        
#List.append(["lepjets_2017",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2017/",    "ForMassWorkshop/Win2_MET_2tags_KLF",      "ControlPlots"])
List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_KLF",      "ControlPlots"])
#List.append(["lepjets_2015",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_2015_KLF", "ControlPlots"])
#List.append(["lepjets_2016",    Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16/", "ForMassWorkshop/Win2_MET_2tags_2016_KLF", "ControlPlots"])

#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_098_100/",     "ForMassWorkshop/Win2_MET_2tags_KLF_098_100",  "Template"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_099_100/",     "ForMassWorkshop/Win2_MET_2tags_KLF_099_100",  "Template"])  
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_0995_100/",    "ForMassWorkshop/Win2_MET_2tags_KLF_0995_100", "Template"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_100/",     "ForMassWorkshop/Win2_MET_2tags_KLF_100_100",  "Template"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_1005_100/",    "ForMassWorkshop/Win2_MET_2tags_KLF_1005_100", "Template"])      
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_101_100/",     "ForMassWorkshop/Win2_MET_2tags_KLF_101_100",  "Template"]) 
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_102_100/",     "ForMassWorkshop/Win2_MET_2tags_KLF_102_100",  "Template"])                      
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_098/",     "ForMassWorkshop/Win2_MET_2tags_KLF_100_098",  "Template"])        
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_099/",     "ForMassWorkshop/Win2_MET_2tags_KLF_100_099",  "Template"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_0995/",    "ForMassWorkshop/Win2_MET_2tags_KLF_100_0995", "Template"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_1005/",    "ForMassWorkshop/Win2_MET_2tags_KLF_100_1005", "Template"])     
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_101_NEW/", "ForMassWorkshop/Win2_MET_2tags_KLF_100_101",  "Template"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_100_102/",     "ForMassWorkshop/Win2_MET_2tags_KLF_100_102",  "Template"])



SystList = []
#SystList.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_SYST/", "ForMassWorkshop/Win2_MET_2tags_KLF_SYST2",      "ControlPlots"])
#List.append(["lepjets_2015_16", Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_KLF, MainFolder+"/Files_2015_16_AF2/", "ForMassWorkshop/Win2_MET_2tags_KLF_SYST2",      "ControlPlots"])


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
        MassSuperScriptPlots.MergeAllHistos(MainOutputFolderChannel)

    if Flag != "ControlPlots" and Flag != "KLFPerf":
        continue

    if MakePlots:
        ListDataPeriod = ["Comb"] #["2015_16"] #, "2017", "Combined"]

        if "2017" in MainInputFolder:
            ListDataPeriod = ["2017"]

        if ReleaseFlag != "Rel21":
            ListDataPeriod = ["2015_16"]

        for DataPeriod in ListDataPeriod:
            NomFolder    = MainOutputFolderChannel.replace("Unmerged", "Merged")
            PlotFolder   = "CP_"+DataPeriod+"_"+Channel+"_"+entry[3]+"_Absolute_Rel21/"
            os.system("python MakeControlPlot_NominalOnly.py "+DataPeriod+" "+Channel+" "+NomFolder+" "+PlotFolder+" "+ReleaseFlag)




# now get all names of systematic trees in the fullsim samples 
SystTreeList = ReturnTreeList()

# now run to get all systematic variations from the trees (detector syst)
for entry in SystList:

    Channel          = entry[0]
    ChannelShort     = (entry[0].split("_"))[0] # just want to know if running over lepjets or dilepton
    Cuts             = entry[1]
    MainInputFolder  = entry[2]
    MainOutputFolder = PersonalOutputFolderPrefix+"/Output_"+entry[3]+"/"
    Flag             = entry[4]

    for SystTree in SystTreeList:

        #if not "nominal" in SystTree:
        #    continue

        MainOutputFolderChannel = MainOutputFolder+"/Histograms_"+ChannelShort+"_"+SystTree+"_Unmerged/"

        SubmissionFolder = MainOutputFolder+"/SubmissionFolder_"+SystTree+"/"

        os.system("mkdir -p "+MainOutputFolder)
        os.system("mkdir -p "+MainOutputFolderChannel)
        os.system("mkdir -p "+SubmissionFolder)

        #print MainOutputFolderChannel

        if FillHistos:
            SubmitFillCluster.SubmitToCluster(MainInputFolder, MainOutputFolderChannel, SubmissionFolder, Channel, SystTree, WeightName, ReleaseFlag, Flag, Cuts)
        
        if MergeHistos:
            print MainOutputFolderChannel
            #MassSuperScriptPlots.MergeAllHistos(MainOutputFolderChannel)
