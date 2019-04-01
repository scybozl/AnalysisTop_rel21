#! /usr/bin/python

import os,sys
import glob
import array
from ROOT import *

from copy import copy
sys.path.append('../SortingScripts/')
from VariableList import *
sys.path.append('../')
from MassSuperScriptPlots import *

doFillHistos = True
doPlotHistos = True


InputFolder = sys.argv[1]
OutputFile  = sys.argv[2]
DSID        = sys.argv[3]
Lumi        = 36.1
Tree        = "nominal"

InputFiles  = glob.glob(InputFolder+"/*root*")

ListPlots   = ReturnVariableList_2D()

Cuts_Window_LJ = "*(tma_klfitter_mtop_param[0]>125.0 && tma_klfitter_mtop_param[0]<200.0)*(tma_original_mw[0]>55.0 && tma_original_mw[0]<110.0)*(tma_original_rbq[0]>0.3 && tma_original_rbq[0]<3.0)"
Cuts_MET       = "*(met_met/1000.0 > 20.0)"
Cuts_NBTAG     = "*(tma_nbjets == 2)"
Cuts_NJETS     = "*(tma_njets  <= 6)"

CUTS = Cuts_Window_LJ+Cuts_MET+Cuts_NBTAG+Cuts_NJETS

ChannelList = ["ejets_2015", "ejets_2016", "mujets_2015", "mujets_2016"]

ChannelFlag = "("

for i in range(0, len(ChannelList)):
    entry = ChannelList[i]

    entry = entry.replace("", "")

    Histo = AddBKHistograms(InputFiles, entry)
    NormEvents = Histo.GetBinContent(1)
    if i < len(ChannelList)-1:
        ChannelFlag += entry+" || "
    else:
        ChannelFlag += entry+")"

if doFillHistos:

    CrossSection = GetCrossSection(DSID)
    NormFactor   = CrossSection*Lumi/NormEvents

    fT      = MakeChain(InputFiles, Tree+"")
    entries = fT.GetEntries()
    fF_out  = TFile(OutputFile, "RECREATE")
    FullWeight = "weight_mc*weight_pileup*weight_leptonSF*weight_jvt*weight_bTagSF_MV2c10_77*"+str(NormFactor)

    for Var in ListPlots:
        
        varName1   = Var[0]
        varName2   = Var[1]
        NBins1     = Var[2]
        lowEdge1   = Var[3]
        highEdge1  = Var[4]
        NBins2     = Var[5]
        lowEdge2   = Var[6]
        highEdge2  = Var[7]
        doOverflow = Var[8]
        histName   = Var[9]

        #VariableList.append(["tma_klfitter_mtop_param[0]", "tma_original_mw[0]",  75, 125.0, 200.0, 55, 55.0, 110.0, True, "h_2D_mtop_mw",  "m_{top}^{reco} [GeV] (KLFitter)", "m_{W}^{reco} [GeV]"])
        
        h_tmp = TH2D(histName, histName, NBins1, lowEdge1, highEdge1, NBins2, lowEdge2, highEdge2)
        h_tmp.Sumw2()
            
        fT.Project(h_tmp.GetName(), varName2+":"+varName1, ChannelFlag+"*"+str(FullWeight)+CUTS)
            
        #if doOverflow:
        #    h_tmp = AddOverflows(h_tmp)
                
        h_tmp.Write(histName)

        print h_tmp.GetCorrelationFactor()
                        
            
        #for entry in BKHistos:
        #    entry[0].Write(entry[1])
                            
    fF_out.Close()



if doPlotHistos:
    for Var in ListPlots:
        histName = Var[9]
        xTitle   = Var[10]
        yTitle   = Var[11]

        fF_in  = TFile(OutputFile, "READ")
        fHist  = fF_in.Get(histName) 

        c = TCanvas(histName, histName, 10, 10, 700, 600)
        
        style=gStyle
        style.SetOptStat(0)
        style.SetOptTitle(0)
        style.SetFrameBorderMode(0)
        style.SetFrameFillColor(0)
        style.SetCanvasBorderMode(0)
        style.SetCanvasColor(0)
        style.SetPadBorderMode(0)
        style.SetPadColor(0)
        style.SetStatColor(0)
        style.SetPalette(1) #kTemperatureMap)

        fHist.GetXaxis().SetTitle(xTitle)
        fHist.GetYaxis().SetTitle(yTitle)
        fHist.GetXaxis().SetTitleOffset(1.05)
        fHist.GetYaxis().SetTitleOffset(1.05)
        fHist.GetXaxis().SetTitleSize(0.045)
        fHist.GetYaxis().SetTitleSize(0.045)
        fHist.Draw("COLZ")

        Corr = round(fHist.GetCorrelationFactor()*100.0, 2)

        l = TLatex()
        l.SetNDC()
        l.SetTextFont(72)
        l.SetTextColor(1)
        l.SetTextSize(0.042)
        l.DrawLatex(0.38, 0.915, "ATLAS")
        l.SetTextFont(42)
        l.DrawLatex(0.50, 0.915, "Internal Simulation, 13 TeV")
        l.DrawLatex(0.11, 0.915, "#rho = "+str(Corr)+" %")

        outputPDF = histName.replace("h_", "Corr_")+".pdf"

        c.SetTicks(1,1)
        c.SetRightMargin(0.12)
        c.Print(outputPDF)
