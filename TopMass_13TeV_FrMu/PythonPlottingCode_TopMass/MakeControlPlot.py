#! /usr/bin/python
 
import os,sys
import glob
import array
from ROOT import *
import math
from copy import copy
from MassSuperScriptPlots import *

print sys.argv[0]
print sys.argv[1]

Number = int(sys.argv[1])

doNormalised = True
doOfficial   = True

MainVec = []
#MainVec.append(["all_el", "root_Histo14062017_el"])
#MainVec.append(["all_mu", "root_Histo14062017_mu"])

entry = MainVec[Number]

NomFolder    = "Histograms3/"+entry[1]+"/"

SelType = entry[0]

PlotFolder   = "TestPlots_"+SelType+"_Comb_Absolute/"

if doNormalised:
    PlotFolder = PlotFolder.replace("_Absolute/", "_Normalised/")

os.system("mkdir -p "+PlotFolder)
                        

def main():
    
    VariableList  = ReturnVariableListSimple()
    VariableList += ReturnVariableListTree()

    for Var in VariableList:
        varName   = Var[0]
        histName  = Var[5]
        xTitle    = Var[6]
        DataHist0 = ReturnHistogram(NomFolder+"/3dTMTcompact_0.root",    histName)
        DataHist1 = ReturnHistogram(NomFolder+"/3dTMTcompact_1.root",    histName)
        HistData  = DataHist0+DataHist1

        # now read in nominal and systematic samples for each variation, hand over a flag if its ttbar only var
        HistNominal    = GetAllHistograms(MainFolder,  "",         histName)
        HistSumNorm    = GetAllHistograms(MainFolder,  "",         histName, "Norm")
        HistSumLumi    = GetAllHistograms(MainFolder,  "",         histName, "Lumi")
        HistSumPH      = GetAllHistograms(MainFolder,  "",         histName, "PH_AF2")
        HistSumMCatNLO = GetAllHistograms(MainFolder,  "",         histName, "MCatNLO_AF2")
        HistSum_hdamp  = GetAllHistograms(MainFolder,  "",         histName, "PP_hdamp_AF2")
        HistSum_radLo  = GetAllHistograms(MainFolder,  "",         histName, "PP_radLo_AF2")
        HistSum_radHi  = GetAllHistograms(MainFolder,  "",         histName, "PP_radHi_AF2")
        HistSum_PP     = GetAllHistograms(MainFolder,  "",         histName, "PP_AF2")
        HistSum_CR     = GetAllHistograms(MainFolder,  "",         histName, "CR_AF2")
        HistSum_mpi    = GetAllHistograms(MainFolder,  "",         histName, "mpiHi_AF2")

        # add uncertainties with different nominal
        HistNominalNeu = GetAllHistograms(MainFolder2, "_nominal",      histName)
        Hist_EES_Up    = GetAllHistograms(MainFolder2, "_ees_up",       histName)
        Hist_EES_Dw    = GetAllHistograms(MainFolder2, "_ees_down",     histName)
        Hist_EER_Up    = GetAllHistograms(MainFolder2, "_err_up",       histName)
        Hist_EER_Dw    = GetAllHistograms(MainFolder2, "_err_down",     histName)
        Hist_MUS_Up    = GetAllHistograms(MainFolder2, "_mu_scaleup",   histName)
        Hist_MUS_Dw    = GetAllHistograms(MainFolder2, "_mu_scaledown", histName)
        Hist_JER0_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP0",   histName)
        Hist_JER0_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP0", histName)
        Hist_JER1_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP1",   histName)
        Hist_JER1_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP1", histName)
        Hist_JER2_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP2",   histName)
        Hist_JER2_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP2", histName)
        Hist_JER3_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP3",   histName)
        Hist_JER3_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP3", histName)
        Hist_JER4_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP4",   histName)
        Hist_JER4_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP4", histName)
        Hist_JER5_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP5",   histName)
        Hist_JER5_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP5", histName)
        Hist_JER6_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP6",   histName)
        Hist_JER6_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP6", histName)
        Hist_JER7_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP7",   histName)
        Hist_JER7_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP7", histName)
        Hist_JER8_Up   = GetAllHistograms(MainFolder2, "_jer_up_NP8",   histName)
        Hist_JER8_Dw   = GetAllHistograms(MainFolder2, "_jer_down_NP8", histName)

        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_EES_Up,  Hist_EES_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_EER_Up,  Hist_EER_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_MUS_Up,  Hist_MUS_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER0_Up, Hist_JER0_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER1_Up, Hist_JER1_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER2_Up, Hist_JER2_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER3_Up, Hist_JER3_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER4_Up, Hist_JER4_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER5_Up, Hist_JER5_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER6_Up, Hist_JER6_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER7_Up, Hist_JER7_Dw)
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistNominalNeu,  Hist_JER8_Up, Hist_JER8_Dw)

        # now add one-sided systematics from new setup on top
        OneSidedNew = ReturnSystematicOneSidedNew()
        for OneSided in OneSidedNew:
            HistHelp    = GetAllHistograms(MainFolder2, "_"+OneSided, histName)
            HistNominal = AddUncertaintyOneSidedOnTop(HistNominal, HistNominalNeu, HistHelp)            

        # now add one-sided systematics from old setup on top                                                                          
        OneSidedOld = ReturnSystematicOneSidedOld()
        for OneSided in OneSidedOld:
            HistHelp    = GetAllHistograms(MainFolder, "_"+OneSided, histName)
            HistNominal = AddUncertaintyOneSided(HistNominal, HistHelp)

        # now add two-sided systematics from old setup on top
        TwoSidedOld = ReturnSystematicsTwoSidedOld()
        for TwoSided in TwoSidedOld:
            #print TwoSided," before ",HistNominal[0][0].GetBinError(1)
            HistHelpUp  = GetAllHistograms(MainFolder, "_"+TwoSided+"_up",   histName)
            HistHelpDw  = GetAllHistograms(MainFolder, "_"+TwoSided+"_down", histName)
            HistNominal = AddUncertaintyTwoSided(HistNominal, HistHelpUp, HistHelpDw)
            #print TwoSided," after ",HistNominal[0][0].GetBinError(1)

        ObjectSF = ReturnListObjectSF()
        BkgSF    = ReturnListBkgSF()

        # add b-tagging and lepton SF
        for objectSF in ObjectSF:
            SFFlag = objectSF[0]
            nrComp = objectSF[1]

            for iComp in range(0, nrComp):

                OutputFlagUp = SFFlag+"up"+str(iComp)
                OutputFlagDw = SFFlag+"dw"+str(iComp)

                HistUp = GetAllHistograms(MainFolder, "_"+OutputFlagUp, histName, "SF")
                HistDw = GetAllHistograms(MainFolder, "_"+OutputFlagDw, histName, "SF")
                HistNominal = AddUncertaintyTwoSided(HistNominal, HistUp, HistDw)

        # add W+jets SF
        for bkgSF in BkgSF:
            SFFlag = bkgSF[0]

            OutputFlagUp = SFFlag+"up"
            OutputFlagDw = SFFlag+"down"

            #print "Wjets SF"
            HistUp = GetAllHistograms(MainFolder, "_"+OutputFlagUp, histName, "Wjets")
            HistDw = GetAllHistograms(MainFolder, "_"+OutputFlagDw, histName, "Wjets")

            HistNominal = AddUncertaintyTwoSided(HistNominal, HistUp, HistDw)


        
        HistNominal    = AddUncertaintyOneSidedOnTop(HistNominal, HistSumPH,      HistSum_PP) # add PS uncertainty
        HistNominal    = AddUncertaintyOneSidedOnTop(HistNominal, HistSumMCatNLO, HistSum_PP) # add ME uncertainty
        HistNominal    = AddUncertaintyTwoSidedOnTop(HistNominal, HistSum_hdamp,  HistSum_radHi, HistSum_radLo) # add ISR/FSR uncertainty
        HistNominal    = AddUncertaintyOneSidedOnTop(HistNominal, HistSum_CR,     HistSum_PP) # add CR uncertainty
        HistNominal    = AddUncertaintyOneSidedOnTop(HistNominal, HistSum_mpi,    HistSum_PP) # add mpi uncertainty
        
        HistNominal    = AddUncertaintyOneSided(HistNominal, HistSumNorm)
        HistNominal    = AddUncertaintyOneSided(HistNominal, HistSumLumi)
                
        HistNominalSum = AddAllHistograms(HistNominal)

        # then here I need to add code that calculates the unc and puts it on top of the HistNominalSumError
        ratioplot(HistData, HistNominalSum, HistNominal, "Data", "MC", histName, xTitle)



def AddUncertaintyOneSided(HistVecNom, HistVecVar):
    
    OutVec = []

    for i in range(0, len(HistVecNom)):

        Nom = HistVecNom[i][0]
        Var = HistVecVar[i][0]

        #print Nom.Integral(),"   ",Var.Integral(),"   ",Var.Integral()/Nom.Integral()
        
        if doNormalised:
            Var.Scale(Nom.Integral()/Var.Integral())

        for j in range(1, Nom.GetNbinsX()+1):
            diff   = Nom.GetBinContent(j) - Var.GetBinContent(j)
            errOld = Nom.GetBinError(j)
            Nom.SetBinError(j, sqrt(errOld*errOld + diff*diff))

            #if sqrt(errOld*errOld + diff*diff) < errOld:
            #print "ERROR !!!! -----------------------------------------> ",j,"  ",errOld,"  ",sqrt(errOld*errOld + diff*diff),"   ",diff
            
            #print j,"  ",errOld,"  ",sqrt(errOld*errOld + diff*diff),"   ",diff,"  ",Nom.GetBinError(j)/Nom.GetBinContent(j)
            
        OutVec.append([Nom, HistVecNom[i][1], HistVecNom[i][2]])

    return OutVec


# to add modelling uncertainties and for example compare AFII/AFII and put diff. on nominal!
def AddUncertaintyOneSidedOnTop(HistVecNom, HistVecVar1, HistVecVar2):

    OutVec = []

    for i in range(0, len(HistVecNom)):

        Nom  = HistVecNom[i][0]
        Var1 = HistVecVar1[i][0]
        Var2 = HistVecVar2[i][0]

        if doNormalised:
            Var2.Scale(Var1.Integral()/Var2.Integral())
            
            
        for j in range(1, Nom.GetNbinsX()+1):
            diff   = Var1.GetBinContent(j) - Var2.GetBinContent(j)
            errOld = Nom.GetBinError(j)
            Nom.SetBinError(j, sqrt(errOld*errOld + diff*diff))

            if sqrt(errOld*errOld + diff*diff) < errOld:
                print "ERROR !!!! -----------------------------------------> ",j,"  ",errOld,"  ",sqrt(errOld*errOld + diff*diff),"   ",diff
                                

            
        OutVec.append([Nom, HistVecNom[i][1], HistVecNom[i][2]])

    return OutVec


def AddUncertaintyTwoSided(HistVecNom, HistVecVarUp, HistVecVarDown):

    OutVec = []

    for i in range(0, len(HistVecNom)):

        Nom   = HistVecNom[i][0]
        VarUp = HistVecVarUp[i][0]
        VarDw = HistVecVarDown[i][0]

        if doNormalised:
            VarUp.Scale(Nom.Integral()/VarUp.Integral())
            VarDw.Scale(Nom.Integral()/VarDw.Integral())

        for j in range(1, Nom.GetNbinsX()+1):
            NomVal = Nom.GetBinContent(j)
            UpVal  = VarUp.GetBinContent(j)
            DwVal  = VarDw.GetBinContent(j)

            diff   = 0

            # check if nom between up and down
            if((UpVal-NomVal)*(NomVal-DwVal) < 0):
                diff1 = math.fabs(UpVal-NomVal)
                diff2 = math.fabs(NomVal-DwVal)
            
                if diff1 > diff2:
                    diff = diff1
                else:
                    diff = diff2

            else:
                diff = math.fabs((UpVal - DwVal)/2.0)

            errOld = Nom.GetBinError(j)
            Nom.SetBinError(j, sqrt(errOld*errOld + diff*diff))

            #print j,"   ",diff,"   ",Nom.GetBinContent(j),"   ",diff/Nom.GetBinContent(j)
            
            #if sqrt(errOld*errOld + diff*diff) < errOld:
            #    print "ERROR !!!! -----------------------------------------> ",j,"  ",errOld,"  ",sqrt(errOld*errOld + diff*diff),"   ",diff
                                
            
        OutVec.append([Nom, HistVecNom[i][1], HistVecNom[i][2]])

    return OutVec            


def AddUncertaintyTwoSidedOnTop(HistVecNom, HistVecNewNom, HistVecVarUp, HistVecVarDown):

    OutVec = []

    for i in range(0, len(HistVecNom)):

        Nom    = HistVecNom[i][0]
        NewNom = HistVecNewNom[i][0]
        VarUp  = HistVecVarUp[i][0]
        VarDw  = HistVecVarDown[i][0]

        if doNormalised:
            VarUp.Scale(NewNom.Integral()/VarUp.Integral())
            VarDw.Scale(NewNom.Integral()/VarDw.Integral())

        for j in range(1, Nom.GetNbinsX()+1):
            NomVal = NewNom.GetBinContent(j)
            UpVal  = VarUp.GetBinContent(j)
            DwVal  = VarDw.GetBinContent(j)

            diff   = 0

            # check if nom between up and down                                                                                                                                                                                                                                     
            if((UpVal-NomVal)*(NomVal-DwVal) < 0):
                diff1 = math.fabs(UpVal-NomVal)
                diff2 = math.fabs(NomVal-DwVal)

                if diff1 > diff2:
                    diff = diff1
                else:
                    diff = diff2

            else:
                diff = math.fabs((UpVal - DwVal)/2.0)

            errOld = Nom.GetBinError(j)
            Nom.SetBinError(j, sqrt(errOld*errOld + diff*diff))

            if sqrt(errOld*errOld + diff*diff) < errOld:
                print "ERROR !!!! -----------------------------------------> ",j,"  ",errOld,"  ",sqrt(errOld*errOld + diff*diff),"   ",diff
                                
            
        OutVec.append([Nom, HistVecNom[i][1], HistVecNom[i][2]])

    return OutVec



def AddAllHistograms(HistVec):

    #Histogram = HistVec[0][0] + HistVec[0][0] + HistVec[0][0] +HistVec[0][0]+HistVec[0][0]+HistVec[0][0]

    Histogram = HistVec[0][0].Clone()

    for i in range(1, len(HistVec)):
        Histogram += HistVec[i][0]
    
    return Histogram


def GetAllHistograms(FolderName, SystFlag, HistoName, ExtraFlag="None"):
    
    TTbar     = ReturnHistogram(FolderName+"/3dTMTcompact_1725"+SystFlag+".root", HistoName)
    SingleTop = ReturnHistogram(FolderName+"/3dTMTcompact_6275"+SystFlag+".root", HistoName)
    Wjets     = ReturnHistogram(FolderName+"/3dTMTcompact_3"+SystFlag+".root",    HistoName)
    Zjets     = ReturnHistogram(FolderName+"/3dTMTcompact_4"+SystFlag+".root",    HistoName)
    Diboson   = ReturnHistogram(FolderName+"/3dTMTcompact_5"+SystFlag+".root",    HistoName)
    QCD0      = ReturnHistogram(NomFolder+"/3dTMTcompact_9990.root",              HistoName)
    QCD1      = ReturnHistogram(NomFolder+"/3dTMTcompact_9991.root",              HistoName)
    QCD       = QCD0+QCD1

    for i in range(1, QCD.GetNbinsX()+1):
        QCD.SetBinError(i, 0)
    

    #TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_105860_fast.root", HistoName)

    if ExtraFlag == "PH_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_105860_fast.root", HistoName)
    if ExtraFlag == "MCatNLO_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_105200_fast.root", HistoName)
    if ExtraFlag == "PP_hdamp_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_110404_fast_mc12b.root", HistoName)
    if ExtraFlag == "PP_radLo_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_110407_fast_mc12b.root", HistoName)
    if ExtraFlag == "PP_radHi_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_110408_fast_mc12b.root", HistoName)
    if ExtraFlag == "PP_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_117050_fast.root", HistoName)
    if ExtraFlag == "CR_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_110402_fast_mc12b.root", HistoName)
    if ExtraFlag == "mpiHi_AF2":
        TTbar     = ReturnHistogram(NomFolder+"/3dTMTcompact_110403_fast_mc12b.root", HistoName)


    if ExtraFlag == "Norm":
        #print "norm"
        TTbar.Scale(1.057)
        SingleTop.Scale(1.06)
        Wjets.Scale(1.0)  # take only charge asymmetry uncertainties
        #value = Zjets.Integral()
        #print Zjets.Integral()
        
        Zjets.Scale(1.48)
        #print Zjets.Integral(),"  ",Zjets.Integral()/value
        Diboson.Scale(1.48)
        #print QCD.Integral()
        value = QCD.Integral()
        QCD.Scale(2.0)
        #print QCD.Integral(),"  ",QCD.Integral()/value
        

    if ExtraFlag == "Lumi":
        TTbar.Scale(1.019)
        SingleTop.Scale(1.019)
        Wjets.Scale(1.019)
        Zjets.Scale(1.019)
        Diboson.Scale(1.019)
        QCD.Scale(1.0)
    
    # Histogram, label, colour
    Vec = []
    Vec.append([TTbar,     "t#bar{t}, m_{top}=172.5 GeV",   0])
    Vec.append([SingleTop, "Single top",                   62])
    Vec.append([Wjets,     "W+jets",                       95])
    Vec.append([Zjets,     "Z+jets",                       92])
    Vec.append([Diboson,   "WW/WZ/ZZ",                      5])
    Vec.append([QCD,       "NP/fake leptons",             619])

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

     h3.SetStats(0)
     h3.Divide(h22)
     
     # Adjust y-axis settings
     y = h4.GetYaxis()
     y.SetTitle(Name1+"/"+Name2)
     y.SetNdivisions(505)
     y.SetTitleSize(22)
     y.SetTitleFont(43)
     y.SetTitleOffset(1.55)
     y.SetLabelFont(43)
     y.SetLabelSize(22)

     # Adjust x-axis settings
     x = h4.GetXaxis()
     x.SetTitleSize(26)
     x.SetTitleFont(43)
     x.SetTitleOffset(4.2)
     x.SetLabelFont(43)
     x.SetLabelSize(22)

     print gStyle.GetTickLength("x"),"   ",gStyle.GetTickLength("y")
     
     return h3,h4


def createCanvasPads(histName):
    c = TCanvas(histName, histName, 10, 10, 700, 600)
    # Upper histogram plot is pad1
    pad1 = TPad("pad1", "pad1", 0, 0.3, 1, 1.0)
    pad1.SetBottomMargin(0.05)  # joins upper and lower plot
    #pad1.SetGridx()
    # Lower ratio plot is pad2
    c.cd()  # returns to main canvas before defining pad2
    pad2 = TPad("pad2", "pad2", 0, 0.04, 1, 0.31)
    pad2.SetTopMargin(0)  # joins upper and lower plot
    pad2.SetBottomMargin(0.4)
    pad2.SetGridy()

    style=ROOT.gStyle
    style.SetOptStat(0)
    style.SetOptTitle(0)
    style.SetFrameBorderMode(0)
    style.SetFrameFillColor(0)
    style.SetCanvasBorderMode(0)
    style.SetCanvasColor(0)
    style.SetPadBorderMode(0)
    style.SetPadColor(0)
    style.SetStatColor(0)
    style.SetPadTopMargin(0.06)
    style.SetPadRightMargin(0.05)
    style.SetPadBottomMargin(0.16)
    style.SetPadLeftMargin(0.16)
    style.SetPadTickX(1)
    style.SetPadTickY(1)
    
    pad1.Draw()
    pad2.Draw()
    
    return c, pad1, pad2
    
    
#ratioplot(HistData, HistNominalSum, HistNominal, "Data", "MC", histName, xTitle)

def GetUncertainty(histo):

    #print "===========================================> GetUncertainty"
    
    totalUnc = 0

    for i in range(1, histo.GetNbinsX()+1):
        binErr = histo.GetBinError(i)
        #print i,"   ",histo.GetBinContent(i),"   ",binErr,"  ",binErr/histo.GetBinContent(i)
        totalUnc += binErr #*binErr

    #print totalUnc/histo.Integral(),"   ",histo.GetBinError(histo.GetNbinsX()+1),"  ",histo.GetBinContent(histo.GetNbinsX()+1)
        
    return totalUnc


def MakeLatexTable(Folder, h1, h2, HistVec):
    bkgHisto = HistVec[2][0].Clone()
    bkgHisto.Add(HistVec[3][0])
    bkgHisto.Add(HistVec[4][0])
    bkgHisto.Add(HistVec[5][0])

    bkgFraction    = bkgHisto.Integral()/h2.Integral()
    bkgUnc         = GetUncertainty(bkgHisto)
    totUnc         = GetUncertainty(h2)
    bkgFractionUnc = bkgFraction*sqrt(bkgUnc*bkgUnc/bkgHisto.Integral()/bkgHisto.Integral() + totUnc*totUnc/h2.Integral()/h2.Integral()) 

    dataMC         = h1.Integral()/h2.Integral()
    dataUnc        = GetUncertainty(h1)
    dataMCUnc      = dataMC*sqrt(dataUnc*dataUnc/h1.Integral()/h1.Integral() + totUnc*totUnc/h2.Integral()/h2.Integral())
    
    outfile = open(Folder+"/EventYield.tex", "w")
    outfile.write("\\begin{table}  \\\\ \n")
    outfile.write("\\begin{tabular}{l|c}  \\\\ \n")
    outfile.write("\hline  \\\\ \n")
    outfile.write("Data & "+str(h1.Integral())+" \\\\ \n")
    outfile.write("\hline  \\\\ \n")
    outfile.write("$t\\bar{t}$ signal & "+str(round(HistVec[0][0].Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(HistVec[0][0]), 3))+"  \\\\ \n")
    outfile.write("Single-top-quark signal & "+str(round(HistVec[1][0].Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(HistVec[1][0]), 3))+"  \\\\ \n")
    #print "QCD unc"
    #outfile.write("NP/fake leptons (data) & "+str(round(HistVec[5][0].Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(HistVec[5][0]), 3))+"  \\\\ \n")
    outfile.write("NP/fake leptons (data) & "+str(round(HistVec[5][0].Integral(), 2))+" $\pm$ "+str(round(HistVec[5][0].Integral(), 3))+"  \\\\ \n")
    #print "Wjets"
    outfile.write("$W$+jets (data) & "+str(round(HistVec[2][0].Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(HistVec[2][0]), 3))+"  \\\\ \n")
    #print "Zjets"
    outfile.write("$Z$+jets & "+str(round(HistVec[3][0].Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(HistVec[3][0]), 3))+"  \\\\ \n")
    outfile.write("$WW/WZ/ZZ$ & "+str(round(HistVec[4][0].Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(HistVec[4][0]), 3))+"  \\\\ \n")
    outfile.write("\hline  \\\\ \n")
    outfile.write("Signal+background & "+str(round(h2.Integral(), 2))+" $\pm$ "+str(round(GetUncertainty(h2), 3))+"  \\\\ \n")
    outfile.write("\hline  \\\\ \n")
    outfile.write("Expected background fraction & "+str(round(bkgFraction,3))+" $\pm$ "+str(round(bkgFractionUnc, 4))+" \\\\ \n")
    outfile.write("Data/(Signal + background) & "+str(round(dataMC, 3))+" $\pm$ "+str(round(dataMCUnc, 3))+" \\\\ \n ")
    outfile.write("\hline  \n")
    outfile.write("\end{tabular}")
    outfile.write("\end{table}")
    outfile.close()
        

def ratioplot(h1, h2, HistVec, Name1, Name2, histName, xTitle):

    if "yield" in histName:
        MakeLatexTable(PlotFolder, h1, h2, HistVec)

    scale = h1.Integral()/h2.Integral()
        
    if doNormalised:
        #h1.Scale(1.0/h1.Integral())
        h2.Scale(h1.Integral()/h2.Integral())

        
    h1.SetLineColor(kBlack)
    h2.SetLineColor(kBlack)

    #VariableList.append(["BhadPt",        65,    0,  325,  True, "h_BhadPt",    "b jets p_{T} [GeV]"]) # check content
    #VariableList.append(["BlepPt",        65,    0,  325,  True, "h_BlepPt",    "b jets p_{T} [GeV]"]) # check content
    #VariableList.append(["nvtx",          25,    0,   25,  True, "h_nvtx",      "n_{vtx}"])
    #VariableList.append(["mu",            40,    0,   40,  True, "h_mu",        "<interactions per crossing>"])
    #VariableList.append(["tagPt",       65,    0,  325, True, "h_tagPt",       "b-tagged jets p_{T} [GeV]"])
    #VariableList.append(["tagEta",      50, -2.5,  2.5, True, "h_tagEta",      "b-tagged jets #eta"])
    #VariableList.append(["untagPt",     65,    0,  325, True, "h_untagPt",     "Untagged jets p_{T} [GeV]"])
    #VariableList.append(["untagEta",    50, -2.5,  2.5, True, "h_untagEta",    "Untagged jets #eta"])
    #VariableList.append(["jetPt",       65,    0,  325, True, "h_jetPt",       "Jet p_{T} [GeV]"])
    #VariableList.append(["jetEta",      50, -2.5,  2.5, True, "h_jetEta",      "Jet #eta"])
        

    if "ntag" in histName:
        histName = histName.replace("ntag", "Nbtag")
    if "mwt" in histName:
        histName = histName.replace("mwt", "MWt")
    if "met" in histName:
        histName = histName.replace("met", "Met")
    if "_lepPt" in histName:
        histName = histName.replace("_lepPt", "_LepPt")
    if "AveAllJetPt" in histName:
        histName = histName.replace("AveAllJetPt", "alljets_average_pt")
    if "LL" in histName:
        histName = histName.replace("LL", "KLFLike")
    if "mtop" in histName:
        histName = histName.replace("mtop", "mtop_stdsel")
    if "mw" in histName:
        histName = histName.replace("mw", "mw_stdsel")
    if "RlbCalo" in histName:
        histName = histName.replace("RlbCalo", "rlbcalo_stdsel")
    if "TTbarPt" in histName:
        histName = histName.replace("TTbarPt", "TTbarPT")
    if "dR_bjets" in histName:
        histName = histName.replace("dR_bjets", "DRbjets")
    if "dR_Wjets" in histName:
        histName = histName.replace("dR_Wjets", "DRwjets")
    if "Prob" in histName:
        histName = histName.replace("Prob", "EvtProb")
    if "WHadPt" in histName:
        histName = histName.replace("WHadPt", "WhadPt")
    if "WLepPt" in histName:
        histName = histName.replace("WLepPt", "WlepPt")
    #if "" in histName:
    #    histName = histName.replace("", "")
    #if "" in histName:
    #    histName = histName.replace("", "")
    #if "" in histName:
    #    histName = histName.replace("", "")
    #if "" in histName:
    #    histName = histName.replace("", "")
    #if "" in histName:
    #    histName = histName.replace("", "")
    #if "" in histName:
    #    histName = histName.replace("", "")
    #if "" in histName:
    #    histName = histName.replace("", "")
                                        

        
    outputFile     = PlotFolder+"/Plot_3dTMT_dataMC_"+histName.replace("h_", "")+"_s1725_"+SelType+".pdf"
    outputFileRoot = PlotFolder+"/Plot_3dTMT_dataMC_"+histName.replace("h_", "")+"_s1725_"+SelType+".root"

    if doOfficial:
        outputFile     = PlotFolder+"/Plot_3dTMT_dataMC_"+histName.replace("h_", "")+"_s1725_"+SelType+"_Prelim.pdf"
        
    #Plot_3dTMT_dataMC_AveJetPt_s1725_seltype997.png

    h3, h4 = createRatio(h1, h2, Name1, Name2)
    c, pad1, pad2 = createCanvasPads(histName)

    # draw everything
    pad1.cd()

    #if not "Number" in xTitle:
    #    pad1.SetLogy()
    
    y = h2.GetYaxis()

    #if doNormalised:
    #    if "GeV" in xTitle:
    #        BinWidth = h1.GetBinWidth(1)
    #        if BinWidth == 1:
    #            y.SetTitle("Entries / GeV")
    #        else:
    #            y.SetTitle("Entries / "+str(BinWidth)+" GeV")
    #    else:
    #        y.SetTitle("Events")
    #
    #else:


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



    leg1 = TLegend(0.2, 0.685, 0.2+0.23, 0.71+0.21)
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

    leg2 = TLegend(0.6, 0.685, 0.6+0.23, 0.71+0.21)
    leg2.SetFillColor(0)
    leg2.SetFillStyle(0)
    leg2.SetBorderSize(0)
    leg2.SetTextSize(0.05)

    counter_leg = 0

    for entry in HistVec:
        counter_leg += 1
        if counter_leg <= 3:
            continue
        leg2.AddEntry(entry[0], entry[1], "f")

    leg2.AddEntry(h2, "Uncertainty", "f")

    nmax_h1 = h1.GetBinContent(h1.GetMaximumBin())
    nmax_h2 = h2.GetBinContent(h2.GetMaximumBin())

    maxi = nmax_h1*1.70

    if(nmax_h2 > nmax_h1):
        maxi = nmax_h2*1.70

    #if not "Number" in xTitle:
    #    maxi = nmax_h2*16.5

    h2.SetMaximum(maxi)
    h2.SetMinimum(0.0001)
        
    x = h2.GetXaxis()
    x.SetLabelSize(0)
    x.SetTitleSize(0)

    gStyle.SetHatchesSpacing(1.2)
    gStyle.SetHatchesLineWidth(1)
    gStyle.SetPadTickX(1)
    gStyle.SetPadTickY(1)       
    
    h2.SetFillStyle(3244)
    h2.SetFillColor(kBlack)
    h2.Draw()


    


    
    l = TLatex()
    l.SetNDC()
    l.SetTextFont(42)
    l.SetTextColor(1)
    l.SetTextSize(0.055)
    
    if "ln" in xTitle or "BDT" in xTitle:
        l.DrawLatex(0.21,  0.535, "#sqrt{s}=8 TeV, 20.2 fb^{-1}")
    else:
        l.DrawLatex(0.655, 0.535, "#sqrt{s}=8 TeV, 20.2 fb^{-1}")

    l2 = TLatex()
    l2.SetNDC();
    l2.SetTextFont(72);
    l2.SetTextColor(1);
    l2.SetTextSize(0.055)

    if "ln" in xTitle or "BDT" in xTitle:
        l2.DrawLatex(0.21,  0.6, "ATLAS")
    else:
        l2.DrawLatex(0.655, 0.6, "ATLAS")

    l3 = TLatex()
    l3.SetNDC();
    l3.SetTextFont(42);
    l3.SetTextColor(1);
    l3.SetTextSize(0.055)

    if "ln" in xTitle or "BDT" in xTitle:
        if doOfficial:
            l3.DrawLatex(0.32,  0.6, "Preliminary")
        else:
            l3.DrawLatex(0.32,  0.6, "Internal")
    else:
        if doOfficial:
            l3.DrawLatex(0.765, 0.6, "Preliminary")
        else:
            l3.DrawLatex(0.765, 0.6, "Internal")
    
    h1.SetMarkerSize(1.2)
    h1.SetMarkerStyle(20)

    upperEdge = BinWidth*h2.GetNbinsX()+h2.GetBinLowEdge(1)
    
    if "pt" in histName or "Pt" in histName:
        h2.GetXaxis().SetRangeUser(25.0, upperEdge)
        h1.GetXaxis().SetRangeUser(25.0, upperEdge)

    if "Met" in histName:
        h2.GetXaxis().SetRangeUser(20.0, upperEdge)
        h1.GetXaxis().SetRangeUser(20.0, upperEdge)

    if "BDT" in histName:
        h2.GetXaxis().SetRangeUser(-0.65, 0.4)
        h1.GetXaxis().SetRangeUser(-0.65, 0.4)
                        
        
    #h2.Draw("E2")
    stack0.Draw("SAME")
    h2.Draw("E2same")
    h1.Draw("SAME")
    #h1.Draw("axis")

    #upperEdge = BinWidth*h2.GetNbinsX()+h2.GetBinLowEdge(1)

    #print upperEdge,"  ",histName
    
    #if "pt" in histName or "Pt" in histName:
    #    stack0.GetXaxis().SetLimits(25.0, upperEdge)
    #    h2.GetXaxis().SetLimits(25.0, upperEdge)
    #    h1.GetXaxis().SetLimits(25.0, upperEdge)
        
        
    gStyle.SetOptStat(0)

    leg1.Draw("SAME")
    leg2.Draw("SAME")

    pad2.cd()


    if "pt" in histName or "Pt" in histName:
        h4.GetXaxis().SetRangeUser(25.0, upperEdge)
        h3.GetXaxis().SetRangeUser(25.0, upperEdge)

    if "Met" in histName:
        h4.GetXaxis().SetRangeUser(20.0, upperEdge)
        h3.GetXaxis().SetRangeUser(20.0, upperEdge)

    if "BDT" in histName:
        h4.GetXaxis().SetRangeUser(-0.65, 0.4)
        h3.GetXaxis().SetRangeUser(-0.65, 0.4)
                
        
    h4.GetXaxis().SetTitle(xTitle)
    h4.SetFillStyle(3244)
    h4.SetFillColor(kBlack)
    h4.GetYaxis().SetNdivisions(5)
    h4.Draw("E2")

    if "njet" in outputFile:
        h4.GetXaxis().SetNdivisions(5)
        h4.GetXaxis().SetBinLabel(1,"4")
        h4.GetXaxis().SetBinLabel(2,"5")
        h4.GetXaxis().SetBinLabel(3,"6")
        h4.GetXaxis().SetBinLabel(4,"#geq 7")
        #h4.GetXaxis().SetLabelOffset(0.3)
        #print h4.GetXaxis().GetLabelOffset()
        h4.GetXaxis().SetLabelOffset(0.012)
        
    if "ntag" in outputFile:
        h4.GetXaxis().SetNdivisions(5)
        
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
    main()
    #print "Hier!"
   
