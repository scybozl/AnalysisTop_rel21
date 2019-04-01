#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
from ROOT import *
import MassSuperScriptPlots
import ListSystematics

#######################################################################################
#
# idea: scripts decides based on the r-tag, if a sample is MC16a or c
# then the histograms are filled for the respective container accordingly
# meaning that if its mc16a, it runs with the 2015 and 2016 flag, and for
# mc16d with the 2017 flag
# it writes out one root file for each input folder, and names it accordingly
# for example: Histogram_410470_mc16a.root 
# in the merging step then three files are created:
# eg Merge_ttbar.root, Merge_ttbar_mc16a.root and Merge_ttbar_mc16d.root, so that 
# we can make plots seperately for each case (easier to compare with plots we 
# made in 20.7) and for the merged one
#
#######################################################################################

fLocal = os.getcwd()

def SubmitToCluster(MainInputFolder, MainOutputFolder, SubmissionFolder, Channel, TreeName, WeightName, ReleaseFlag, Flag, Cuts):
    
    InputFolders = glob.glob(MainInputFolder+"/*")
    
    for InputFolder in InputFolders:

        #print InputFolder

        # now determine DSID
        Folder     = InputFolder.replace(MainInputFolder, "")
        InputFiles = glob.glob(InputFolder+"/*root*")

        if len(InputFiles) == 0:
            print "No input files for folder "+InputFolder
            continue

        array   = Folder.split(".")
        DSID    = array[2]

        #######################################

        IsMC16d = True

        if "r9364" in Folder:
            IsMC16d = False

        IsData = False
        if "data" in Folder or "grp" in Folder:
            IsData = True

        OutputFlag = "bla"
        DataMCFlag = "bla"

        if not IsData:
            if not IsMC16d:
                DataMCFlag = "MC16a"
            else:
                DataMCFlag = "MC16d"

            if ReleaseFlag != "Rel21":
                DataMCFlag = "MC15"

            OutputFlag = str(DSID)+"_"+DataMCFlag
        else:
            DataMCFlag = "Data"
            OutputFlag = ""
            if "grp15" in InputFolder:
                OutputFlag = "data2015"
            if "grp16" in InputFolder:
                OutputFlag = "data2016"
            if "grp17" in InputFolder:
                OutputFlag = "data2017"

            DSID       = array[2]
            if ReleaseFlag != "Rel21":
                DSID = array[2]+"."+array[3]
                OutputFlag = array[5] #+"."+array[3]
                DataMCFlag = "Data15"


        OutputFile     = MainOutputFolder+"/Histogram_"+OutputFlag+".root"
        SubmitFileName = SubmissionFolder+"/DoSubmitJob_"+OutputFlag+"_"+Flag+"_"+Channel+"_"+TreeName+".sh"

        #print OutputFile

        if os.path.exists(OutputFile):
            continue
        if os.path.exists(SubmitFileName):
            print "WARNING: Submission file "+SubmitFileName+" already exists, will not re-make it... "
            continue

        #print SubmissionFolder
        #print SubmitFileName

        submitfile     = open(SubmitFileName, "w")
        submitfile.write("#! /bin/bash \n")
        submitfile.write("mkdir $TMPDIR/$SLURM_JOB_ID \n")
        submitfile.write("cd $TMPDIR/$SLURM_JOB_ID \n")
        submitfile.write("cp -r "+fLocal+"/* . \n")
        submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
        submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
        submitfile.write("localSetupROOT 6.10.04-x86_64-slc6-gcc62-opt \n")
        submitfile.write("python RunJobCluster.py "+str(DSID)+" "+InputFolder+" "+OutputFile+" "+DataMCFlag+" "+TreeName+" "+WeightName+" "+Channel+" "+Flag+" "+Cuts+"\n")
        submitfile.write("cd ../ \n")
        submitfile.write("rm -rf $TMPDIR/$SLURM_JOB_ID \n")
        submitfile.write("rm "+SubmitFileName+" \n")
        submitfile.close()
        cmd = "chmod a+x " + SubmitFileName
        os.system(cmd)
        cmd = "sbatch -p standard "+SubmitFileName
        os.system(cmd)

