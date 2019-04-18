#!/usr/bin/env python

# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
import TopExamples.grid
import DerivationTags
import Data_rel21
import MC16_TOPQ1

## fancy function to shorten the physics part of the name of a sample
#def MyFancyShortener(superLongInDSName):
    #splitted = superLongInDSName.split('.')
    #runNumber = splitted[1]
    #physicsName = splitted[2]
    #if splitted[0] == "user" or splitted[0] == "group": #this is in case we run on private derivations, either produced with user or group role
        #runNumber = splitted[2]
        #physicsName = splitted[3]
    #tags = splitted[-1].replace('/','')
    #physicsName = physicsName.split('_')[0]
    #outDSName = runNumber + '.' + physicsName + '.someFunnyTags'
    #return outDSName

config = TopExamples.grid.Config()
config.code          = 'top-xaod'
config.settingsFile  = 'UpfoldingRecoLevel.txt'

config.gridUsername  = 'lscyboz'
config.suffix        = 'mt173p0-t1'
config.excludedSites = ''
config.noSubmit      = False
config.mergeType     = 'Default' #'None', 'Default' or 'xAOD'
config.destSE        = '' #This is the default (anywhere), or try e.g. 'UKI-SOUTHGRID-BHAM-HEP_LOCALGROUPDISK'
#config.forceSite     = 'MPPMU'
#config.groupProduction = True # for group production only; if True, gridUsername must be e.g. 'phys-top'
# by default the requested memory is set to 2GB, if you need to increase this, please disable the line below!!!
# config.memory = '4000' 
#config.nameShortener = MyFancyShortener # to use your own physics part shortening function - uncomment here and in the function definition above

###############################################################################

###Command line interface
###If you want a script that ask you what you want to run on interactively,
###and uses lists of primary xAODs to convert them as TOPQ derivations
###Otherwise you can edit the automatic scripts below
#names, derivation, ptag = DerivationTags.InteractiveSubmission()
#samples = TopExamples.grid.Samples(names)
#TopExamples.grid.convertAODtoTOPQ(derivation, ptag, samples)
#TopExamples.grid.submit(config, samples)

###############################################################################

# Data - look in Data_rel21.py
# Change if you want TOPQ2/3/4/5
#names = ['Data15_TOPQ1', 
#         'Data16_TOPQ1', 
#         'Data17_TOPQ1']
#samples = TopExamples.grid.Samples(names)
#TopExamples.grid.submit(config, samples)

###############################################################################

###MC Simulation - look in MC16_TOPQ1.py
###Using list of TOPQ1 25ns MC samples, consistent mixture of p-tags
###Edit these lines if you don't want to run everything!
names = ['TOPQ1_ttbar_PowPy8']

samples = TopExamples.grid.Samples(names)
TopExamples.grid.submit(config, samples)

