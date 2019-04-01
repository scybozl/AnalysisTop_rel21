#! /usr/bin/python                                                                                                                                                                                                       

import os
import sys
import glob

MainFolder = "/ptmp/mpp/bpearson/TopAnalysis_13TeV/Output_21.2.38/Output_Win_2tags_100_100/Histograms_dilepton_2015_16_Merged/"

InputFiles = []
InputFiles.append([MainFolder+"/Merge_Tree_ttbar_171_MC16a.root",  "171p0_1p0_1p0"])
InputFiles.append([MainFolder+"/Merge_Tree_ttbar_172_MC16a.root",  "172p0_1p0_1p0"])
InputFiles.append([MainFolder+"/Merge_Tree_ttbar_MC16a.root",      "172p5_1p0_1p0"])
InputFiles.append([MainFolder+"/Merge_Tree_ttbar_173_MC16a.root",  "173p0_1p0_1p0"])
InputFiles.append([MainFolder+"/Merge_Tree_ttbar_174_MC16a.root",  "174p0_1p0_1p0"])

DimensionFit = 1 # 1: mtop only, 2: mtop+jsf, 3:mtop+jsf+bjsf
ParameterSgn = "combfit_output"
OutputFolder = "OutputTest"
TreeName     = "PE_Tree"
WeightName   = "FinalWeight"
NrPE         = 1
IsLeptonJets = 0

os.system("mkdir -p "+OutputFolder)

for entry in InputFiles:
    fileName     = entry[0]
    fileString   = entry[1]+"_"+str(NrPE)+"PE_"+str(DimensionFit)+"D"
    OutputFile   = OutputFolder+"/"+fileString+".root"
    if not os.path.exists(OutputFile):
        os.system("RunPseudoExp "+ParameterSgn+" "+fileName+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightName+" "+WeightName+" "+str(NrPE)+" "+str(DimensionFit)+" "+str(IsLeptonJets))


InputFolderClosure  = OutputFolder
OutputFolderClosure = "OutputTest_Closure"

os.system("mkdir -p "+OutputFolderClosure)

FileString = str(NrPE)+"PE_"+str(DimensionFit)+"D"

os.system("MakeClosureTests "+InputFolderClosure+" "+OutputFolderClosure+" "+str(DimensionFit)+" "+str(NrPE)+" "+FileString+" mlb ") # mtop, jsf, bjsf

