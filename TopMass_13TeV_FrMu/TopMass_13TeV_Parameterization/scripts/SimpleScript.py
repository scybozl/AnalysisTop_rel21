#! /usr/bin/python

import glob
import os
import sys

Executable1 = "RunSepFitPar"
Executable2 = "RunCombFitPar"
histo_name = "hist_klf_window_mtop_reco"
#histo_name = "hist_klf_window_mw_reco"
#histo_name = "hist_klf_window_rbq_reco"
#histo_name = "hist_klf_window_mlb_reco"
#histo_name = "hist_klf_original_mlb_reco"
ConfigFileName = "../TopMass_13TeV_FrMu/TopMass_13TeV_Parameterization/data/MainConfigFile_LJ"

cmd1 = Executable1 + " " + histo_name + " " + ConfigFileName
cmd2 = Executable2 + " " + histo_name + " " + ConfigFileName

print(cmd1)
os.system(cmd1)

print(cmd2)
os.system(cmd2)
