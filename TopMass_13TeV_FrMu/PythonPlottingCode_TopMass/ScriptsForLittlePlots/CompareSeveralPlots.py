#! /usr/bin/python                                                                                                                                                                   

import os,sys
import glob
from ROOT import *
from copy import copy
import gc

def createCanvasPads():
    c = TCanvas("c", "canvas", 800, 800)
    # Upper histogram plot is pad1                                                                                                                                                                         
    
    pad1 = TPad("pad1", "pad1", 0, 0.30, 1, 1.0)
    pad1.SetBottomMargin(0.02)  # joins upper and lower plot                                                                                                                                               
    pad1.SetLeftMargin(0.12)
    pad1.SetRightMargin(0.06)
    pad1.SetTicks(1,1)
    #pad1.SetGridx()                                                                                                                                                                                      
    
    pad1.Draw()
    # Lower ratio plot is pad2                                                                                                                                                                            
    c.cd()  # returns to main canvas before defining pad2                                                                                                                                                 
    pad2 = TPad("pad2", "pad2", 0, 0.04, 1, 0.295)
    pad2.SetTopMargin(0)  # joins upper and lower plot                                                                                                                                                    
    pad2.SetBottomMargin(0.325)
    pad2.SetLeftMargin(0.12)
    pad2.SetRightMargin(0.06)
    pad2.SetTicks(1,1)
    pad2.Draw()

    return c, pad1, pad2

def createRatio(h1, h2, Name1, Name2):
    h3 = h1.Clone("h3")
    h3.SetTitle("")
    
    h3.SetMinimum(0.75)
    h3.SetMaximum(1.25)
    
    h3.Sumw2()
    h3.SetStats(0)
    h3.Divide(h2)
    h3.SetLineWidth(2)
    
    if "mu" in Name2:
        Name2 = Name2.replace("mu", "#mu")
         
    y = h3.GetYaxis()
    y.CenterTitle()
    y.SetTitle("Var./"+Name2+" ") #+Name2)                                                                                                                                                                 
    y.SetNdivisions(505)
    y.SetTitleSize(26)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.55)
    y.SetLabelFont(43)
    y.SetLabelSize(24)
    
    x = h3.GetXaxis()
    x.SetTitleSize(26)
    x.SetTitleFont(43)
    x.SetTitleOffset(3.9)
    x.SetLabelFont(43)
    x.SetLabelSize(24)
    
    return copy(h3)

    
def ratioplot(histVec, nameVec, outputFile, HistoTitle):
    ratio = []

    for i in range(1, len(histVec)):
         #print histVec[i].Integral()
        print "Hier "
        h = createRatio(histVec[i], histVec[0], nameVec[i], nameVec[0])
        ratio.append(copy(h))
        del h

    c, pad1, pad2 = createCanvasPads()

    # draw everything
    pad1.cd()

    histVec[0].SetLineColor(kMagenta)
    histVec[1].SetLineColor(kBlue)
    histVec[1].SetLineWidth(2)
    histVec[0].SetLineWidth(2)
    
    if len(histVec) > 2:
         histVec[2].SetLineColor(kGreen+2)
         histVec[2].SetLineWidth(2)
    if len(histVec) > 3:
         histVec[3].SetLineColor(kOrange)
         histVec[3].SetLineWidth(2)
    #if len(histVec) > 4:
    #     histVec[4].SetLineColor(kBlue)
    #     histVec[4].SetLineWidth(2)
    #if len(histVec) > 5:
    #     histVec[5].SetLineColor(kGreen+2)
    #     histVec[5].SetLineWidth(2)
         
    y = histVec[0].GetYaxis()
    y.SetTitle("Events")
    y.SetTitleSize(28)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.75)
    y.SetLabelFont(43)
    y.SetLabelSize(24)

    leg = TLegend(0.715, 0.75, 0.735+0.145, 0.865)

    for i in range(0, len(histVec)):
         leg.AddEntry(histVec[i], nameVec[i].replace("mu", "#mu"), "f")
  
    leg.SetFillColor(0)
    leg.SetLineColor(0)
    leg.SetBorderSize(0)
    leg.SetTextFont(72)
    leg.SetTextSize(0.044)

    y = histVec[0].GetYaxis()
    y.SetTitleSize(26)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.65)
    y.SetLabelFont(43)
    y.SetLabelSize(24)


    Label = "Normalised events"

    #if "jets" in xTitle and not ("Delta" in xTitle or "Number" in xTitle):
    #     Label = "Entries"
    
    #if "jetPt" in Var or "jetEta" in Var:
    #     Label = "Normalised entries"
         
    BinWidth = histVec[0].GetBinWidth(1)
         
    if "GeV" in HistoTitle:
         if BinWidth == 1:
              y.SetTitle(Label+" / GeV ")
         else:
              y.SetTitle(Label+" / "+str(BinWidth)+" GeV ")
    else:
         if BinWidth == 1:
              y.SetTitle(Label+" ")
         else:
              y.SetTitle(Label+" / "+str(BinWidth)+" ")
                                                                   
    
    nmax_h1 = histVec[0].GetBinContent(histVec[0].GetMaximumBin())
    nmax_h2 = histVec[1].GetBinContent(histVec[1].GetMaximumBin())

    maxi = nmax_h1*1.25

    if(nmax_h2 > nmax_h1):
         maxi = nmax_h2*1.25
    
    histVec[0].SetMaximum(maxi)
    histVec[0].SetMinimum(0.0)
    histVec[0].GetXaxis().SetLabelSize(0)
    histVec[0].GetXaxis().SetTitleSize(0)
    histVec[0].GetYaxis().SetTitleSize(27)
    histVec[0].GetYaxis().SetTitleFont(43)
    histVec[0].GetYaxis().SetTitleOffset(1.75)
    histVec[0].GetYaxis().SetLabelFont(43)
    histVec[0].GetYaxis().SetLabelSize(22)
    histVec[0].SetTitle("")
    histVec[0].Draw()

    gStyle.SetOptStat(0)

    leg.Draw("SAME")


    l2 = TLatex()
    l2.SetNDC();
    l2.SetTextFont(72);
    l2.SetTextColor(1);
    l2.DrawLatex(0.155, 0.835, "ATLAS")

    l3 = TLatex()
    l3.SetNDC();
    l3.SetTextFont(42);
    l3.SetTextColor(1);
    l3.DrawLatex(0.275, 0.835, "Simulation")
    l3.DrawLatex(0.155, 0.785, "Internal, #sqrt{s}=13 TeV")
                                            
    
    for i in range(1, len(histVec)):
         histVec[i].Draw("same")

    pad2.cd()

    #histVec[0].SetLineColor(kMagenta)
    ratio[0].SetLineColor(kBlue)

    if len(ratio) > 1:
         ratio[1].SetLineColor(kGreen+2)
    if len(ratio) > 2:
         ratio[2].SetLineColor(kOrange)

    ratio[0].GetXaxis().SetTitle(HistoTitle)
    ratio[0].Draw()

    for i in range(1, len(ratio)):
         ratio[i].Draw("same")

    #ratio_func = TF1("new", "dMCpdf_0PH/dMCpdf_0nom", 125.0, 200.0)

    norm1 = TF1("fa1","1", -10, 700);
    norm1.SetLineColor(kBlack);
    norm1.SetLineStyle(1);
    norm1.SetLineWidth(2);
    norm1.Draw("Same");

    lowEdge = histVec[0].GetBinLowEdge(1)
    upEdge  = histVec[0].GetBinLowEdge(histVec[0].GetNbinsX()) + histVec[0].GetBinWidth(1)

    #print lowEdge,"  ",upEdge

    #for i in range(1, ratio[0].GetNbinsX()):
    #     center = ratio[0].GetBinCenter(i)
    #     hist   = histVec[0].GetBinContent(i)
    #     func   = histVec[3].Eval(center)
    #     print center,"  ",histVec[0].GetBinContent(i),"   ",histVec[3].Eval(center),"  ",hist/func
    
    #ratio_func  = TH1D("ratio_func",  "", 10000, lowEdge, upEdge)
    #ratio_func2 = TH1D("ratio_func2", "", 10000, lowEdge, upEdge)
    
    #for i in range(1, 10001):
    #     center = ratio_func.GetBinCenter(i)
    #     val1   = histVec[3].Eval(center)
    #     val2   = histVec[4].Eval(center)
    #     ratio2 = val2/val1
    #     print "Ratio 1 =   ",i,"  ",center,"  ",ratio2,"  ",val1,"  ",val2
    #     ratio_func.SetBinContent(i, ratio2)
    #     val12   = histVec[3].Eval(center)
    #     val22   = histVec[5].Eval(center)
    #     ratio22 = val22/val12
    #     print "Ratio 2 =   ",i,"  ",ratio22,"  ",val12,"  ",val22
    #     ratio_func2.SetBinContent(i, ratio22)
                                                               
         
    #ratio_func.SetLineColor(kBlue)
    #ratio_func.SetLineWidth(2)
    #ratio_func.Draw("CSAME")

    #ratio_func2.SetLineColor(kGreen+2)
    #ratio_func2.SetLineWidth(2)
    #ratio_func2.Draw("CSAME")

    #extPDF_1 = histVec[3]
    #extPDF_2 = histVec[4]

    #extSumPDF.SetLineColor(kRed)

    #for i in range(1, 10001):
    #     print extSumPDF.Eval(ratio_func2.GetBinCenter(i))
    
    #help = TF1("pdf", extSumPDF, lowEdge, upEdge)
    #help.SetLineColor(kRed)
    #help.Draw("SAME")

    #for i in range(1, 10001):
    #     center = ratio_func2.GetBinCenter(i)
    #     print help.Eval(center)
    
    c.Print(outputFile)
    
    


def MakeComparisonPlots(OutputFile, HistoName, HistoTitle, InputFile1, Name1, InputFile2, Name2, InputFile3="", Name3="", InputFile4="", Name4=""):
     
    NrHistos = 2

    if InputFile3 == "":
        InputFile3 = InputFile1
        Name3      = Name1
    else:
        NrHistos = 3
          
    if InputFile4 == "":
        InputFile4 = InputFile1
        Name4      = Name1
    else:
        NrHistos = 4


    fF1 = TFile(InputFile1, "READ")
    fF2 = TFile(InputFile2, "READ")
    fF3 = TFile(InputFile3, "READ")
    fF4 = TFile(InputFile4, "READ")
    
    fH1 = fF1.Get(HistoName)
    fH2 = fF2.Get(HistoName)
    fH3 = fF3.Get(HistoName)
    fH4 = fF4.Get(HistoName)
    
    if fH1.Integral() == 0:
        return
    if fH2.Integral() == 0:
        return
    if fH3.Integral() == 0:
        return
    if fH4.Integral() == 0:
        return
    
     
    fH1.Scale(1.0/fH1.Integral())
    fH2.Scale(1.0/fH2.Integral())
    fH3.Scale(1.0/fH3.Integral())
    fH4.Scale(1.0/fH4.Integral())
    
    Vec1 = []
    Vec1.append(fH1)
    Vec1.append(fH2)
    
    Vec2 = []
    Vec2.append(Name1)
    Vec2.append(Name2)
    
    size = len(sys.argv)
     
    print Name3,"  ",Name4
     
    if NrHistos == 3:
        Vec1.append(fH3)
        Vec2.append(Name3)
        print fH3.Integral()
          

    if NrHistos == 4:
        Vec1.append(fH3)
        Vec1.append(fH4)
        Vec2.append(Name3)
        Vec2.append(Name4)
        
    print len(Vec1),"   ",InputFile3,"  ",InputFile4
    
    ratioplot(Vec1, Vec2, OutputFile, HistoTitle)
    
    #gc.collect()
