#! /usr/bin/python                                                                                                                                                                   

import os,sys
import glob
from ROOT import *
import gc

from CompareSeveralPlots import *

sys.path.append('../SortingScripts')
import VariableList
from ListSystematics import *

# to be specified by the user:
NomFile = "../../../../Downloads_21.2.38/Output_ForMassWorkshop/Win2_MET_2tags_KLF_SYST/Histograms_lepjets_nominal_Merged/Merge_ttbar_PP8_MC16a.root"

fHelp       = TFile(NomFile, "READ")
histoHelp   = fHelp.Get("h_mtop_param")

CompareList2 = []

# to compare three files                                                                                                                                                          
CompareList3 = []

JESList_noBJES = ReturnJESList_noBJES()

for entry in JESList_noBJES:
    
    LabelUp   = entry[1]
    LabelDown = entry[2]
    FileUp   = NomFile.replace("nominal", LabelUp)
    FileDown = NomFile.replace("nominal", LabelDown)

    CompareList3.append([NomFile, "nominal", FileUp, "Up", FileDown, "Down", "Comparison_Syst/", "lepjets", entry[0]])

for entry in CompareList2:
    InputFile1 = MainFolder1+"/"+entry[0]
    InputFile2 = MainFolder2+"/"+entry[2]
    InputName1 = entry[1]
    InputName2 = entry[3]
    OutputFolder = os.getcwd()+"/"+entry[4]
    Channel    = entry[5]

    os.system("mkdir -p "+OutputFolder)

    VarList = VariableList.ReturnVariableListTemplates("", Channel)
        
    for Var in VarList:

        HistoName   = Var[5]
        HistoTitle  = Var[6]
        OutputFile = OutputFolder+"/"+HistoName.replace("h_", "")+".pdf"
        
        MakeComparisonPlots(OutputFile, HistoName, HistoTitle, InputFile1, InputName1, InputFile2, InputName2) 


for entry in CompareList3:
    InputFile1 = entry[0]
    InputFile2 = entry[2]
    InputFile3 = entry[4]
    InputName1 = entry[1]
    InputName2 = entry[3]
    InputName3 = entry[5]
    OutputFolder = os.getcwd()+"/"+entry[6]
    Channel    = entry[7]
    Syst       = entry[8]

    os.system("mkdir -p "+OutputFolder)

    VarList = VariableList.ReturnVariableListTemplate("", Channel)

    for Var in VarList:

        HistoName   = Var[5]
        HistoTitle  = Var[6]
        OutputFile = OutputFolder+"/"+HistoName.replace("h_", "")+"_"+Syst+".pdf"

        MakeComparisonPlots(OutputFile, HistoName, HistoTitle, InputFile1, InputName1, InputFile2, InputName2, InputFile3, InputName3)
        
        #gc.collect()
