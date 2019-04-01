#! /usr/bin/python
 
import os,sys
import glob
import array
from ROOT import *
import math
from copy import copy
from MassSuperScriptPlots import *
from VariableList import *

doNormalised = False
doOfficial   = False

DataPeriod   = str(sys.argv[1])  #"2017" # 2017, 2015_16, Combined
ChannelOld   = sys.argv[2] #"boosted"  # "boosted" or "resolved"
NomFolder    = sys.argv[3] #"/work/ws/atlas/ak1148-ak1148/TTH/Ntuples_21.2.16.1/Histograms_Nominal_Merged/"
PlotFolder   = sys.argv[4] #"ControlPlots_"+DataPeriod+"_Absolute/"
ReleaseFlag  = sys.argv[5]

#Channel = ""

if doNormalised:
    PlotFolder = PlotFolder.replace("_Absolute/", "_Normalised/")

os.system("mkdir -p "+PlotFolder)
                        
def main():

    Flag = "MC15"

    if "Rel21" in ReleaseFlag:
        Flag = "MC16"

    CampaignFlag = "MC16a"
    if DataPeriod == "2017":
        CampaignFlag = "MC16c"

    VariableFlag = ReturnVariableFlag(ChannelOld, CampaignFlag) # campaign does not matter here
    Channel      = ReturnChannelLabel(ChannelOld, CampaignFlag)

    print Channel

    #print VariableFlag
    
    VariableList  = ReturnVariableListSimple(Flag, VariableFlag)

    #if "KLF" in PlotFolder:
    #    VariableList  = ReturnVariablesKLFPerf()

    for Var in VariableList:
        varName   = Var[0]
        histName  = Var[5]
        xTitle    = Var[6]

        DataHist  = ""

        if DataPeriod == "2015_16":
            DataHist  = ReturnHistogram(NomFolder+"/Merge_data2015_16.root",    histName)
            #print NomFolder+"/Merge_data2015_16.root"
        elif DataPeriod == "2017":
            DataHist  = ReturnHistogram(NomFolder+"/Merge_data2017.root",    histName)
        else:
            DataHist  = ReturnHistogram(NomFolder+"/Merge_data2015_16_17.root",    histName)


        #print histName
        # now read in nominal and systematic samples for each variation, hand over a flag if its ttbar only var
        HistNominal    = GetAllHistograms(NomFolder,  "",  histName, "None", DataPeriod, Flag)

        if HistNominal[0][0].Integral() <= 0.0:
            continue

        HistNominalSum = AddAllHistograms(HistNominal)

        #print DataPeriod

        #print histName

        # then here I need to add code that calculates the unc and puts it on top of the HistNominalSumError
        ratioplot(DataHist, HistNominalSum, HistNominal, "Data", "MC", histName, xTitle, Channel)



def AddAllHistograms(HistVec):
    
    #print len(HistVec)
    #print len(HistVec[0])

    #print HistVec[0][0].Integral()

    Histogram = HistVec[0][0].Clone()

    for i in range(1, len(HistVec)): # last entry is ttH
        Histogram += HistVec[i][0]
    
    return Histogram


def GetAllHistograms(FolderName, SystFlag, HistoName, ExtraFlag, DataPeriod, RelFlag):
    
    Flag = ""
    if DataPeriod == "2015_16":
        Flag = "_MC16a"
        if "MC15" in RelFlag:
            Flag = "_MC15"
    if DataPeriod == "2017":
        Flag = "_MC16c"

    #TTbar     = ReturnHistogram(FolderName+"/Merge_ttbar"+Flag+"_PH7_AF2.root",        HistoName)
    TTbar     = ReturnHistogram(FolderName+"/Merge_ttbar_PP6"+Flag+".root",        HistoName)
    SingleTop = ReturnHistogram(FolderName+"/Merge_SingleTop"+Flag+".root",    HistoName)
    Wjets     = ReturnHistogram(FolderName+"/Merge_Wjets"+Flag+".root",        HistoName)
    Zjets     = ReturnHistogram(FolderName+"/Merge_Zjets"+Flag+".root",        HistoName)
    Diboson   = ReturnHistogram(FolderName+"/Merge_Diboson"+Flag+".root",      HistoName)
    TTV       = ReturnHistogram(FolderName+"/Merge_TTV"+Flag+".root",          HistoName)
 
    #print FolderName+"/Merge_ttbar"+Flag+".root"

    # Histogram, label, colour
    Vec = []
    Vec.append([TTbar,     "t#bar{t}",       0])
    Vec.append([SingleTop, "Single top",    62])
    Vec.append([Wjets,     "W+jets",        95])
    Vec.append([Zjets,     "Z+jets",        92])
    Vec.append([Diboson,   "Diboson",        5])
    Vec.append([TTV,       "t#bar{t}+V",    kPink+7])

    #Vec.append([QCD,       "NP/fake leptons",             619])

    return Vec
    

def ReturnHistogram(FileName, HistoName):
    fF = TFile(FileName, "READ")
    fH = fF.Get(HistoName)
    return copy(fH)






def createRatio(h1, h2, Name1, Name2):
     h3 = h1.Clone("h3")
     h3.SetLineColor(kBlack)
     h3.SetMarkerStyle(20)
     h3.SetTitle("")
     h3.SetMinimum(0.70)
     h3.SetMaximum(1.30)

     h4  = h2.Clone("h4")
     h22 = h2.Clone("h22")
     h4.SetTitle("")
     h4.SetMinimum(0.70)
     h4.SetMaximum(1.30)

     gStyle.SetTickLength(0.07)
     
     h4.Divide(h22)

     for i in range(1, h22.GetNbinsX()+1):
         h22.SetBinError(i, 0)

     for i in range(1, h22.GetNbinsX()+1):
         if h3.GetBinContent(i) == 0:
             h4.SetBinError(i, 0)
             h4.SetBinContent(i, 0)

     h3.SetStats(0)
     h3.Divide(h22)
     
     # Adjust y-axis settings
     y = h4.GetYaxis()
     y.CenterTitle()
     y.SetTitle(Name1+"/"+Name2)
     y.SetNdivisions(505)
     y.SetTitleSize(22)
     y.SetTitleFont(43)
     y.SetTitleOffset(1.65)
     y.SetLabelFont(43)
     y.SetLabelSize(22)

     # Adjust x-axis settings
     x = h4.GetXaxis()
     x.SetTitleSize(24)
     x.SetTitleFont(43)
     x.SetTitleOffset(4.1)
     x.SetLabelFont(43)
     x.SetLabelSize(22)
     
     return h3,h4


def createCanvasPads(histName):
    c = TCanvas(histName, histName, 10, 10, 700, 600)
    # Upper histogram plot is pad1
    pad1 = TPad("pad1", "pad1", 0, 0.26, 1, 1.0)
    pad1.SetTopMargin(0.05)
    pad1.SetRightMargin(0.05)
    pad1.SetLeftMargin(0.14)
    pad1.SetBottomMargin(0.02)  # joins upper and lower plot
    pad1.SetTicks(1,1)
    # Lower ratio plot is pad2
    c.cd()  # returns to main canvas before defining pad2
    pad2 = TPad("pad2", "pad2", 0, 0.02, 1, 0.27)
    pad2.SetTopMargin(0)  # joins upper and lower plot
    pad2.SetBottomMargin(0.38)
    pad2.SetRightMargin(0.05)
    pad2.SetLeftMargin(0.14)
    pad2.SetGridy()

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
    #style.SetPadTickX(1)
    #style.SetPadTickY(1)
    
    pad1.Draw()
    pad2.Draw()
    
    return c, pad1, pad2
    
    
def GetUncertainty(histo):
    totalUnc = 0

    for i in range(1, histo.GetNbinsX()+1):
        binErr = histo.GetBinError(i)
        totalUnc += binErr #*binErr

    return totalUnc


def MakeLatexTable(Folder, h1, h2, HistVec):
    bkgHisto = HistVec[2][0].Clone()
    bkgHisto.Add(HistVec[3][0])
    bkgHisto.Add(HistVec[4][0])
    bkgHisto.Add(HistVec[5][0])
    #bkgHisto.Add(HistVec[5][0])

    bkgFraction    = bkgHisto.Integral()/(h2.Integral())
    bkgUnc         = GetUncertainty(bkgHisto)
    totUnc         = GetUncertainty(h2)
    bkgFractionUnc = bkgFraction*math.sqrt(bkgUnc*bkgUnc/bkgHisto.Integral()/bkgHisto.Integral() + totUnc*totUnc/h2.Integral()/h2.Integral()) 

    dataMC         = h1.Integral()/h2.Integral()
    dataUnc        = GetUncertainty(h1)

    #print h1.Integral(),"  ",h2.Integral()

    dataMCUnc      = dataMC*math.sqrt(dataUnc*dataUnc/h1.Integral()/h1.Integral() + totUnc*totUnc/h2.Integral()/h2.Integral())
    
    outfile = open(Folder+"/EventYield.tex", "w")
    outfile.write("\\begin{table}   \n")
    outfile.write("\\begin{tabular}{|l|rr|}  \n")
    outfile.write("\hline   \n")
    outfile.write("Data & "+(str(h1.Integral())).replace(".0", "")+" & \\\\ \n")
    outfile.write("\hline   \n")
    outfile.write("$t\\bar{t}$ signal & "+str(round(HistVec[0][0].Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(HistVec[0][0]), 1))+"  \\\\ \n")
    outfile.write("Single-top-quark signal & "+str(round(HistVec[1][0].Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(HistVec[1][0]), 1))+"  \\\\ \n")
    outfile.write("\hline   \n")
    #print "QCD unc"
    #outfile.write("NP/fake leptons (data) & "+str(round(HistVec[5][0].Integral(), 1))+" $\pm$ "+str(round(GetUncertainty(HistVec[5][0]), 3))+"  \\\\ \n")
    #outfile.write("NP/fake leptons (data) & "+str(round(HistVec[5][0].Integral(), 1))+" $\pm$ "+str(round(HistVec[5][0].Integral(), 3))+"  \\\\ \n")
    #print "Wjets"
    outfile.write("$W$+jets & "+str(round(HistVec[2][0].Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(HistVec[2][0]), 1))+"  \\\\ \n")
    #print "Zjets"
    outfile.write("$Z$+jets & "+str(round(HistVec[3][0].Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(HistVec[3][0]), 1))+"  \\\\ \n")
    outfile.write("Diboson & "+str(round(HistVec[4][0].Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(HistVec[4][0]), 1))+"  \\\\ \n")
    outfile.write("$t\\bar{t}+V$ & "+str(round(HistVec[5][0].Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(HistVec[5][0]), 1))+"  \\\\ \n")
    outfile.write("\hline  \n")
    outfile.write("Signal+background & "+str(round(h2.Integral(), 1))+" $\pm$& "+str(round(GetUncertainty(h2), 1))+"  \\\\ \n")
    outfile.write("\hline  \n")
    outfile.write("Expected background fraction & "+str(round(bkgFraction,3))+" $\pm$& "+str(round(bkgFractionUnc, 3))+" \\\\ \n")
    outfile.write("Data/(Signal + background) & "+str(round(dataMC, 3))+" $\pm$& "+str(round(dataMCUnc, 3))+" \\\\ \n ")
    outfile.write("\hline  \n")
    outfile.write("\end{tabular} \n")
    outfile.write("\end{table}")
    outfile.close()
        

def ratioplot(h1, h2, HistVec, Name1, Name2, histName, xTitle, Channel):

    if "jet_n" in histName:
        MakeLatexTable(PlotFolder, h1, h2, HistVec)

    #print h1.Integral()
    #print h2.Integral()

    if h1.Integral() == 0 or h2.Integral() == 0:
        scale = 0
    else:
        scale = h1.Integral()/h2.Integral()
        
    if doNormalised:
        h2.Scale(scale)

        
    h1.SetLineColor(kBlack)
    h2.SetLineColor(kBlack)

    outputFile     = PlotFolder+"/"+histName.replace("h_", "")+"_"+DataPeriod+".pdf"
    outputFileRoot = PlotFolder+"/"+histName.replace("h_", "")+"_"+DataPeriod+".root"
     
    h3, h4 = createRatio(h1, h2, Name1, Name2)
    c, pad1, pad2 = createCanvasPads(histName)

    pad1.cd()

    #if not "Number" in xTitle:
    #    pad1.SetLogy()
    
    y = h2.GetYaxis()

    Label = "Events"

    if "jets" in xTitle and not ("Delta" in xTitle or "Number" in xTitle):
        Label = "Entries"

    if "jetPt" in histName or "jetEta" in histName:
        Label = "Events"
        
    BinWidth = h1.GetBinWidth(1)
        
    if "GeV" in xTitle:
        if BinWidth == 1:
            y.SetTitle(Label+" / GeV")
        else:
            y.SetTitle(Label+" / "+str(BinWidth).replace(".0", "")+" GeV")
    else:
        if BinWidth == 1:
            y.SetTitle(Label)
        else:
            y.SetTitle(Label+" / "+str(BinWidth).replace(".0", ""))


    #y.SetNdivisions(505)
    y.SetTitleSize(22)
    y.SetTitleFont(43)
    y.SetTitleOffset(1.75)
    y.SetLabelFont(43)
    y.SetLabelSize(21)
    
    testHist = HistVec[0][0].Clone()

    for iEntry in range(1, len(HistVec)):
        testHist.Add(HistVec[iEntry][0])
    
    stack0 = THStack("stack0", "");

    for entry in reversed(HistVec):

        if doNormalised:
            #fraction = entry[0].Integral()/testHist.Integral()
            fraction = scale
            #print fraction
            entry[0].Scale(scale)
            #entry[0].Scale(fraction/entry[0].Integral())
        
        for i in range(1, entry[0].GetNbinsX()+1):
            entry[0].SetBinError(i, 0)

        entry[0].SetFillColor(entry[2])
        entry[0].SetMarkerStyle(21)

        if entry[2] == 0:
            entry[0].SetLineColor(kBlack)
        else:
            entry[0].SetLineColor(entry[2])
        stack0.Add(entry[0])



    leg1 = TLegend(0.20, 0.71, 0.20+0.23, 0.72+0.20)
    leg1.SetFillColor(0)
    leg1.SetFillStyle(0)
    leg1.SetBorderSize(0)
    leg1.SetTextSize(0.05)
    leg1.AddEntry(h1, "Data", "p")
    
    counter_leg = 0

    for entry in HistVec:
        counter_leg += 1
        if counter_leg > 3:
            continue
        leg1.AddEntry(entry[0], entry[1], "f")

    leg2 = TLegend(0.44, 0.71, 0.44+0.23, 0.72+0.20)
    leg2.SetFillColor(0)
    leg2.SetFillStyle(0)
    leg2.SetBorderSize(0)
    leg2.SetTextSize(0.05)

    counter_leg = 0

    for entry in HistVec:
        counter_leg += 1
        if counter_leg <= 3:
            continue
        if counter_leg > 6:
            continue
        leg2.AddEntry(entry[0], entry[1], "f")

    leg2.AddEntry(h2, "Unc.", "f")

    nmax_h1 = h1.GetBinContent(h1.GetMaximumBin())
    nmax_h2 = h2.GetBinContent(h2.GetMaximumBin())

    maxi = nmax_h1*1.55

    if(nmax_h2 > nmax_h1):
        maxi = nmax_h2*1.55

    if "phi" in xTitle or "eta" in xTitle:
        maxi = nmax_h1*1.75

    h2.SetMaximum(maxi)
    h2.SetMinimum(0.0001)
        
    x = h2.GetXaxis()
    x.SetLabelSize(0)
    x.SetTitleSize(0)

    gStyle.SetHatchesSpacing(1.2)
    gStyle.SetHatchesLineWidth(1)
    
    # now check for blinding, the last entry in the vector is TTH
    iTTH    = len(HistVec)-1
    TTHHist = HistVec[iTTH][0]

    Blind   = TTHHist.Clone()

    for i in range(1, TTHHist.GetNbinsX()+1):
        ratio = 0.0
        if h2.GetBinContent(i) > 0:
            ratio = TTHHist.GetBinContent(i)/h2.GetBinContent(i)
        if ratio > 0.05:
            #print "blinding bin i = ",i,"  ratio = ",ratio
            h1.SetBinContent(i, 0)
            Blind.SetBinContent(i, h2.GetBinContent(i)*1000.0)
        else:
            Blind.SetBinContent(i, 0)

    h2.SetFillStyle(3244)
    h2.SetFillColor(kBlack)
    h2.Draw()
    
    l = TLatex()
    l.SetNDC()
    l.SetTextFont(42)
    l.SetTextColor(1)
    l.SetTextSize(0.055)
    
    if DataPeriod == "2015_16":
        l.DrawLatex(0.655, 0.805, "#sqrt{s}=13 TeV, 36.1 fb^{-1}")
    elif DataPeriod == "2017":
        l.DrawLatex(0.655, 0.805, "#sqrt{s}=13 TeV, 43.8 fb^{-1}")
    else:
        l.DrawLatex(0.655, 0.805, "#sqrt{s}=13 TeV, 80 fb^{-1}")

    if Channel == "lepjets":
        l.DrawLatex(0.675, 0.74, "-- lepton + jets --")
    else:
        print Channel
        l.DrawLatex(0.675, 0.74, "--"+Channel+"--")

    l2 = TLatex()
    l2.SetNDC();
    l2.SetTextFont(72);
    l2.SetTextColor(1);
    l2.SetTextSize(0.055)
    l2.DrawLatex(0.655, 0.875, "ATLAS")

    if doOfficial:
        l.DrawLatex(0.77, 0.875, "Preliminary")
    else:
        l.DrawLatex(0.77, 0.875, "Internal")
    
    h1.SetMarkerSize(1.2)
    h1.SetMarkerStyle(20)

    upperEdge = BinWidth*h2.GetNbinsX()+h2.GetBinLowEdge(1)
    
    #if "Met" in histName:
    #    h2.GetXaxis().SetRangeUser(20.0, upperEdge)
    #    h1.GetXaxis().SetRangeUser(20.0, upperEdge)

    stack0.Draw("SAME")
    h2.Draw("E2same")
    h1.Draw("SAME")
    Blind.Draw("SAME")

    gStyle.SetOptStat(0)

    leg1.Draw("SAME")
    leg2.Draw("SAME")

    pad2.cd()
        
    h4.GetXaxis().SetTitle(xTitle)
    h4.SetFillStyle(3244)
    h4.SetFillColor(kBlack)
    h4.GetYaxis().SetNdivisions(5)
    h4.Draw("E2")

    if "jet_n" in outputFile and not "bjet_n" in outputFile:
        h4.GetXaxis().SetNdivisions(5)
        h4.GetXaxis().SetBinLabel(1,"2")
        h4.GetXaxis().SetBinLabel(2,"3")
        h4.GetXaxis().SetBinLabel(3,"4")
        h4.GetXaxis().SetBinLabel(4,"5")
        h4.GetXaxis().SetBinLabel(5,"6")
        h4.GetXaxis().SetBinLabel(6,"7")
        h4.GetXaxis().SetBinLabel(7,"#geq 8")
        h4.GetXaxis().SetLabelOffset(0.012)
        
    if "btag_n" in outputFile:
        h4.GetXaxis().SetNdivisions(5)
        h4.GetXaxis().SetBinLabel(1,"1")
        h4.GetXaxis().SetBinLabel(2,"2")
        h4.GetXaxis().SetBinLabel(3,"3")
        h4.GetXaxis().SetBinLabel(4,"#geq 4")
        h4.GetXaxis().SetLabelOffset(0.012)


    h3.Draw("PSAME")

    c.Print(outputFile)
    c.Print(outputFile.replace(".pdf", ".png"))

    output = TFile(outputFileRoot, "RECREATE")

    h2.Write("hist_MC")
    h1.Write("hist_Data")
    h3.Write("hist_Ratio")

    output.Close()

    pad1.Delete()
    pad2.Delete()
    c.Delete()


if __name__ == '__main__':
    gROOT.SetBatch(True)
    gROOT.ProcessLine( "gErrorIgnoreLevel = 2001;")
    main()
    #print "Hier!"
   
