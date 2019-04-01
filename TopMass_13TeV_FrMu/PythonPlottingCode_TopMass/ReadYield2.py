#! /usr/bin/python

import os,subprocess
from ROOT import *

InputFile = "../../../Downloads_21.2.38/Files_2015_16/user.aknue.410470.PhPy8EG.DAOD_TOPQ1.e6337_s3126_r9364_p3554.2-38_V1_output_root/user.aknue.14757104._000001.output.root"

newChain = TChain("sumWeights")
newChain.Add(InputFile)


#print newChain.GetEntries()

nr = 0

sum = 0
sumTree = 0

fHelp     = TFile(InputFile, "READ")
histoHelp = fHelp.Get("ejets_2016/cutflow_mc")
sum       = histoHelp.GetBinContent(1)

for i in range(0, newChain.GetEntries()):
    newChain.GetEntry(i)
    #nr += newChain.weight_mc*newChain.weight_pileup*newChain.weight_leptonSF*newChain.weight_jvt*newChain.weight_bTagSF_MV2c10_77*newChain.NormFactor

    
    for j in range(0, len(newChain.names_mc_generator_weights)):
        print j,"  ",newChain.names_mc_generator_weights[j]


    sumTree += newChain.totalEventsWeighted_mc_generator_weights[0]


print sum,"  ",sumTree,"  ",1-sum/sumTree
