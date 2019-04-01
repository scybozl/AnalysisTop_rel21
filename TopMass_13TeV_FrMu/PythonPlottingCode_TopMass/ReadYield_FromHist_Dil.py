#! /usr/bin/python

import os,subprocess
from ROOT import *

#/../run_dilepton/Histograms_dilepton_2015_16_Merged/Merge

InputFolder  = "../../../Downloads_21.2.51/Output_Win_MET_2tags_KLF_100_100/Histograms_lepjets_2015_16_Merged/"

InputFiles = []
InputFiles.append("Merge_Signal_169_MC16a.root")
InputFiles.append("Merge_Signal_171_MC16a.root")
InputFiles.append("Merge_Signal_172_MC16a.root")
InputFiles.append("Merge_Signal_172p25_MC16a.root")
InputFiles.append("Merge_Signal_172p5_MC16a.root")
InputFiles.append("Merge_Signal_172p75_MC16a.root")
InputFiles.append("Merge_Signal_173_MC16a.root")
InputFiles.append("Merge_Signal_174_MC16a.root")
InputFiles.append("Merge_Signal_176_MC16a.root")


for InputFile in InputFiles:
    fHelp     = TFile(InputFolder+"/"+InputFile, "READ")
    histoHelp = fHelp.Get("h_mtop_param")
    diff = (479944.077978 - histoHelp.Integral())/479944.077978*100
    print InputFile,"  ",histoHelp.Integral(),"   ",round(diff, 2)
