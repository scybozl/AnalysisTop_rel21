#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
from ROOT import *
import SuperScriptPlots


DSID        = sys.argv[1]
InputFolder = sys.argv[2]
OutputFile  = sys.argv[3]
MCDataFlag  = sys.argv[4]
TreeName    = sys.argv[5]
WeightName  = sys.argv[6]
Channel     = sys.argv[7]
Flag        = sys.argv[8]
Cuts        = "" 

if len(sys.argv) > 9:
    Cuts = sys.argv[9]

SuperScriptPlots.FillHistograms(DSID, InputFolder, OutputFile, MCDataFlag, TreeName, WeightName, Channel, Flag, Cuts)
