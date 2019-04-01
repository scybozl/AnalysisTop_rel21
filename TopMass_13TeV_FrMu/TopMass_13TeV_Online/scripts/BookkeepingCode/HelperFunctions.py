#! /usr/bin/python                                                                                                                                                                                        

import os,sys
import glob

from SubmissionDict import *
from DefineSamples import *
from HelperFunctions import *

import pyAMI
import pyAMI.client
import pyAMI.atlas.api

client = pyAMI.client.Client('atlas')
pyAMI.atlas.api.init()


def MakeInputFileLists(OutputFileName, Campaign, ptag):

    fOutFile = open(OutputFileName, 'w')

    DSIDList = []
    

    for name, entry in SampleDict.items():
        dsid_list = entry[0] 
        
        for dsid in dsid_list:
            DSIDList.append(dsid)

    # now make sure that there are no duplicates
    print len(DSIDList)
    DSIDList = sorted(list(set(DSIDList)))
    print len(DSIDList)

    for dsid in DSIDList:

        currentPattern = "mc16_13TeV.%s" % (dsid) + ".%.DAOD_TOPQ1.%_r9364_"+ptag+"/"

        if Campaign == "MC16d":
            currentPattern = "mc16_13TeV.%s" % (dsid) + ".%.DAOD_TOPQ1.%_r10201_"+ptag+"/"
        if Campaign == "MC16e":
            currentPattern = "mc16_13TeV.%s" % (dsid) + ".%.DAOD_TOPQ1.%_r10724_"+ptag+"/"

        #print currentPattern  a875
        fullList = pyAMI.atlas.api.list_datasets(client, patterns=currentPattern)

        if len(fullList) == 0:
            print "WARNING: Did not find container for following expression: ",currentPattern
            currentPattern = currentPattern.replace("DAOD_TOPQ1", "AOD")
            currentPattern = currentPattern.replace("_"+ptag, "")
            fullList = pyAMI.atlas.api.list_datasets(client, patterns=currentPattern)
            print "You have to request the derivation for"
            for currentEntry in fullList:
                print currentEntry["ldn"]
        else:
            for currentEntry in fullList:
                fileName = currentEntry["ldn"]
                #print fileName
                fOutFile.write(fileName+"\n")

    fOutFile.close()


def ReturnExactSample(List, dsid, Type):

    OutputList = []

    for line in List:
        line = line.replace("\n", "")
        if dsid in line:
            OutputList.append(line)

    # if two samples are found (aka AFII and FS), return only appropriate sample
    if len(OutputList) > 1:
        for entry in OutputList:
            if "_a87" in entry and Type == "TMPL":
                return entry
            if "_s3126" in entry and Type != "TMPL":
                return entry

    if len(OutputList) == 0:
        return []

    return OutputList[0]

        
            


def ReturnNames(DerivListFile, Type):

    DSIDList = []

    for name, entry in SampleDict.items():
        dsids = entry[0]

        if Type == "TEST":
            if entry[5] != True:
                continue
            else:
                DSIDList += dsids
        if Type == "NOM":
            if entry[1] != True:
                continue
            else:
                DSIDList += dsids
        if Type == "TMPL":
            if entry[2] != True:
                continue
            else:
                DSIDList += dsids
        if "SYSDIL" in Type:
            if entry[3] != True:
                continue
            else:
                DSIDList += dsids
        if "SYSLJ" in Type:
            if entry[4] != True:
                continue
            else:
                DSIDList += dsids



    DerivList = []

    fInFile = open(DerivListFile, 'r')
    fLines  = fInFile.readlines()

    for dsid in DSIDList:
        HelpList = ReturnExactSample(fLines, dsid, Type)
        if len(HelpList) != 0:
            DerivList.append(HelpList)


    return DerivList
