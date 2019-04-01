#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
from ROOT import *
import SuperScriptPlots
import ListSystematics

sys.path.append('SortingScripts')

from MassDictionaries import *

#######################################################################################
#
# idea: scripts decides based on the r-tag, if a sample is MC16a, d or e
# then the histograms are filled for the respective container accordingly
# meaning that if its mc16a, it runs with the 2015 and 2016 flag, and for
# mc16d with the 2017 flag and mc16e with the 2018 flag
# it writes out one root file for each input folder, and names it accordingly
# for example: Hist_410470_mc16a.root 
# in the merging step then three files are created:
# eg Merge_ttbar.root, Merge_ttbar_mc16a.root and Merge_ttbar_mc16d.root, so that 
# we can make plots seperately for each case (easier to compare with plots we 
# made in 20.7) and for the merged one
#
#######################################################################################

fLocal = os.getcwd()

def SendToCluster(MainInputFolder, MainOutputFolder, SubmissionFolder, Channel, TreeName, WeightName, Flag, Cuts):
    
    MainOutputFolderMerged = MainOutputFolder.replace("Unmerged", "Merged")

    #print MainOutputFolder

    HelpFlag = MainOutputFolder.replace("Unmerged", "")
    HelpFlag = (HelpFlag.split("Out_"))[1]
    HelpFlag = HelpFlag.replace("/", "")

    os.system("mkdir -p "+MainOutputFolderMerged)

    List = []
    List.append(["MC16a", "r9364"])
    List.append(["MC16d", "r10201"])
    List.append(["MC16e", "r10724"])
    List.append(["data",  "_v0"])

    for entry in List:
        Campaign = entry[0]
        Pattern  = entry[1]

        # now we need to check if folders with all DSIDs required exist for this campaign, so we need to loop over the different processes
        for name, entry in SampleDict.items():

            if "dil" in name:
                # for lepton+jets we are running the dilepton samples in any case, do not want to interfere with jobs!!!
                if "lepjets" in Channel:
                    continue
                if "ejets" in Channel:
                    continue
                if "mujets" in Channel:
                    continue
            
            
            dsid_list = entry[0]
            #print dsid_list

            MergedOutputFileHist = MainOutputFolderMerged+"/Merge_Hist_"+name+"_"+Campaign+".root"
            MergedOutputFileTree = MainOutputFolderMerged+"/Merge_Tree_"+name+"_"+Campaign+".root"            

            # if merged samples already exist: do nothing
            if os.path.exists(MergedOutputFileHist) and os.path.exists(MergedOutputFileTree):
                # check output size, if compatible with zero, do run through
                file_hist = TFile(MergedOutputFileHist, "READ")
                if file_hist.GetSize() < 900:
                    os.system("rm "+MergedOutputFileHist)
                    os.system("rm "+MergedOutputFileTree)
                file_hist.Close()
                continue

            SubmissionList = []

            MergeStringHist = ""
            MergeStringTree = ""

            AllContainerAvailable = True

            for DSID in dsid_list:
                found = False

                #if "grp1" in DSID and "data" in Campaign:
                #    Pattern = ""

                #print MainInputFolder,"   ",DSID,"   ",Pattern
                HelpList = glob.glob(MainInputFolder+"/*"+DSID+"*"+Pattern+"*") 


                #print len(HelpList),"  ",MainInputFolder+"/*"+DSID+"*"+Pattern+"*"

                
                if len(HelpList) > 1:
                    print "ERROR::SubmitToCluster: have more than one candidate for submission!!!"
                    print HelpList
                    break
                if len(HelpList) == 1:
             
                    OutputFlag = str(DSID)+"_"+Campaign

                    OutputFileHist = MainOutputFolder+"/Hist_"+OutputFlag+".root"
                    OutputFileTree = MainOutputFolder+"/Tree_"+OutputFlag+".root"

                    found = True
                    
                    MergeStringHist += " "+OutputFileHist
                    MergeStringTree += " "+OutputFileTree

                    #print OutputFileHist

                    if os.path.exists(OutputFileHist) and os.path.exists(OutputFileTree):
                        continue

                    SubmissionList.append([DSID, HelpList[0], OutputFileHist, Campaign])

                if not found:
                    AllContainerAvailable = False

            # if container for one DSID is missing: do nothing
            if not AllContainerAvailable:
                continue

            SubmitFileName = SubmissionFolder+"/DoSubmitJob_"+name+"_"+Flag+"_"+Channel+"_"+HelpFlag+"_"+TreeName+".sh"


            if os.path.exists(SubmitFileName):
                print "WARNING: Submission file "+SubmitFileName+" already exists, will not re-make it... "
                continue

            
            submitfile     = open(SubmitFileName, "w")
            submitfile.write("#! /bin/bash \n")
            submitfile.write("mkdir $TMPDIR/$SLURM_JOB_ID \n")
            submitfile.write("cd $TMPDIR/$SLURM_JOB_ID \n")
            submitfile.write("cp -r "+fLocal+"/* . \n")
            submitfile.write("export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/ \n")
            submitfile.write("source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n")
            submitfile.write("localSetupROOT 6.10.04-x86_64-slc6-gcc62-opt \n")
            # here we need to loop now:

            for entry in SubmissionList:
                DSID        = entry[0]
                InputFolder = entry[1]
                OutputFile  = entry[2]
                Campaign    = entry[3]
                submitfile.write("python JobCluster.py "+str(DSID)+" "+InputFolder+" "+OutputFile+" "+Campaign+" "+TreeName+" "+WeightName+" "+Channel+" "+Flag+" "+Cuts+"\n")

            # if done with running the jobs, start merging the files:
            submitfile.write("hadd "+MergedOutputFileHist+"  "+MergeStringHist+" \n")
            submitfile.write("hadd "+MergedOutputFileTree+"  "+MergeStringTree+" \n")
            submitfile.write("cd ../ \n")
            submitfile.write("rm -rf $TMPDIR/$SLURM_JOB_ID \n")
            submitfile.write("rm "+SubmitFileName+" \n")
            submitfile.close()
            cmd = "chmod a+x " + SubmitFileName
            os.system(cmd)
            print SubmitFileName
            cmd = "sbatch -p standard "+SubmitFileName
            os.system(cmd)

