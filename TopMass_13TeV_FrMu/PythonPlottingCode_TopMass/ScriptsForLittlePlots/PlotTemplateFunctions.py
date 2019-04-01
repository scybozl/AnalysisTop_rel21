#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
from ROOT import *

import EvalFitFunction

def createRatio(h1, h2, Name1, Name2, ic):
     h3 = h1.Clone("h3")
     h3.SetTitle("")
     if ic == 0:
          h3.SetMinimum(0.75)
          h3.SetMaximum(1.25)
     else:
          h3.SetMinimum(0.85)
          h3.SetMaximum(1.15)
          
     h3.Sumw2()
     h3.SetStats(0)
     h3.Divide(h2)
     h3.SetLineWidth(2)
     
     # Adjust y-axis settings
     y = h3.GetYaxis()
     y.SetNdivisions(505)
     y.SetTitleSize(28)
     y.SetTitleFont(43)
     y.SetTitleOffset(1.55)
     y.SetLabelFont(43)
     y.SetLabelSize(24)

     # Adjust x-axis settings
     x = h3.GetXaxis()
     x.SetTitleSize(28)
     x.SetTitleFont(43)
     x.SetTitleOffset(3.6)
     x.SetLabelFont(43)
     x.SetLabelSize(24)

     return h3


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
    #pad2.SetGridx()
    pad2.Draw()
    
    return c, pad1, pad2
    
    
def ratioplot(histVec, nameVec, outputFile, Var, ic, Dependence):

    ratio = []

    for i in range(1, len(histVec)-3):
         h = createRatio(histVec[i], histVec[0], nameVec[i], nameVec[0], ic)
         ratio.append(h)
         
    c, pad1, pad2 = createCanvasPads()

    pad1.cd()

    pad1.SetTitle("")
    c.SetTitle("")
    
    histVec[0].SetLineColor(kBlue)
    histVec[0].SetLineWidth(2)

    if "mtop" in outputFile or "mw" in outputFile:
         histVec[0].GetYaxis().SetTitle("Normalised events / GeV")
    if "rbq" in outputFile:
         histVec[0].GetYaxis().SetTitle("Normalised events / 0.05")
         

    histVec[1].SetLineColor(kGray+1)
    histVec[1].SetFillStyle(3013)
    histVec[1].SetFillColor(kGray+1)
    histVec[1].SetLineStyle(1)
    histVec[1].SetLineWidth(2)
    
    histVec[2].SetLineColor(kRed)
    histVec[2].SetLineWidth(2)

    histVec[3].SetLineColor(kBlue)
    histVec[3].SetLineStyle(2)
    histVec[4].SetLineColor(kGray+1)
    histVec[4].SetFillColor(kGray+1)
    histVec[4].SetFillStyle(3013)
    histVec[5].SetLineColor(kRed)

    histVec[3].SetNpx(5000)
    histVec[4].SetNpx(5000)
    histVec[5].SetNpx(5000)
         
    y = histVec[2].GetYaxis()
    y.SetTitle("Events")
    y.SetTitleSize(28)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.75)
    y.SetLabelFont(43)
    y.SetLabelSize(24)

    x = histVec[2].GetXaxis()
    x.SetLabelSize(0)
    
    leg = TLegend(0.68, 0.68, 0.68+0.205, 0.885)

    if "JSF" in Dependence:
         leg = TLegend(0.73, 0.68, 0.73+0.195, 0.885)

    for i in range(3, 6):
         LegendLabel = nameVec[i-3]
         if "17" in LegendLabel:
              leg.AddEntry(histVec[i], "m_{top} = "+LegendLabel+" GeV", "F")
         else:
              leg.AddEntry(histVec[i], " "+Dependence+" = "+LegendLabel, "F")

    leg.SetFillColor(0)
    leg.SetLineColor(0)
    leg.SetBorderSize(0)
    leg.SetTextFont(72)
    leg.SetTextSize(0.035)

    y = histVec[2].GetYaxis()
    y.SetTitleSize(26)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.70)
    y.SetLabelFont(43)
    y.SetLabelSize(24)

    Label = "Normalised pdf"

    y.SetTitle(Label)
                                                                   
    nmax_h1 = histVec[0].GetBinContent(histVec[0].GetMaximumBin())
    nmax_h2 = histVec[1].GetBinContent(histVec[1].GetMaximumBin())

    maxi = nmax_h1*1.2

    if(nmax_h2 > nmax_h1):
         maxi = nmax_h2*1.2

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

    for i in range(1, 3):
         histVec[i].Draw("same")

    for i in range(3, 6):
         histVec[i].Draw("csame")


    histVec[0].Draw("SAME")
    histVec[3].Draw("SAME")

    pad1.RedrawAxis()

    pad2.cd()

    lowEdge = histVec[0].GetBinLowEdge(1)
    upEdge  = histVec[0].GetBinLowEdge(histVec[0].GetNbinsX()) + histVec[0].GetBinWidth(1)
    
    ratio_func  = TH1D("ratio_func",  "", 1000, lowEdge, upEdge)
    ratio_func2 = TH1D("ratio_func2", "", 1000, lowEdge, upEdge)
    
    for i in range(1, 1001):
         center = ratio_func.GetBinLowEdge(i)
         val1   = histVec[3].Eval(center)
         val2   = histVec[4].Eval(center)
         val3   = histVec[5].Eval(center)
         ratio1 = val1/val2
         ratio2 = val3/val2
         ratio_func.SetBinContent(i,  ratio1)
         ratio_func2.SetBinContent(i, ratio2)

    
    y = ratio_func.GetYaxis()
    y.SetNdivisions(505)
    y.SetTitleSize(28)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.65)
    y.SetLabelFont(43)
    y.SetLabelSize(22)

    x = ratio_func.GetXaxis()
    x.SetTitleSize(28)
    x.SetTitleFont(43)
    x.SetTitleOffset(2.05)
    x.SetLabelFont(43)
    x.SetLabelSize(24)

    
    ratio_func.Draw("C")
    ratio_func.GetXaxis().SetTitle(Var)
    ratio_func.GetYaxis().SetTitle("Ratio")
    ratio_func.GetXaxis().SetTitleOffset(4.25)
    ratio_func.GetYaxis().CenterTitle()
    ratio_func.SetMinimum(0.75)
    ratio_func.SetMaximum(1.25)
    ratio_func.SetLineColor(kBlue)
    ratio_func.SetLineStyle(2)
    ratio_func2.SetLineColor(kRed)
    ratio_func.SetLineWidth(2)
    ratio_func2.SetLineWidth(2)
    ratio_func2.Draw("CSAME")


    norm1 = TF1("fa1","1", 0, 210);
    norm1.SetLineColor(kBlack);
    norm1.SetLineStyle(1);
    norm1.SetLineWidth(1);
    norm1.Draw("SAME");
    
    c.SetTitle("")
    c.Print(outputFile)
    
    


if __name__ == "__main__":
    print sys.argv

    InputFolder  = sys.argv[1]
    HistoName    = sys.argv[2]
    OutputFolder = sys.argv[3]

    InFileHist1  = sys.argv[4]
    InFileHist2  = sys.argv[5]
    InFileHist3  = sys.argv[6]

    Dependence   = sys.argv[7]

    fF1 = TFile(InFileHist1, "READ")
    fH1 = fF1.Get(HistoName)
    fH1.Scale(1.0/fH1.Integral())

    fF2 = TFile(InFileHist2, "READ")
    fH2 = fF2.Get(HistoName)
    fH2.Scale(1.0/fH2.Integral())

    fF3 = TFile(InFileHist3, "READ")
    fH3 = fF3.Get(HistoName)
    fH3.Scale(1.0/fH3.Integral())

    outputFile = OutputFolder+"/Template_"
    BinWidth   = 1.0
    

    if "mtop" in HistoName:
         Var = "m_{top}^{reco} [GeV]"
         ic  = 0
         outputFile = outputFile+"mtop"
    if "mw" in HistoName:
         Var = "m_{W}^{reco} [GeV]"
         ic  = 1
         outputFile = outputFile+"mw"
    if "rbq" in HistoName:
         Var = "R_{bq}^{reco}  "
         ic  = 2
         outputFile = outputFile+"rbq"
         BinWidth = 0.05

    if Dependence == "mtop":
         func_mtop_mtop1 = TF1()
         func_mtop_mtop1 = EvalFitFunction.EvalFitFunction(171.0, 1.0, 1.0, ic, BinWidth, InputFolder)
         func_mtop_mtop2 = TF1()
         func_mtop_mtop2 = EvalFitFunction.EvalFitFunction(172.5, 1.0, 1.0, ic, BinWidth, InputFolder)
         func_mtop_mtop3 = TF1()
         func_mtop_mtop3 = EvalFitFunction.EvalFitFunction(174.0, 1.0, 1.0, ic, BinWidth, InputFolder)
         
         Vec1 = [fH1, fH2, fH3, func_mtop_mtop1, func_mtop_mtop2, func_mtop_mtop3]
         Vec2 = ["171.0", "172.5", "174.0"]
         ratioplot(Vec1, Vec2, outputFile+"_mtop_LJ.pdf", Var, 0, "mtop")


    if Dependence == "JSF":
         func_mtop_jsf1  = TF1()
         func_mtop_jsf1  = EvalFitFunction.EvalFitFunction(172.5, 0.98, 1.0, ic, BinWidth, InputFolder)
         func_mtop_jsf2  = TF1()
         func_mtop_jsf2  = EvalFitFunction.EvalFitFunction(172.5, 1.00, 1.0, ic, BinWidth, InputFolder)
         func_mtop_jsf3  = TF1()
         func_mtop_jsf3  = EvalFitFunction.EvalFitFunction(172.5, 1.02, 1.0, ic, BinWidth, InputFolder)

         Vec1 = [fH1, fH2, fH3, func_mtop_jsf1, func_mtop_jsf2, func_mtop_jsf3]
         Vec2 = ["0.98", "1.00", "1.02"]
         ratioplot(Vec1, Vec2, outputFile+"_JSF_LJ.pdf", Var, 0, "JSF")
    
    if Dependence == "bJSF":
         func_mtop_bjsf1 = TF1()
         func_mtop_bjsf1 = EvalFitFunction.EvalFitFunction(172.5, 1.0, 0.98, ic, BinWidth, InputFolder)
         func_mtop_bjsf2 = TF1()
         func_mtop_bjsf2 = EvalFitFunction.EvalFitFunction(172.5, 1.0, 1.00, ic, BinWidth, InputFolder)
         func_mtop_bjsf3 = TF1()
         func_mtop_bjsf3 = EvalFitFunction.EvalFitFunction(172.5, 1.0, 1.02, ic, BinWidth, InputFolder)

         Vec1 = [fH1, fH2, fH3, func_mtop_bjsf1, func_mtop_bjsf2, func_mtop_bjsf3]
         Vec2 = ["0.98", "1.00", "1.02"]
         ratioplot(Vec1, Vec2, outputFile+"_bJSF_LJ.pdf", Var, 0, "bJSF")


