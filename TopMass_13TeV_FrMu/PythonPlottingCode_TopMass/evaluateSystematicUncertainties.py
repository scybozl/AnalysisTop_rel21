#! /usr/bin/python

import os
import sys
import glob
import math

import PlottingMaster
sys.path.append('SortingScripts')
from ListSystematics import *


# here you have to specify in which folder you stored the output of all your pseudo-experiments, the dimension of the fit, and the number of PEXP
PEFolder      = "/ptmp/mpp/knand/TopMass_13TeV/Rel21_AnalysisTop_21.2.51_MTOP/run_51/OutputTest_V2/"
OutputFolder  = "/ptmp/mpp/knand/TopMass_13TeV/Rel21_AnalysisTop_21.2.51_MTOP/run_51/OutputFolder_PE_Syst_Plots/"
OutputFileAF2 = "/ptmp/mpp/knand/TopMass_13TeV/Rel21_AnalysisTop_21.2.51_MTOP/run_51/OutputTest/"
Dimension     = [2]
Nr_PEXP       = 1
TreeName      = "PETree"
Parameters    = "mtop"

Flag = str(Nr_PEXP)+"PE_"+str(Dimension)+"D"

os.system("mkdir -p "+OutputFolder)

# ok, now the idea of this code is to read the trees that we get as output of the pseudo-experiments and check the shifts in the top mass
# in the future, I also want the original histograms for the observables stored in those output files, so that we can make simple
# shape comparisons as well as overlay the distributions with the functions from the template fit
# -> these checks will be useful to see how flexible the fit really is, as it has been shown in the 8 TeV code, that for some observables
#    the functions were a bit stiff. 
# we also stored the total event yields, which will be used in the following to check the shifts in the normalisation, which can be
# useful to see if something went wrong already before the pseudo-experiments were run
# in the end we need also some scripts that make html pages, so that we can make the output more accessible and get a more systematic overview

# still to do:
#  * evaluate correlations between samples -> need to store more information for this in PE trees (event number, run number)
#  * evaluate statistical uncertainty on systematics
#  * make seperate systematic tables for b-tagging, JES, etc
#  * make shape comparisons from histograms -> need to store more information for this in PE trees 
#  * read in parametrisation functions and overlay the histograms 
#  * we should also store the SystematicName in the Output file from the PE -> the earlier, the better

# call the systematics by class

def ReturnUncertainty(entry, OutputFolder, Flag):
    if len(entry) == 4 or len(entry) == 3:
        FileUp   = PEFolder+"/"+entry[1]+"_"+Flag+".root"
        FileDown = PEFolder+"/"+entry[2]+"_"+Flag+".root"
        FileNom  = PEFolder+"/nominal_"+Flag+".root" 
        Uncertainty = PlottingMaster.EvaluateTrees_TwoSided(FileUp, FileDown, FileNom, TreeName, Parameters, entry[0], OutputFolder, Flag)
        return Uncertainty
    if len(entry) == 2:
        FileUp   = PEFolder+"/"+entry[1]+"_"+Flag+".root"
        FileNom  = PEFolder+"/nominal_"+Flag+".root"
        Uncertainty = PlottingMaster.EvaluateTrees_OneSided(FileUp, FileNom, TreeName, Parameters, entry[0], OutputFolder, Flag)
        return Uncertainty

    return "bla"
        

def GetTotalUncertainty(List):
    # just do a simple quadratic sum now
    Unc = 0
    for entry in List:
        Unc += entry[1]*entry[1]

    return math.sqrt(Unc)

for Dim in Dimension:
    Flag     = str(Nr_PEXP)+"PE_"+str(Dim)+"D"
    FlagStat = "1PE_"+str(Dim)+"D"

    BTagUnc     = []
    CTagUnc     = []
    MTagUnc     = []
    TagExtraUnc = []
    TagUnc      = [] # for all three tagging categories listed above
    LeptonUnc   = []
    JVTUnc      = []
    PileupUnc   = []
    JES_noBUnc  = []
    BJESUnc     = []
    JERUnc      = []
    METUnc      = []
    RadiationUnc     = []
    GeneratorUnc     = []
    HadronisationUnc = []

    TotalUnc  = []
    
    # start with the b-tagging uncertainties
    BTagList       = ReturnBtagSFList()
    CTagList       = ReturnCtagSFList()
    MTagList       = ReturnMistagSFList()
    TagExtraList   = ReturnTagExtrapolationList()
    LepSFList      = ReturnLeptonSFList()
    JVTList        = ReturnJVTList()
    PileupList     = ReturnPileupList()
    LeptonResList  = ReturnLeptonResList()
    JESList_noBJES = ReturnJESList_noBJES()
    BJESList       = ReturnBJESList()
    JERList        = ReturnJERList()
    METList        = ReturnMETList()
    RadiationList  = ReturnRadiationSyst()
    GeneratorList  = ReturnGeneratorSyst()
    HadronisationList = ReturnHadronisationSyst()

    StatUnc = PlottingMaster.ReturnStatUncertainty(FlagStat, Parameters, PEFolder)
    TotalUnc.append(["Statistical", StatUnc])

    for entry in GeneratorList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        GeneratorUnc.append([entry[0], Unc])

    TotalGen  = GetTotalUncertainty(GeneratorUnc)
    TotalUnc.append(["ME Generator", TotalGen])
    
    for entry in HadronisationList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        HadronisationUnc.append([entry[0], Unc])

    TotalHad  = GetTotalUncertainty(HadronisationUnc)
    TotalUnc.append(["Hadronisation", TotalHad])

    for entry in RadiationList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        RadiationUnc.append([entry[0], Unc])

    TotalRad  = GetTotalUncertainty(RadiationUnc)
    TotalUnc.append(["ISR/FSR", TotalRad])

    for entry in JESList_noBJES:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        JES_noBUnc.append([entry[0], Unc])

    TotalJES_noB = GetTotalUncertainty(JES_noBUnc)
    TotalUnc.append(["JES (without bJES)", TotalJES_noB])
    PlottingMaster.MakeSystematicTable(Parameters, Dim, OutputFolder, "JES_noBJES", JES_noBUnc)
    

    for entry in BJESList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        BJESUnc.append([entry[0], Unc])

    TotalBJES = GetTotalUncertainty(BJESUnc)
    TotalUnc.append(["bJES", TotalBJES])

    for entry in JERList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        JERUnc.append([entry[0], Unc])

    TotalJER = GetTotalUncertainty(JERUnc)
    TotalUnc.append(["JER", TotalJER])

    for entry in JVTList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        JVTUnc.append([entry[0], Unc])
        
    TotalJVT = GetTotalUncertainty(JVTUnc)
    TotalUnc.append(["JVT", TotalJVT])

    for entry in BTagList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        BTagUnc.append([entry[0], Unc])
        TagUnc.append([entry[0], Unc])

    for entry in CTagList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        CTagUnc.append([entry[0], Unc])
        TagUnc.append([entry[0], Unc])

    for entry in MTagList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        MTagUnc.append([entry[0], Unc])
        TagUnc.append([entry[0], Unc])
    
    for entry in TagExtraList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        TagExtraUnc.append([entry[0], Unc])
        TagUnc.append([entry[0], Unc])
                        
    TotalBTag     = GetTotalUncertainty(BTagUnc)
    TotalCTag     = GetTotalUncertainty(CTagUnc)
    TotalMTag     = GetTotalUncertainty(MTagUnc)
    TotalTagExtra = GetTotalUncertainty(TagExtraUnc)
    TotalTag      = GetTotalUncertainty(TagUnc)

    TotalUnc.append(["Btagging", TotalTag])
    
    # now add the lepton SF uncertainties
    for entry in LepSFList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        LeptonUnc.append([entry[0], Unc])

    for entry in LeptonResList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        LeptonUnc.append([entry[0], Unc])

    TotalLepton = GetTotalUncertainty(LeptonUnc)
    TotalUnc.append(["Lepton", TotalLepton])

    for entry in METList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        METUnc.append([entry[0], Unc])

    TotalMET = GetTotalUncertainty(METUnc)
    TotalUnc.append(["MET", TotalMET])
        
    for entry in PileupList:
        Unc = ReturnUncertainty(entry, OutputFolder, Flag)
        PileupUnc.append([entry[0], Unc])

    TotalPileup = GetTotalUncertainty(PileupUnc)
    TotalUnc.append(["Pileup", TotalPileup])

    print "\n \n \n"
    print "####################################################################"
    print "####################################################################"
    print "############################# RESULTS ##############################"
    print "####################################################################"
    print "####################################################################"
        
    
    outfile = open(OutputFolder+"/Uncertainties_"+str(Dim)+"D_mtop.tex", "w")
    outfile.write("\\begin{table}   \n")
    outfile.write("\\begin{tabular}{|l|r|}  \n")
    outfile.write("\hline   \n")
    if Parameters == "mtop":
        outfile.write("Uncertainty & $\Delta m_{top}$ [GeV] & \\\\ \n")
    if Parameters == "jsf":
        outfile.write("Uncertainty & $\Delta$ JSF & \\\\ \n")
    if Parameters == "bjsf":
        outfile.write("Uncertainty & $\Delta$ bJSF & \\\\ \n")
    outfile.write("\hline   \n")

    for entry in TotalUnc:
        
        print entry[0],"  ",round(entry[1], 3)
        
        outfile.write(entry[0]+" & "+str(round(entry[1], 2))+" \\\\ \n")
        if "ISR" in entry[0] or "Pileup" in entry[0] or "Statistical" in entry[0]:
            outfile.write("\hline   \n")
            
        
    TotalUnc = GetTotalUncertainty(TotalUnc)
    SystUnc  = math.sqrt(TotalUnc*TotalUnc - StatUnc*StatUnc)

    outfile.write("Total systematic uncertainty & "+str(round(SystUnc, 2))+" \\\\ \n")
    outfile.write("Total & "+str(round(TotalUnc, 2))+" \\\\ \n")

    print "Total Unc = ",round(TotalUnc, 2)

    outfile.write("\hline  \n")
    outfile.write("\end{tabular} \n")
    outfile.write("\end{table}")
    outfile.close()
