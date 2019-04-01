#! /bin/python

#ssh username@lxplus.cern.ch "cern-get-sso-cookie -u https://bigpanda.cern.ch/ -o bigpanda.cookie.txt;"
#ssh username@lxplus.cern.ch 'curl -b ~/bigpanda.cookie.txt -H '"'"'Accept: application/json'"'"' -H '"'"'Content-Type: application/json'"'"' "https://bigpanda.cern.ch/tasks/?taskname=user.nacken*&days=3&json"'

# sed -i 's/null/0/g' GridDict.py

from GridDict import *
from glob import glob
from ROOT import TFile,TH1D

InputFolders = glob("Files_*/*/")


def AddBKHistograms(ListFiles, Channel):
    # open file number one and store histogram in new histo
    Channel = Channel.replace("", "")

    fF = TFile(ListFiles[0], "READ")
    histo = TH1D()
    histo = fF.Get(Channel+"/cutflow")

    for i in range(1, len(ListFiles)):
        fHelp     = TFile(ListFiles[i], "READ")
        histoHelp = fHelp.Get(Channel+"/cutflow")
        histo.Add(histoHelp)
        fHelp.Close()

    #return copy(histo
    return histo.GetBinContent(1)


RunIncomplete = []
RunComplete   = []
DL_Incomplete = []
DL_Complete   = []
NoOutputCont  = []

for line in GridDict:
    datasets   = line.get('datasets')
    jeditaskid = line.get('jeditaskid')
    #print "======================================================================================================================="

    # now get a global overview and add all relevant numbers here
    InputContainer  = ""
    OutputContainer = ""
    nevents_total   = 0
    nevents_used    = 0
    

    for dataset in datasets:
        status = dataset.get('status')

        container = dataset.get('containername')
        if "user.aknue." in container:
            OutputContainer = container
        else:
            InputContainer  = container

        
        nevents_total += dataset.get('nevents')
        nevents_used  += dataset.get('neventsused')

    #print InputContainer
    #print OutputContainer
    #print nevents_total
    #print nevents_used
    frac_run = float(nevents_used)/float(nevents_total)


    nevents_downloaded = 0
            
    if OutputContainer == "":
        #print "NO OUTPUT CONTAINER, NEED TO CHECK!"
        NoOutputCont.append([InputContainer, jeditaskid])
        continue

    for Folder in InputFolders:
        if OutputContainer in Folder:
            #print Folder
            # ok now that we know what downloaded folder the above numbers correspond to:
            # make list of files in folder
            # loop over files and get information from bookkeeping tree
            # then compare with above numbers
            ListFiles = glob(Folder+"/*root*")
            #print ListFiles
            nevents_downloaded = AddBKHistograms(ListFiles, "ejets_2015")
    
    #print nevents_downloaded
    frac_dl    = float(nevents_downloaded)/float(nevents_used)
    frac_total = float(nevents_downloaded)/float(nevents_total)

    if frac_run != 1.0:
        RunIncomplete.append([OutputContainer, frac_run, jeditaskid])
    else:
        RunComplete.append([OutputContainer, frac_run])

    if frac_dl != 1.0:
        DL_Incomplete.append([OutputContainer, frac_dl])
    else:
        DL_Complete.append([OutputContainer, frac_dl])



print "==========================================================================================================="
print "==========================================================================================================="
print "============================================ SUMMARY ======================================================"
print "==========================================================================================================="
print "==========================================================================================================="

print "-------------------------------> Run Incomplete: "
for entry in RunIncomplete:
    print entry

print "-------------------------------> DL Incomplete: "
for entry in DL_Incomplete:
    print entry

print "-------------------------------> No output container: "
for entry in NoOutputCont:
    print entry
