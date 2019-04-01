#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
import array
from ROOT import *
import math
from array import array

from copy import copy
sys.path.append('SortingScripts')
import VariableList
from MassDictionaries import *
from DefineSamples import *

def AddOverflows(Histogram):
    
    NBins       = Histogram.GetNbinsX()
    BinUnder    = Histogram.GetBinContent(0)
    BinUnderErr = Histogram.GetBinError(0)
    BinOne      = Histogram.GetBinContent(1)
    BinOneErr   = Histogram.GetBinError(1)
    BinOver     = Histogram.GetBinContent(NBins+1)
    BinOverErr  = Histogram.GetBinError(NBins+1)
    BinLast     = Histogram.GetBinContent(NBins)
    BinLastErr  = Histogram.GetBinError(NBins)

    Histogram.SetBinContent(0, 0)
    Histogram.SetBinError(0,   0)
    Histogram.SetBinContent(NBins+1, 0)
    Histogram.SetBinError(NBins+1,   0)
    Histogram.SetBinContent(1, BinUnder+BinOne)
    Histogram.SetBinError(1,   math.sqrt(BinUnderErr*BinUnderErr+BinOneErr*BinOneErr))
    Histogram.SetBinContent(NBins, BinOver+BinLast)
    Histogram.SetBinError(NBins,   math.sqrt(BinOverErr*BinOverErr+BinLastErr*BinLastErr))

    return Histogram


def AddBKHistograms(ListFiles, Channel):
    # open file number one and store histogram in new histo

    Channel = Channel.replace("", "")

    fF = TFile(ListFiles[0], "READ")
    histo = TH1D() 
    histo = fF.Get(Channel+"/cutflow_mc_pu")
    #print ListFiles[0]
    #print Channel
    #print histo.Integral()

    for i in range(1, len(ListFiles)):
        fHelp     = TFile(ListFiles[i], "READ")
        histoHelp = fHelp.Get(Channel+"/cutflow_mc_pu")

        #print ListFiles[i]
        #print Channel+"/cutflow_mc_pu"
        
        histo.Add(histoHelp)

    return copy(histo)


def GetCrossSection(DSID):
    fInFile = open("SortingScripts/XSection-MC15-13TeV.data", 'r')
    fInputLines = fInFile.readlines()
    fInFile.close()

    #print "================================================================================> ",DSID

    for entry in fInputLines:
        if DSID in entry:
            SubArray     = entry.split()
            CrossSection = float(SubArray[1])*float(SubArray[2])
            return CrossSection

    return -1000.0


def MakeChain(ListFiles, Tree):    
    newChain = TChain(Tree)
    for entry in ListFiles:
        newChain.Add(entry)
    return newChain


def PrepareInputTrees(Chain, Channel, NormFactorList, OutputFile, Cuts, DSID, TreeName):

    NewCuts = Cuts.replace("*", "&&")
    #NewCuts = NewCuts.replace("(", "")
    #NewCuts = NewCuts.replace(")", "")
    
    if NewCuts.endswith("&&"):
        NewCuts = NewCuts[:-2]

    NewCuts = NewCuts.replace("&&&&", "&&")

    fF_out = TFile(OutputFile, "RECREATE")

    fT_interm = Chain.CopyTree(NewCuts)

    fT_interm.SetBranchStatus("*", 0)
    fT_interm.SetBranchStatus("*generator*", 1)
    fT_interm.SetBranchStatus("weight_*", 1)
    fT_interm.SetBranchStatus("weight_indiv*", 0)
    fT_interm.SetBranchStatus("*global*", 0)
    fT_interm.SetBranchStatus("eventNumber", 1)
    fT_interm.SetBranchStatus("runNumber", 1)
    fT_interm.SetBranchStatus("randomRunNumber", 1)
    fT_interm.SetBranchStatus("mcChannelNumber", 1)
    fT_interm.SetBranchStatus("mu", 1)

    if Channel == "lepjets":
        fT_interm.SetBranchStatus("tma_klfitter_mtop_param", 1)
        fT_interm.SetBranchStatus("tma_original_mw",   1)
        fT_interm.SetBranchStatus("tma_original_rbq",  1)
    else:
        fT_interm.SetBranchStatus("tma_mlb_minmaxavg", 1)
    
    fT_out = fT_interm.CloneTree(0)  

    weight_FSR20 = 0.0
    weight_FSR05 = 0.0
    weight_ISR20 = 0.0
    weight_ISR05 = 0.0

    # SUPER UGLY! Need to find more elegant solution later
    d0 = array( 'f', [0.])
    d0[0] = NormFactorList[0][0]
    d1 = array( 'f', [0.])
    d1[0] = NormFactorList[1][0]
    d11 = array( 'f', [0.])
    d11[0] = weight_FSR20
    d2 = array( 'f', [0.])
    d2[0] = NormFactorList[2][0]
    d22 = array( 'f', [0.])
    d22[0] = weight_FSR05
    d3 = array( 'f', [0.])
    d3[0] = NormFactorList[3][0]
    d33 = array( 'f', [0.])
    d33[0] = weight_ISR20
    d4 = array( 'f', [0.])
    d4[0] = NormFactorList[4][0]
    d44 = array( 'f', [0.])
    d44[0] = weight_ISR05


    fT_out.Branch(NormFactorList[0][1], d0, NormFactorList[0][1]+'/F')
    fT_out.Branch(NormFactorList[1][1], d1, NormFactorList[1][1]+'/F')
    fT_out.Branch(NormFactorList[2][1], d2, NormFactorList[2][1]+'/F')
    fT_out.Branch(NormFactorList[3][1], d3, NormFactorList[3][1]+'/F')
    fT_out.Branch(NormFactorList[4][1], d4, NormFactorList[4][1]+'/F')
    fT_out.Branch("weight_FSR20", d11, 'weight_FSR20/F')
    fT_out.Branch("weight_FSR05", d22, 'weight_FSR05/F')
    fT_out.Branch("weight_ISR20", d33, 'weight_ISR20/F')
    fT_out.Branch("weight_ISR05", d44, 'weight_ISR05/F')

    for i in range(0, fT_interm.GetEntries()):
        fT_interm.GetEntry(i)

        if "nominal" in TreeName:
            if DSID == "410470" or DSID== "410472" or DSID== "410480" or DSID== "410482": 
                d11[0] = fT_interm.mc_generator_weights[198]/fT_interm.mc_generator_weights[0]
                d22[0] = fT_interm.mc_generator_weights[199]/fT_interm.mc_generator_weights[0]
                d33[0] = fT_interm.mc_generator_weights[194]*fT_interm.mc_generator_weights[6]/fT_interm.mc_generator_weights[0]/fT_interm.mc_generator_weights[0]
                d44[0] = fT_interm.mc_generator_weights[193]*fT_interm.mc_generator_weights[5]/fT_interm.mc_generator_weights[0]/fT_interm.mc_generator_weights[0]
            
        fT_out.Fill()

    # this below is not enough for the modelling weights!
    #fT_out.CopyEntries(fT_interm)

    fT_out.Write("PE_Tree")
    fF_out.Close()


def FillHistograms(DSID, InputFolder, OutputFile, DataMCFlag, Tree, Weight, Channel, Flag, Cuts):

    #print DSID,"   ",DataMCFlag,"   ",Channel

    Lumi = 36184.86

    if "MC16d" in DataMCFlag:
        Lumi = 43813.7 

    HelpDataMCFlag = DataMCFlag

    if "data" in DataMCFlag or "Data" in DataMCFlag:
        if "2017" in OutputFile:
            HelpDataMCFlag = "MC16d"
        else:
            HelpDataMCFlag = "MC16a"

    VariableFlag = ReturnVariableFlag(Channel, HelpDataMCFlag)
   
    VarList    = VariableList.ReturnVariableListSimple(DataMCFlag, VariableFlag)
    InputFiles = glob.glob(InputFolder+"/*root*")

    if Flag == "Template":
        VarList = VariableList.ReturnVariableListTemplate(DataMCFlag, VariableFlag)
    if Flag == "KLFPerf":
        VarList = VariableList.ReturnVariablesKLFPerf()

    BKHistos   = []

    ChannelFlag = Channel
    NormEvents     = 0.0
    NormEvents_Tree = 0.0
    # these weights are needed to evaluate ISR/FSR uncertainties!
    NormEvents_Tree_FSR20 = 0.0
    NormEvents_Tree_FSR05 = 0.0
    NormEvents_Tree_ISR20 = 0.0
    NormEvents_Tree_ISR05 = 0.0
    NormEvents_Tree_ME20  = 0.0
    NormEvents_Tree_ME05  = 0.0

    ChannelList = ReturnChannelList(Channel, HelpDataMCFlag)

    if "data" in DSID or "grp" in InputFolder:
        Flag = "2017"
        if "data15" in DSID or "grp15" in InputFolder:
            Flag = "2015"
        if "data16" in DSID or "grp16" in InputFolder:
            Flag = "2016"

    ChannelFlag = "("

    counter = 0

    for i in range(0, len(ChannelList)):
        entry = ChannelList[i]
        entry = entry.replace("", "")
        Histo = AddBKHistograms(InputFiles, entry)                                                                                                                                                  
        BKHistos.append([Histo, "BK_"+entry])                                                                                                                                                        
        NormEvents = Histo.GetBinContent(1)
        if i < len(ChannelList)-1:
            ChannelFlag += entry+" || "
        else:
            ChannelFlag += entry+")"

    # or get normalisation from trees
    fT_weights      = MakeChain(InputFiles, "sumWeights")
    entries_weights = fT_weights.GetEntries()

    if not "Data" in DataMCFlag:
    
        for j in range(0, entries_weights):
            fT_weights.GetEntry(j)
            NormEvents_Tree += fT_weights.totalEventsWeighted_mc_generator_weights[0]
            if DSID == "410470" or DSID == "410472" or DSID == "410480" or DSID == "410482":
                NormEvents_Tree_FSR20 += fT_weights.totalEventsWeighted_mc_generator_weights[198]
                NormEvents_Tree_FSR05 += fT_weights.totalEventsWeighted_mc_generator_weights[199]
                NormEvents_Tree_ISR20 += fT_weights.totalEventsWeighted_mc_generator_weights[194]
                NormEvents_Tree_ISR05 += fT_weights.totalEventsWeighted_mc_generator_weights[193]
                NormEvents_Tree_ME20  += fT_weights.totalEventsWeighted_mc_generator_weights[6]
                NormEvents_Tree_ME05  += fT_weights.totalEventsWeighted_mc_generator_weights[5]
            else:
                NormEvents_Tree_FSR20 = 1
                NormEvents_Tree_FSR05 = 1
                NormEvents_Tree_ISR20 = 1
                NormEvents_Tree_ISR05 = 1
                NormEvents_Tree_ME20  = 1
                NormEvents_Tree_ME05  = 1
                
    else:
        NormEvents_Tree = 1
        NormEvents_Tree_FSR20 = 1
        NormEvents_Tree_FSR05 = 1
        NormEvents_Tree_ISR20 = 1
        NormEvents_Tree_ISR05 = 1
        NormEvents_Tree_ME20  = 1
        NormEvents_Tree_ME05  = 1



    # first thing to do: get the cross-sections from TopDataPrep, for the moment store the file in here
    CrossSection = GetCrossSection(DSID)
    NormFactor   = CrossSection*Lumi/NormEvents #_Tree
    NormFactor_FSR20 = CrossSection*Lumi/NormEvents_Tree_FSR20
    NormFactor_FSR05 = CrossSection*Lumi/NormEvents_Tree_FSR05
    NormFactor_ISR20 = CrossSection*Lumi/(NormEvents_Tree_ISR20*NormEvents_Tree_ME20/NormEvents_Tree)
    NormFactor_ISR05 = CrossSection*Lumi/(NormEvents_Tree_ISR05*NormEvents_Tree_ME05/NormEvents_Tree)

    NormFactorList = []
    NormFactorList.append([NormFactor,       "NormFactor"])
    NormFactorList.append([NormFactor_FSR20, "NormFactor_FSR20"])
    NormFactorList.append([NormFactor_FSR05, "NormFactor_FSR05"])
    NormFactorList.append([NormFactor_ISR20, "NormFactor_ISR20"])
    NormFactorList.append([NormFactor_ISR05, "NormFactor_ISR05"])

    # make chain of input files
    fT      = MakeChain(InputFiles, Tree+"")
    entries = fT.GetEntries()
    fF_out  = TFile(OutputFile, "RECREATE")

    FullWeight = "weight_mc*weight_pileup*weight_leptonSF*weight_jvt*weight_bTagSF_MV2c10_77*"+str(NormFactor)

    #if DSID == "410470":
    #    FullWeight = "mc_generator_weights[0]*weight_pileup*weight_leptonSF*weight_jvt*weight_bTagSF_MV2c10_77*"+str(NormFactor)

    #198    isr:muRfac=10_fsr:muRfac=20
    #199    isr:muRfac=10_fsr:muRfac=05


    if DataMCFlag == "MC15":
        FullWeight = "weight_mc*weight_pileup*weight_leptonSF*weight_jvt*weight_bTagSF_MV2c10_77*"+str(NormFactor)

    if "Data" in DataMCFlag:
        FullWeight = "1.0"

    #print str(FullWeight)+Cuts

    # now loop over all input variables, project them and write them out into dedicated root file
    for Var in VarList:
        varName    = Var[0]
        NBins      = Var[1]
        lowEdge    = Var[2]
        highEdge   = Var[3]
        doOverflow = Var[4]
        histName   = Var[5]
        
        h_tmp = TH1D(histName, histName, NBins, lowEdge, highEdge)
        h_tmp.Sumw2()            
        
        if "+" in varName:
            varNameList = varName.split("+")
            counter = 0
            for varNameEntry in varNameList:
                if counter == 0:
                    fT.Project(h_tmp.GetName(), varNameEntry, ChannelFlag+"*"+str(FullWeight)+Cuts)
                    counter += 1
                else:         
                    h_tmp2 = TH1D(histName+"_2", histName+"_2", NBins, lowEdge, highEdge)
                    h_tmp2.Sumw2()
                    fT.Project(h_tmp2.GetName(), varNameEntry, ChannelFlag+"*"+str(FullWeight)+Cuts)
                    h_tmp.Add(h_tmp2)
        else:
            fT.Project(h_tmp.GetName(), varName, ChannelFlag+"*"+str(FullWeight)+Cuts)

        if doOverflow:
            h_tmp = AddOverflows(h_tmp)

        h_tmp.Write(histName)

        
    for entry in BKHistos:
        entry[0].Write(entry[1])

    # now call here the tree maker                                                                                                                                                                        
    OutputFileTree = OutputFile.replace("Unmerged//Histogram", "Unmerged/Tree")
    InputTree = PrepareInputTrees(fT, VariableFlag, NormFactorList, OutputFileTree, ChannelFlag+"*"+Cuts, DSID, Tree)

    fF_out.Close()


def MergeHistos(InputFolder, List, Name, InputFlags):
    OutputFolder = InputFolder.replace("Unmerged", "Merged")
    os.system("mkdir -p "+OutputFolder)

    Label = "Comb"

    if len(InputFlags) == 1:
        Label = InputFlags[0]

    OutputFile     = OutputFolder+"/Merge_"+Name+"_"+Label+".root"
    OutputFileTree = OutputFolder+"/Merge_Tree_"+Name+"_"+Label+".root" 
        
    # only merge if the output file does not yet exist
    if not os.path.exists(OutputFile):
        MergeString     = ""
        MergeStringTree = ""

        doMerge = True

        counter = 0

        for InputFlag in InputFlags:

            for entry in List:
                #print entry
                File     = InputFolder+"/Histogram_"+entry+"_"+InputFlag+".root"
                FileTree = InputFolder+"/Tree_"+entry+"_"+InputFlag+".root"
            
                # if production incomplete: do not merge!
                #if not os.path.exists(File):
                #    doMerge = False

                if os.path.exists(File):
                    MergeString     += " "+File
                    MergeStringTree += " "+FileTree
                    counter += 1

        if len(MergeString) < 3:
            return

        if counter == 0:
            return

        if doMerge:
            os.system("hadd -f " + OutputFile + " " + MergeString)
            os.system("hadd -f " + OutputFileTree + " " + MergeStringTree)




def MergeAllHistos(InputFolder):

    InputFlags = [["MC16a"], ["MC16d"], ["MC16a", "MC16d"]]

    for InputFlag in InputFlags:
        for name, dsid_list in SampleDict.items():
            #print name, dsid_list
            MergeHistos(InputFolder, dsid_list, name, InputFlag)
            
