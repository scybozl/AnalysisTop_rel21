#! /usr/bin/python                                                                                                                                                                      

import os,sys
from glob import glob
#from ROOT import *

fLocal = os.getcwd()
fCode  = fLocal+"/../"

MainInputFolder  = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.58_withBDT/"
MainOutputFolder = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.58_withBDT_and_DNN/"

SubmissionFolder = MainInputFolder+"/SubmissionFolder/"

os.system("mkdir -p "+SubmissionFolder)
os.system("mkdir -p "+MainOutputFolder)

InputFolders  = []
InputFolders.append(MainInputFolder+"/Files_SYSLJ_FS/")
InputFolders.append(MainInputFolder+"/Files_NOM_FS/")
InputFolders.append(MainInputFolder+"/Files_NOM_AF/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_098/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_099/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_0995/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_100/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_1005/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_101/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_100_102/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_098_100/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_099_100/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_0995_100/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_1005_100/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_101_100/")
InputFolders.append(MainInputFolder+"/Files_TMPL_AF_102_100/")

List = []
List.append(["MC16a", "r9364"])
List.append(["MC16d", "r10201"])
List.append(["MC16e", "r10724"])
List.append(["MC16a", "grp1"])

InputFiles    = [] 
for InputFolder in InputFolders:

    for entry in List:
        Campaign = entry[0]
        Pattern  = entry[1]

        SubFolders = glob(InputFolder+"/*"+Pattern+"*/")

        for InputSubFolder in SubFolders:

            OutputSubFolder = InputSubFolder.replace(MainInputFolder, MainOutputFolder)

            os.system("mkdir -p "+OutputSubFolder)

            HelpString = (InputSubFolder.split("user.aknue."))[1]
            HelpString = HelpString.replace("/", "")
            HelpString = HelpString.replace(".root", "")

            # check folder content, if no root files in folder: do not submit
            nr_files_in  = len(glob(InputSubFolder+"/*root*"))

            if nr_files_in == 0:
                continue

            SubmitFileName = SubmissionFolder+"/DoSubmitJob_"+HelpString+"_"+Campaign+"_DNN.sh"
            print(SubmitFileName)

            if os.path.exists(SubmitFileName):
                continue

            # now: open a shell script
            submitfile     = open(SubmitFileName, "w")
            submitfile.write("#! /bin/bash \n")
            submitfile.write("mkdir $TMPDIR/$SLURM_JOB_ID \n")
            submitfile.write("cd $TMPDIR/$SLURM_JOB_ID \n")
            submitfile.write("cp -r "+fCode+"/* . \n")
            submitfile.write("cd ApplyBDTWeights/ \n")
            submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
            submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
            submitfile.write("cd TATORTCleaner/ \n")
            submitfile.write("source cvmfs-setup.sh \n")
            submitfile.write("cd  ../ \n")
            submitfile.write("python RunDNN_Cluster.py "+InputSubFolder+" "+OutputSubFolder+" \n")
            submitfile.write("cd ../ \n")
            submitfile.write("rm -rf $TMPDIR/$SLURM_JOB_ID \n")
            submitfile.write("rm "+SubmitFileName+" \n")
            submitfile.close()
            cmd = "chmod a+x " + SubmitFileName
            os.system(cmd)
            cmd = "sbatch -p standard "+SubmitFileName

            if "user.aknue.3*" in InputSubFolder:
                cmd = "sbatch -p short "+SubmitFileName

            if "SYS" in InputFolder:
                cmd = "sbatch -p long --mem=8000 "+SubmitFileName
            os.system(cmd)

            #break
