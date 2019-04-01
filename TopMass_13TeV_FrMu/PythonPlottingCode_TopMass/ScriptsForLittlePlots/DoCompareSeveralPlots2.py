#! /usr/bin/python                                                                                                                                                                   

import os,sys
import glob
from ROOT import *

from CompareSeveralPlots import *

sys.path.append('../SortingScripts')
import VariableList

# to be specified by the user:
MainFolder1 = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.38/Output_Win_MET_2tags_KLF_100_100/Histograms_lepjets_2015_16_Merged/"
MainFolder2 = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.51/Output_Win_MET_2tags_KLF_100_100/Histograms_lepjets_2015_16_Merged/"

# to compare two files
CompareList2 = []
#CompareList2.append(["Output_Win_MET_2tags/Histograms_lepjets_Unmerged/Histogram_410470_MC16a.root", "FullSim", "Output_Win_MET_2tags_100_100/Histograms_lepjets_Unmerged/Histogram_410470_MC16a.root", "AF2", "Comparison_FS_AF2_2015_16_ttbar_MC16a/", "lepjets"])
#CompareList2.append(["Output_Win_2tags_2016/Histograms_dilepton_2016_Merged/Merge_ttbar_MC16a.root", "2016", "Output_Win_2tags_2015/Histograms_dilepton_2015_Merged/Merge_ttbar_MC16a.root", "2015", "Comparison_dilepton_dataPeriods_ttbar_MC16a/", "dilepton"])
#CompareList2.append(["Output_Win_MET_2tags_ejets/Histograms_ejets_2015_16_Merged/Merge_ttbar_MC16a.root", "e+jets", "Output_Win_MET_2tags_mujets/Histograms_mujets_2015_16_Merged/Merge_ttbar_MC16a.root", "mujets", "Comparison_lepjets_channels_ttbar_MC16a/", "lepjets"])
#CompareList2.append(["Output_Win_MET_2tags_ejets/Histograms_ejets_2017_Merged/Merge_ttbar_MC16c.root", "e+jets", "Output_Win_MET_2tags_mujets/Histograms_mujets_2017_Merged/Merge_ttbar_MC16c.root", "mujets", "Comparison_lepjets_channels_ttbar_MC16c/", "lepjets"])
#CompareList2.append(["Output_Win_MET_2tags/Histograms_lepjets_2015_16_Merged/Merge_ttbar_MC16a.root", "Pow+Py8", "Output_Win_MET_2tags/Histograms_lepjets_2015_16_Merged/Merge_ttbar_MC16a_PH7_AF2.root", "Pow+H7", "Comparison_lepjets_Py8_H7_ttbar_MC16a/", "lepjets"])
CompareList2.append(["Merge_ttbar_MC16a.root", "old", "Merge_ttbar_PP8_MC16a.root", "new", "Comparison_Templates_172p5/", "lepjets"])
CompareList2.append(["Merge_ttbar_171_MC16a.root", "old", "Merge_ttbar_PP8_171_MC16a.root", "new", "Comparison_Templates_171p0/", "lepjets"])
CompareList2.append(["Merge_ttbar_172_MC16a.root", "old", "Merge_ttbar_PP8_172_MC16a.root", "new", "Comparison_Templates_172p0/", "lepjets"])
CompareList2.append(["Merge_ttbar_173_MC16a.root", "old", "Merge_ttbar_PP8_173_MC16a.root", "new", "Comparison_Templates_173p0/", "lepjets"])
CompareList2.append(["Merge_ttbar_174_MC16a.root", "old", "Merge_ttbar_PP8_174_MC16a.root", "new", "Comparison_Templates_174p0/", "lepjets"])

#CompareList2.append(["Output_Win_MET_2tags_ejets/Histograms_ejets_2015_16_Merged/Merge_ttbar_MC16a.root", "e+jets", "Output_Win_MET_2tags_mujets/Histograms_mujets_2015_16_Merged/Merge_ttbar_MC16a.root", "2015", "Comparison_lepjets_channels_ttbar_MC16a/", "lepjets"])

# those are all the folders that are in the MainFolder
#Output_noCuts/                    Output_Win_2tags_2015/            Output_Win_2tags_mumu/            Output_Win_MET_2tags_ejets_2015/  Output_Win_MET_2tags_mujets_2016/
#Output_Win/                       Output_Win_2tags_2016/            Output_Win_MET_1tags/             Output_Win_MET_2tags_ejets_2016/  
#Output_Win_1tags/                 Output_Win_2tags_ee/              Output_Win_MET_2tags/             Output_Win_MET_2tags_mujets/      
#Output_Win_2tags/                 Output_Win_2tags_emu/             Output_Win_MET_2tags_ejets/       Output_Win_MET_2tags_mujets_2015/ 

# to compare three files
CompareList3 = []
#CompareList3.append(["Output_Win_2tags_emu/Histograms_emu_2015_16_Merged/Merge_ttbar_MC16a.root", "emu", "Output_Win_2tags_mumu/Histograms_mumu_2015_16_Merged/Merge_ttbar_MC16a.root", "mumu", "Output_Win_2tags_ee/Histograms_ee_2015_16_Merged/Merge_ttbar_MC16a.root", "ee", "Comparison_dilepton_channels_ttbar_MC16a/", "dilepton"])
#CompareList3.append(["Output_Win_2tags_emu/Histograms_emu_2017_Merged/Merge_ttbar_MC16c.root", "emu", "Output_Win_2tags_mumu/Histograms_mumu_2017_Merged/Merge_ttbar_MC16c.root", "mumu", "Output_Win_2tags_ee/Histograms_ee_2017_Merged/Merge_ttbar_MC16c.root", "ee", "Comparison_dilepton_channels_ttbar_MC16c/", "dilepton"])
#CompareList3.append(["Output_Win_2tags/Histograms_dilepton_2017_Merged/Merge_ttbar_MC16c.root", "2017", "Output_Win_2tags_2016/Histograms_dilepton_2016_Merged/Merge_ttbar_MC16a.root", "2016", "Output_Win_2tags_2015/Histograms_dilepton_2015_Merged/Merge_ttbar_MC16a.root", "2015", "Comparison_dilepton_dataPeriods_ttbar/", "dilepton"])
#CompareList3.append(["Output_Win_MET_2tags/Histograms_lepjets_2017_Merged/Merge_ttbar_MC16c.root", "2017", "Output_Win_MET_2tags_2016/Histograms_lepjets_2016_Merged/Merge_ttbar_MC16a.root", "2016", "Output_Win_MET_2tags_2015/Histograms_lepjets_2015_Merged/Merge_ttbar_MC16a.root", "2015", "Comparison_lepjets_dataPeriods_ttbar/", "lepjets"])

for entry in CompareList2:
    InputFile1 = MainFolder1+"/"+entry[0]
    InputFile2 = MainFolder2+"/"+entry[2]
    InputName1 = entry[1]
    InputName2 = entry[3]
    OutputFolder = os.getcwd()+"/"+entry[4]
    Channel    = entry[5]

    os.system("mkdir -p "+OutputFolder)

    VarList = VariableList.ReturnVariableListTemplate("", Channel)
        
    for Var in VarList:

        HistoName   = Var[5]
        HistoTitle  = Var[6]
        OutputFile = OutputFolder+"/"+HistoName.replace("h_", "")+".pdf"
        
        MakeComparisonPlots(OutputFile, HistoName, HistoTitle, InputFile1, InputName1, InputFile2, InputName2) 


for entry in CompareList3:
    InputFile1 = MainFolder+"/"+entry[0]
    InputFile2 = MainFolder+"/"+entry[2]
    InputFile3 = MainFolder+"/"+entry[4]
    InputName1 = entry[1]
    InputName2 = entry[3]
    InputName3 = entry[5]
    OutputFolder = os.getcwd()+"/"+entry[6]
    Channel    = entry[7]

    os.system("mkdir -p "+OutputFolder)

    VarList = VariableList.ReturnVariableListSimple("", Channel)

    for Var in VarList:

        HistoName   = Var[5]
        HistoTitle  = Var[6]
        OutputFile = OutputFolder+"/"+HistoName.replace("h_", "")+".pdf"

        MakeComparisonPlots(OutputFile, HistoName, HistoTitle, InputFile1, InputName1, InputFile2, InputName2, InputFile3, InputName3)
