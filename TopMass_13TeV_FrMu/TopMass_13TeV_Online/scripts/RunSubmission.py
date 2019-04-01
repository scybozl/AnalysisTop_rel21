#! /usr/bin/python                                                                                                                                                                                       

import os,sys
import glob
import array
from ROOT import *
import math
from array import array
from copy import copy

import TopExamples.grid

sys.path.append('BookkeepingCode')

from SubmissionDict import *
from DefineSamples import *
from HelperFunctions import *

doMakeDerivationLists = False
doCheckConfigFiles    = True

# say what default ptag you want to use for the derivations
default_ptag = "p3629"

#change the output_tag according to what version of AT you are running over (here: 21.2.58)
output_tag   = "21258_V1"

# comment in or out what you want to run over
CampaignList = ["MC16a"] #, "MC16d", "MC16e",  "Data"]
TypeList     = ["SYSLJ_BTAG"]  #["NOM",   "TMPL",  "SYSDIL", "SYSLJ", "TEST", "SYSLJ_oldQG", "SYSLJ_BTAG"]
BTagList     = ["TAG70"]

# from here on you do not need to make further changes
DerivList_MC16a = "InputLists/DerivationList_MC16a.txt"
DerivList_MC16d = "InputLists/DerivationList_MC16d.txt"
DerivList_MC16e = "InputLists/DerivationList_MC16e.txt"
DerivList_Data  = "InputLists/DerivationList_Data.txt"

JSFList = []
JSFList.append([0.98,  1.00])
JSFList.append([0.99,  1.00])
JSFList.append([0.995, 1.00])
JSFList.append([1.00,  1.00])
JSFList.append([1.005, 1.00])
JSFList.append([1.01,  1.00])
JSFList.append([1.02,  1.00])
JSFList.append([1.00,  0.98])
JSFList.append([1.00,  0.99])
JSFList.append([1.00,  0.995])
JSFList.append([1.00,  1.005])
JSFList.append([1.00,  1.01])
JSFList.append([1.00,  1.02])

DerivList    = [DerivList_MC16a, DerivList_MC16d, DerivList_MC16e, DerivList_Data]

if doMakeDerivationLists:
    if not os.path.exists(DerivList_MC16a): 
        MakeInputFileLists(DerivList_MC16a, "MC16a", default_ptag)
    if not os.path.exists(DerivList_MC16d):
        MakeInputFileLists(DerivList_MC16d, "MC16d", default_ptag)
    if not os.path.exists(DerivList_MC16e):
        MakeInputFileLists(DerivList_MC16e, "MC16e", default_ptag)


# check only if all config files are there that you want to run over, do NOT make them automatically (too paranoid for now)
if doCheckConfigFiles:
    for Campaign in CampaignList:
        for BTag in BTagList:
            for Type in TypeList:
                if Campaign == "Data" and Type != "NOM":
                    continue
                # we need the list since for the templates we will submit all config files in one go
                ConfigList = []
                if Type == "TMPL":
                    for entry in JSFList:
                        JSF      = str(entry[0]).replace(".", "p")
                        bJSF     = str(entry[1]).replace(".", "p")
                        JSF_val  = entry[0]
                        bJSF_val = entry[1]
                        ConfigFile = "ConfigFiles/TopMassConfig_"+Campaign+"_"+Type+"_"+JSF+"_"+bJSF+"_"+BTag+".txt"
                        if os.path.exists(ConfigFile):
                            ConfigList.append(ConfigFile)
                        else:
                            print "ERROR: Config file "+ConfigFile+" does not exists! ---> EXIT."
                            break
                else:
                    ConfigFile = "ConfigFiles/TopMassConfig_"+Campaign+"_"+Type+"_"+BTag+".txt"
                    if os.path.exists(ConfigFile):
                        ConfigList.append(ConfigFile)
                    else:
                        print "ERROR: Config file "+ConfigFile+" does not exists! ---> EXIT."
                        break

                if len(ConfigList) == 0:
                    continue

                ConfigFileString = ""

                for i in range(0, len(ConfigList)):
                    Config = ConfigList[i]
                    if i == len(ConfigList)-1:
                        ConfigFileString += Config
                    else:
                        ConfigFileString += Config+","

                if Type != "NOM" and Type != "TEST":
                    output_tag += "_"+Type

                config = TopExamples.grid.Config()
                config.code          = 'top-xaod'
                config.settingsFile  = ConfigFileString
                config.gridUsername  = 'aknue' # use e.g. phys-top or phys-higgs for group production                                                                                                  
                config.suffix        = output_tag
                config.excludedSites = ''
                config.noSubmit      = False
                config.mergeType     = 'Default'
                config.destSE        = '' #This is the default (anywhere), or try e.g. 'UKI-SOUTHGRID-BHAM-HEP_LOCALGROUPDISK'                                                                          
                config.maxNFilesPerJob = '2'
                
                if Campaign == "Data":
                    config.maxNFilesPerJob = '10'

                # config.memory = '4000'                                                                                                                                                               
                config.otherOptions = '--unlimitNumOutputs --long --expertOnly_skipScout --extFile=FlavComp_21256_Dil.root,FlavComp_21256_LJ.root '   # '--unlimitNumOutputs'    
                
                # WARNING!!! NEEDS TO BE CHANGED !!!
                SampleList = [] 
                
                if Campaign == "MC16a":
                    SampleList = ReturnNames(DerivList_MC16a, Type)
                if Campaign == "MC16d":
                    SampleList = ReturnNames(DerivList_MC16d, Type)
                if Campaign == "MC16e":
                    SampleList = ReturnNames(DerivList_MC16e, Type)
                if Campaign == "Data":
                    SampleList = ReturnNames(DerivList_Data,  Type)

                print SampleList

                TopExamples.grid.Add("TOPQ1").datasets = SampleList

                samples = TopExamples.grid.Samples(["TOPQ1"])

                TopExamples.grid.submit(config, samples)
