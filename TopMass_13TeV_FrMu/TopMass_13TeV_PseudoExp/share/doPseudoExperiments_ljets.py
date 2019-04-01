#! /usr/bin/python                                                                                                                                                                                                       

import os
import sys
import glob

MainFolder = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.38/"
CodeFolder = "/ptmp/mpp/knand/TopMass_13TeV/Rel21_AnalysisTop_21.2.38_MTOP/build/"


DimensionFit = 2 # 1: mtop only, 2: mtop+jsf, 3:mtop+jsf+bjsf                                                                                                                                             
ParameterSgn = "combfit_output"
OutputFolder = "OutputTest"
TreeName     = "PE_Tree"
WeightName   = "FinalWeight"
NrPE         = 500

InputFiles = []
InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_171_MC16a.root",  "171p0_1p0_1p0"])
InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_172_MC16a.root",  "172p0_1p0_1p0"])
InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",      "172p5_1p0_1p0"])
InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_173_MC16a.root",  "173p0_1p0_1p0"])
InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_174_MC16a.root",  "174p0_1p0_1p0"])

if DimensionFit > 1:
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_098_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_0p98_1p0"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_099_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_0p99_1p0"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p0_1p0"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_101_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p01_1p0"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_102_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p02_1p0"])

if DimensionFit > 2:
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_098_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p0_0p98"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_099_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p0_0p99"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_100_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p0_1p0"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_101_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p0_1p01"])
    InputFiles.append([MainFolder+"/Output_Win_MET_2tags_KLF_100_102_NEW/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_MC16a.root",  "172p5_1p0_1p02"])



os.system("mkdir -p "+OutputFolder)

for entry in InputFiles:
    fileName     = entry[0]
    fileString   = entry[1]+"_"+str(NrPE)+"PE_"+str(DimensionFit)+"D"
    OutputFile   = OutputFolder+"/"+fileString+".root"
    if os.path.exists(OutputFile):
        continue
    # now make submission files!

    SubmitFileName = "Submit_PEXP_"+fileString+".sh"

    if os.path.exists(SubmitFileName):
        continue

    submitfile     = open(SubmitFileName, "w")
    submitfile.write("#! /bin/bash \n")
    submitfile.write("cd "+CodeFolder+" \n")
    submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
    submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
    submitfile.write("asetup AnalysisTop,21.2.38,here \n")
    submitfile.write("source */setup.sh \n")
    submitfile.write("cd ../run/ \n")
    submitfile.write("RunPseudoExp "+ParameterSgn+" "+fileName+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightName+" "+WeightName+" "+str(NrPE)+" "+str(DimensionFit)+" 1 \n")
    submitfile.write("rm "+SubmitFileName+" \n")
    submitfile.close()
    cmd = "chmod a+x " + SubmitFileName
    os.system(cmd)
    cmd = "sbatch -p standard "+SubmitFileName
    os.system(cmd)

        
        #os.system("RunPseudoExp "+ParameterSgn+" "+fileName+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightName+" "+WeightName+" "+str(NrPE)+" "+str(DimensionFit)+" 1 ")


InputFolderClosure  = OutputFolder
OutputFolderClosure = "OutputTest_Closure"

os.system("mkdir -p "+OutputFolderClosure)

FileString = str(NrPE)+"PE_"+str(DimensionFit)+"D"

os.system("MakeClosureTests "+InputFolderClosure+" "+OutputFolderClosure+" "+str(DimensionFit)+" "+str(NrPE)+" "+FileString+" mtop ") # mtop, jsf, bjsf

if DimensionFit > 1:
    os.system("MakeClosureTests "+InputFolderClosure+" "+OutputFolderClosure+" "+str(DimensionFit)+" "+str(NrPE)+" "+FileString+" jsf ") # mtop, jsf, bjsf 
