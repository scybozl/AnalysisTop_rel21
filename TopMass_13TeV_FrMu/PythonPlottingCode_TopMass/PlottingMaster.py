#! /usr/bin/python

import os
import sys
import glob

from ROOT import *
from ROOT import gStyle

from array import array
import math

# check sign
def CheckNominalPosition(up, down, nominal):

    Unc      = 0
    diffUp   = 0
    diffDown = 0

    # if the nominal lies between the up and down variation, then use (up-down)/2.0 as systematic uncertainty
    if up > nominal and down < nominal:
        Unc = (up-down)/2.0
    elif up < nominal and down > nominal:
        Unc = (down-up)/2.0
    else:
        diffUp   = up-nominal
        diffDown = nominal-down

        if math.fabs(diffUp) > math.fabs(diffDown):
            Unc = diffUp
        else:
            Unc = diffDown
    
    print round(Unc, 4)

    return Unc

    # otherwise implement what we used at 8 TeV: take the largest difference, but need to think what should define the sign of the shift

    
# this code does nothing else than looping over a tree and find the minimum and maximum values for a given variable
def FindEdges(FileName, TreeName, Parameter):

    lowerEdge =  1000
    upperEdge = -1000

    fF       = TFile(FileName, "READ")
    fT       = fF.Get(TreeName)
    entries  = fT.GetEntries()             
    LocalPar = array('d', [0])
    
    # need to use SetBranchAddress to call Variable by name, makes code more flexible
    fT.SetBranchAddress(Parameter, LocalPar)

    # loop over tree and find lower and upper edges
    for iEvent in range(0, entries):
        fT.GetEntry(iEvent)

        if LocalPar[0] < lowerEdge:
            lowerEdge = LocalPar[0]
        if LocalPar[0] > upperEdge:
            upperEdge = LocalPar[0]
            
    return lowerEdge, upperEdge


# fill now the histograms with the proper ranges, so that we can plot them all together
def FillHistos(FileName, TreeName, Parameter, LowerEdge, UpperEdge):

    hist    = TH1D("", "", 30, LowerEdge, UpperEdge)
    fF      = TFile(FileName, "READ")
    fT      = fF.Get(TreeName)
    entries = fT.GetEntries()

    LocalPar = array('d', [0])
    fT.SetBranchAddress(Parameter, LocalPar)
    
    for iEvent in range(0, entries):
        fT.GetEntry(iEvent)
        
        hist.Fill(LocalPar[0])
                        
    return hist


def PlotParameters(HistVec, NameVec, OutputFile, XLabel):

    c = TCanvas(NameVec[0], NameVec[0], 10, 10, 700, 600)

    style=TStyle() #gStyle
    style.SetOptStat(0)
    style.SetOptTitle(0)
    style.SetFrameBorderMode(0)
    style.SetFrameFillColor(0)
    style.SetCanvasBorderMode(0)
    style.SetCanvasColor(0)
    #style.SetTopMargin(0.06)
    #style.SetCanvasRightMargin(0.05)
        
    y = HistVec[0].GetYaxis()
    y.SetTitleSize(22)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.15)
    y.SetLabelFont(43)
    y.SetLabelSize(21)
    y.SetTitle("Number of pseudo-experiments")

    HistVec[0].SetMaximum(1.45*HistVec[0].GetBinContent(HistVec[0].GetMaximumBin()))
    HistVec[0].SetLineWidth(2)
    HistVec[0].SetLineStyle(2)
    HistVec[0].SetStats(False)

    x = HistVec[0].GetXaxis()
    x.SetTitleSize(22)
    x.SetTitleFont(43)
    x.SetTitleOffset(1.15)
    x.SetLabelFont(43)
    x.SetLabelSize(21)
    x.SetTitle(XLabel)
    
    HistVec[0].Draw()

    l2 = TLatex()
    l2.SetNDC();
    l2.SetTextFont(72);
    l2.SetTextColor(1);
    l2.SetTextSize(0.04)
    l2.DrawLatex(0.14, 0.85, "ATLAS")
    l2.SetTextFont(42);
    l2.DrawLatex(0.25, 0.85, "Internal")
    l2.DrawLatex(0.14, 0.80, "Simulation")
    
    
    for iEntry in range(1, len(HistVec)):
        HistVec[iEntry].SetLineColor(iEntry)
        HistVec[iEntry].SetLineWidth(2)
        HistVec[iEntry].Draw("SAME")

    leg = TLegend(0.455, 0.72, 0.455+0.23, 0.72+0.17)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.SetTextSize(0.04)
    leg.AddEntry(HistVec[0], NameVec[0], "l")

    for iEntry in range(1, len(HistVec)):
        leg.AddEntry(HistVec[iEntry], NameVec[iEntry], "l")

    leg.Draw("SAME")
    
    c.Print(OutputFile)
        

def GetXLabel(Parameter):

    if Parameter == "mtop":
        return "m_{top} [GeV]"
    if Parameter == "jsf":
        return "JSF"
    if Parameter == "bjsf":
        return "bJSF"
    
    
# this function is used to read the output from the pseudo-experiments, create histograms, and return the information
def EvaluateTrees_TwoSided(FileNameUp, FileNameDown, FileNameNominal, TreeName, Parameter, Systematic, OutputFolder, Flag):

    EdgesUp    = FindEdges(FileNameUp,      TreeName, Parameter)
    EdgesDown  = FindEdges(FileNameDown,    TreeName, Parameter)
    EdgesNom   = FindEdges(FileNameNominal, TreeName, Parameter)

    Minimum    = min(EdgesUp[0], EdgesDown[0], EdgesNom[0])
    Maximum    = max(EdgesUp[1], EdgesDown[1], EdgesNom[1])
    Addition   = math.fabs(Minimum-Maximum)/10

    hist_up    = FillHistos(FileNameUp,      TreeName, Parameter, Minimum-Addition, Maximum+Addition)
    hist_down  = FillHistos(FileNameDown,    TreeName, Parameter, Minimum-Addition, Maximum+Addition)
    hist_nom   = FillHistos(FileNameNominal, TreeName, Parameter, Minimum-Addition, Maximum+Addition)

    ValUp      = hist_up.GetMean()
    ValDown    = hist_down.GetMean()
    ValNom     = hist_nom.GetMean()
    
    OutputFile = OutputFolder+"/PlotParameter_"+Systematic+"_"+Parameter+"_"+Flag+".pdf"

    HistVec    = [hist_up, hist_down, hist_nom]
    NameVec    = [Systematic+"_up", Systematic+"_down", "Nominal"]

    PlotParameters(HistVec, NameVec, OutputFile, GetXLabel(Parameter))

    Uncertainty = CheckNominalPosition(ValUp, ValDown, ValNom)
    
    print ValUp,"    ",ValNom,"    ",ValDown

    return Uncertainty


# this function is used to read the output from the pseudo-experiments, create histograms, and return the information (when only up variation) 
def EvaluateTrees_OneSided(FileNameUp, FileNameNominal, TreeName, Parameter, Systematic, OutputFolder, Flag):

    EdgesUp    = FindEdges(FileNameUp,      TreeName, Parameter)
    EdgesNom   = FindEdges(FileNameNominal, TreeName, Parameter)

    Minimum    = min(EdgesUp[0], EdgesNom[0])
    Maximum    = max(EdgesUp[1], EdgesNom[1])
    Addition   = math.fabs(Minimum-Maximum)/10

    hist_up    = FillHistos(FileNameUp,      TreeName, Parameter, Minimum-Addition, Maximum+Addition)
    hist_nom   = FillHistos(FileNameNominal, TreeName, Parameter, Minimum-Addition, Maximum+Addition)

    ValUp      = hist_up.GetMean()
    ValNom     = hist_nom.GetMean()

    OutputFile = OutputFolder+"/PlotParameter_"+Systematic+"_"+Parameter+"_"+Flag+".pdf"

    HistVec    = [hist_up, hist_nom]
    NameVec    = [Systematic, "Nominal"]

    PlotParameters(HistVec, NameVec, OutputFile, GetXLabel(Parameter))

    #Uncertainty = CheckNominalPosition(ValUp, ValDown, ValNom)

    print ValUp,"  ",ValNom

    Uncertainty = ValUp - ValNom

    return Uncertainty


def ReturnStatUncertainty(Flag, Parameter, PEFolder):
    InputFile = PEFolder+"/nominal_"+Flag+".root"
    fF        = TFile(InputFile, "READ")
    fT        = fF.Get("PETree")
    fT.GetEntry(0)

    if Parameter == "mtop":
        return fT.mtop_e
    if Parameter == "jsf":
        return fT.jsf_e
    if Parameter == "bjsf":
        return fT.bjsf_e


def MakeSystematicTable(Parameter, Dim, OutputFolder, Syst, List):

    TotalUnc = 0.0

    outfile = open(OutputFolder+"/Uncertainties_"+str(Dim)+"D_"+Parameter+"_"+Syst+".tex", "w")
    outfile.write("\\begin{table}   \n")
    outfile.write("\\begin{tabular}{|l|r|}  \n")
    outfile.write("\hline   \n")
    if Parameter == "mtop":
        outfile.write("Uncertainty & $\Delta m_{top}$ [GeV] & \\\\ \n")
    if Parameter == "jsf":
        outfile.write("Uncertainty & $\Delta$ JSF & \\\\ \n")
    if Parameter == "bjsf":
        outfile.write("Uncertainty & $\Delta$ bJSF & \\\\ \n")
    outfile.write("\hline   \n")

    for entry in List:
        Name = entry[0]
        Unc  = entry[1]
        outfile.write(entry[0].replace("_", "\_")+" & "+str(abs(round(entry[1], 2)))+" \\\\ \n")
        TotalUnc += Unc*Unc


    TotalUnc = math.sqrt(TotalUnc)

    outfile.write("\hline \n")
    outfile.write("Total & "+str(round(TotalUnc, 2))+" \\\\ \n")
    outfile.write("\hline \n")
    outfile.write("\end{tabular} \n")
    outfile.write("\end{table}")
    outfile.close()
