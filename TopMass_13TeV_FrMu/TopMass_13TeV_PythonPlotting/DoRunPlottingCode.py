#! /usr/bin/python

import glob,sys,subprocess,os
from SuperScriptPlots import *
sys.path.append('SortingScripts')
from ListSystematics import *

fLocal       = os.getcwd()

FillHistos        = True
MergeHistos       = False
MakePlots         = False
DoParametrisation = False

BTagWP = "70"

MainFolder     = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.58_withBDT_and_DNN/"
OutputFolder   = "/ptmp/mpp/knand/TopMass_13TeV/Output_21.2.58_withBDT_and_DNN/"

MainFolder_dil = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.58_dilOnly/"

RunTypes  = ["TMPL", "SYSLJ", "NOM"] # "TMPL", "SYSLJ"] # the different run types for lepton+jets
#RunTypes  = ["NOM", "SYSDIL"] # the different run types for dilepton

Cuts_Window_LJ = ["\"*(tma_klf_mtop_param>130.0 && tma_klf_mtop_param<200.0)*(tma_klf_orig_mw>55.0 && tma_klf_orig_mw<110.0)*(tma_klf_orig_rbq>0.5 && tma_klf_orig_rbq<3.0)\"", "Win"]
Cuts_Window_DL = ["\"*(tma_mlb_minmaxavg/1000.0>30.0&&tma_mlb_minmaxavg/1000.0<170.0)\"", "Win"]
Cuts_MET       = ["\"*(met_met/1000.0 > 20.0)\"", "MET20"]
Cuts_4Jets     = ["\"*(tma_njets == 4)\"",     "4jetsExcl"]
Cuts_5Jets     = ["\"*(tma_njets == 5)\"",     "5jetsExcl"]
Cuts_6Jets     = ["\"*(tma_njets == 6)\"",     "6jetsExcl"]
Cuts_NBTAG     = ["\"*(tma_nbjets_70 == 2)\"", "2bE"]
#Cuts_KLF       = ["\"*(klfitter_minuitDidNotConverge[0]==0&&klfitter_fitAbortedDueToNaN[0]==0&&klfitter_atLeastOneFitParameterAtItsLimit[0]==0&&klfitter_invalidTransferFunctionAtConvergence[0]==0)\"", "KLF"]

# specify channel, additional cuts, name of the input folder, flag for the name of the output folder and flag (Template, ControlPlots)
# channel can be either lepjets or dilepton
List = []
List.append(["lepjets_2015_16",  [Cuts_NBTAG, Cuts_MET],                             MainFolder,     "", "ControlPlots"])
List.append(["lepjets_2015_16",  [Cuts_NBTAG, Cuts_MET, Cuts_Window_LJ],             MainFolder,     "", "ControlPlots"])
#List.append(["lepjets_2015_16",  [Cuts_MET, Cuts_4Jets],                 MainFolder,     "", "ControlPlots"])
#List.append(["lepjets_2015_16",  [Cuts_Window_LJ, Cuts_MET, Cuts_4Jets], MainFolder,     "", "ControlPlots"])
#List.append(["lepjets_2015_16",  [Cuts_MET, Cuts_5Jets],                 MainFolder,     "", "ControlPlots"])
#List.append(["lepjets_2015_16",  [Cuts_Window_LJ, Cuts_MET, Cuts_5Jets], MainFolder,     "", "ControlPlots"])
#List.append(["lepjets_2015_16",  [Cuts_MET, Cuts_6Jets],                 MainFolder,     "", "ControlPlots"])
#List.append(["lepjets_2015_16",  [Cuts_Window_LJ, Cuts_MET, Cuts_6Jets], MainFolder,     "", "ControlPlots"])
#List.append(["dilepton_2015_16", [Cuts_Window_DL],           MainFolder_dil, "_V2", "ControlPlots"])

for entry in List:

    Channel          = entry[0]
    ChannelShort     = (Channel.split("_"))[0]
    CutList          = entry[1]
    MainInputFolder  = entry[2]
    OutputFolderFlag = entry[3]
    Type             = entry[4]
    
    if FillHistos or MergeHistos:
        for RunType in RunTypes:
            FillHistosAndTrees(Channel, CutList, MainInputFolder, OutputFolder, OutputFolderFlag, Type, RunType, MergeHistos)

    if Type != "ControlPlots":
        continue

    if MakePlots:
        ListDataPeriod = ["2015_16"] #, "2017", "Combined"]

    #    if "2017" in MainInputFolder:
    #        ListDataPeriod = ["2017"]

        for DataPeriod in ListDataPeriod:

            CutFlag = ""

            for i in range(0, len(CutList)):
                CutFlag += "_"+CutList[i][1]

            NewOutputFolder = OutputFolder+"/Output_"+Channel+CutFlag+OutputFolderFlag

            NomFolder = NewOutputFolder+"/Out_NOM_FS/Merged_nominal/"
            
            print NomFolder

            PlotFolder   = NewOutputFolder+"/CP_"+DataPeriod+"_"+ChannelShort+"_"+CutFlag+"_Abs/"
            #print PlotFolder
            os.system("python MakeControlPlot_NominalOnly.py "+DataPeriod+" "+Channel+" "+NomFolder+" "+PlotFolder+ " 0") # absolute
            os.system("python MakeControlPlot_NominalOnly.py "+DataPeriod+" "+Channel+" "+NomFolder+" "+PlotFolder+ " 1") # normalised

