#! /usr/bin/python

import os,subprocess
from ROOT import *

InputFile = "/ptmp/mpp/knand/TopMass_13TeV/Downloads_21.2.38//Output_Win_MET_2tags_KLF_100_100//Histograms_lepjets_2015_16_Unmerged//Tree_410470_MC16a.root"

newChain = TChain("PE_Tree")
newChain.Add(InputFile)


#print newChain.GetEntries()

nr = 0

for i in range(0, newChain.GetEntries()):
    newChain.GetEntry(i)
    nr += newChain.weight_mc*newChain.weight_pileup*newChain.weight_leptonSF*newChain.weight_jvt*newChain.weight_bTagSF_MV2c10_77*newChain.NormFactor
    

print nr
