#! /usr/bin/python                                                                                                                                                                                       

import glob,sys,subprocess,os
sys.path.append('SortingScripts')
from ListSystematics import *

MainFolder   = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.51/"
CodeFolder   = "/ptmp/mpp/knand/TopMass_13TeV/Rel21_AnalysisTop_21.2.51_MTOP/build/"
RunFolder    = "/ptmp/mpp/knand/TopMass_13TeV/Rel21_AnalysisTop_21.2.51_MTOP/run_51/"
ParamFolder  = RunFolder+"/combfit_output/"
OutputFolder = RunFolder+"/OutputTest_V2/"
AnalysisTop  = "21.2.51"

DimensionFit = 2 # 1: mtop only, 2: mtop+jsf, 3:mtop+jsf+bjsf    
TreeName     = "PE_Tree"
WeightName   = "nominal"
NrPE         = 1

# NominalFile  = MainFolder+"/Win2_MET_2tags_KLF/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_PP8_MC16a.root"
NominalFile  = MainFolder+"/Output_Win2_MET_2tags_KLF/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_PP8_MC16a.root"
SystNomFile  = MainFolder+"/Output_Win2_MET_2tags_KLF_AF_SYST/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_PP8_MC16a.root"
SystNomFile2 = MainFolder+"/Output_Win2_MET_2tags_KLF/Histograms_lepjets_nominal_Merged/Merge_Tree_ttbar_PP8_MC16a.root"
SystNomFile3 = MainFolder+"/Output_Win2_MET_2tags_KLF_AF/Histograms_lepjets_2015_16_Merged/Merge_Tree_ttbar_PP8_Rad_MC16a.root"


ModellingVar = []
ModellingVar.append([NominalFile.replace("PP8", "aMC"), (ReturnGeneratorSyst())[0][1]])
ModellingVar.append([NominalFile.replace("PP8", "PH7"), (ReturnHadronisationSyst())[0][1]])
ModellingVar.append([SystNomFile3, "ISRup"])
ModellingVar.append([SystNomFile2, "ISRdown"])
ModellingVar.append([SystNomFile2, "FSRup"])
ModellingVar.append([SystNomFile2, "FSRdown"])

os.system("mkdir -p "+OutputFolder)

SFList = ReturnSFSystList()

for Category in SFList:
    
    for i in range(1,3):

        Name  = Category[0]
        SF    = Category[i]
        SFnom = Category[3]

        WeightPos = 0

        if "bTag" in SF:
            if "extrapolation" in SF:
                WeightPos = -1
                SF_label  = SF
            else:
                nr        = len(SF.split("_"))
                WeightPos = (SF.split("_"))[nr-1]

                SF_label   = (SF.split("up_"+str(WeightPos)))[0]+"up"
            
                if "down" in SF_label:
                    SF_label   = (SF.split("down_"+str(WeightPos)))[0]+"down"
        else:
            SF_label = SF
        

        fileString = SF+"_"+str(NrPE)+"PE_"+str(DimensionFit)+"D"

        OutputFile   = OutputFolder+"/"+fileString+".root"
        #print fileString,"   ",SF_label,"   ",SF,"  ",WeightPos
        
        if os.path.exists(OutputFile):
            continue

        # now make submission files                                                                                                                                                 
        SubmitFileName = os.getcwd()+"/Submit_PEXP_"+fileString+".sh"

        if os.path.exists(SubmitFileName):
            continue

        submitfile     = open(SubmitFileName, "w")
        submitfile.write("#! /bin/bash \n")
        submitfile.write("cd "+CodeFolder+" \n")
        submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
        submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
        submitfile.write("asetup AnalysisTop,"+AnalysisTop+",here \n")
        submitfile.write("source */setup.sh \n")
        submitfile.write("RunPseudoExp "+ParamFolder+" "+NominalFile+" "+OutputFolder+" "+fileString+" "+TreeName+" "+SFnom+" "+SF_label+" "+str(WeightPos)+" "+str(NrPE)+" "+str(DimensionFit)+" 1 \n")
        submitfile.write("rm "+SubmitFileName+" \n")
        submitfile.close()
        cmd = "chmod a+x " + SubmitFileName
        os.system(cmd)
        cmd = "sbatch -p standard "+SubmitFileName
        os.system(cmd)

        #sys.exit()


#sys.exit()

# now get all names of systematic trees in the fullsim samples
SystTreeList = ReturnTreeList()

for Tree in SystTreeList:
    print Tree

    fileString   = Tree+"_"+str(NrPE)+"PE_"+str(DimensionFit)+"D"
    OutputFile   = OutputFolder+"/"+fileString+".root"
    
    if os.path.exists(OutputFile):
        continue
    # now make submission files

    SubmitFileName = os.getcwd()+"/Submit_PEXP_"+fileString+".sh"

    if os.path.exists(SubmitFileName):
        continue

    SystFile = SystNomFile.replace("lepjets_2015_16", "lepjets_"+Tree)
    print SystFile

    if not os.path.exists(SystFile):
        continue

    submitfile     = open(SubmitFileName, "w")
    submitfile.write("#! /bin/bash \n")
    submitfile.write("cd "+CodeFolder+" \n")
    submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
    submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
    submitfile.write("asetup AnalysisTop,"+AnalysisTop+",here \n")
    submitfile.write("source */setup.sh \n")
    submitfile.write("RunPseudoExp "+ParamFolder+" "+SystFile+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightName+" "+WeightName+" 0  "+str(NrPE)+" "+str(DimensionFit)+" 1 \n")

    #print "RunPseudoExp "+ParamFolder+" "+SystFile+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightName+" "+WeightName+" 0  "+str(NrPE)+" "+str(DimensionFit)+" 1 \n"

    submitfile.write("rm "+SubmitFileName+" \n")
    submitfile.close()
    cmd = "chmod a+x " + SubmitFileName
    os.system(cmd)
    cmd = "sbatch -p standard "+SubmitFileName
    os.system(cmd)


for entry in ModellingVar:
    
    UncName = entry[1]
    UncFile = entry[0]

    fileString   = UncName+"_"+str(NrPE)+"PE_"+str(DimensionFit)+"D"
    OutputFile   = OutputFolder+"/"+fileString+".root"

    if os.path.exists(OutputFile):
        continue
    # now make submission files                                                                                                                                                                                                                                       

    SubmitFileName = os.getcwd()+"/Submit_PEXP_"+fileString+".sh"

    if os.path.exists(SubmitFileName):
        continue

    SystFile = UncFile

    if not os.path.exists(SystFile):
        continue

    WeightNameNom = "nominal"
    WeightNameSys = "nominal"

    if UncName == "ISRup":
        WeightNameSys = "weight_ISR05"
    if UncName == "ISRdown":
        WeightNameSys = "weight_ISR20"
    if UncName == "FSRup":
        WeightNameSys = "weight_FSR05"
    if UncName == "FSRdown":
        WeightNameSys = "weight_FSR20"


    submitfile     = open(SubmitFileName, "w")
    submitfile.write("#! /bin/bash \n")
    submitfile.write("cd "+CodeFolder+" \n")
    submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
    submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
    submitfile.write("asetup AnalysisTop,"+AnalysisTop+",here \n")
    submitfile.write("source */setup.sh \n")
    submitfile.write("RunPseudoExp "+ParamFolder+" "+SystFile+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightNameNom+" "+WeightNameSys+" 0  "+str(NrPE)+" "+str(DimensionFit)+" 1 \n")

    #print "RunPseudoExp "+ParamFolder+" "+SystFile+" "+OutputFolder+" "+fileString+" "+TreeName+" "+WeightName+" "+WeightName+" 0  "+str(NrPE)+" "+str(DimensionFit)+" 1 \n"

    submitfile.write("rm "+SubmitFileName+" \n")
    submitfile.close()
    cmd = "chmod a+x " + SubmitFileName
    os.system(cmd)
    cmd = "sbatch --mem=4000 "+SubmitFileName
    os.system(cmd)



#ModellingVar.append([NominalFile.replace("PP8", "aMC"), (ReturnGeneratorSyst())[1]])
#ModellingVar.append([NominalFile.replace("PP8", "PH7"), (ReturnHadronisationSyst())[1]])
