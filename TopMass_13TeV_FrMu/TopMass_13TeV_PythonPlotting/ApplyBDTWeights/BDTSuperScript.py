#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
from array import array
from ROOT import TMVA, TFile, TTree, TDirectory

sys.path.append('../SortingScripts')
from ListSystematics import *

# now need list of systematic trees
SystTreeList = ReturnTreeList()

# code needs to be modified as soon as MC16d and e samples are available

ChannelList_MC16a = ["ee_2015", "ejets_2015", "emu_2015", "mujets_2015", "mumu_2015", "ee_2016", "ejets_2016", "emu_2016", "mujets_2016", "mumu_2016"]
ChannelList_MC16d = ["ee_2017", "ejets_2017", "emu_2017", "mujets_2017", "mumu_2017"]
ChannelList_MC16e = ["ee_2018", "ejets_2018", "emu_2018", "mujets_2018", "mumu_2018"]

# apply DNN from Olafs TATORTCleaner
def ApplyDNN(InputFolder, OutputFolder):

    TreeList = ["nominal"]

    if "SYSLJ" in InputFolder:
        TreeList = SystTreeList

    InputFiles = glob.glob(InputFolder+"/*root*")

    for InputFile in InputFiles:
        OutputFile = InputFile.replace(InputFolder, OutputFolder)

        for TreeName in TreeList:
            
            print("---------------------------------------------------------------------------> Running over tree = ",TreeName)
            
            if TreeName == "nominal_SYST":
                continue

            Config1 = "model/dnn_4j_layer_36_128_256_128_64_8_1.json"
            Config2 = "model/dnn_5j_layer_36_60_51_42_33_24_15_1.json"
            
            #os.system("cd TATORTCleaner; ./bin/TATORTCleaner "+Config1+" "+InputFile+" "+TreeName+" "+"DNN_Olaf_4j_layer_36_128_256_128_64_8_1_V2;  cd ../")
            os.system("cd TATORTCleaner; ./bin/TATORTCleaner "+Config2+" "+InputFile+" "+TreeName+" "+"DNN_Olaf_5j_layer_36_60_51_42_33_24_15_1_V2; cd ../")

        os.system("mv "+InputFile+" "+OutputFile)
            

def ApplyAddCuts(InputFolder, OutputFolder, Campaign):

    ChannelList = ChannelList_MC16a

    if Campaign == "MC16d":
        ChannelList = ChannelList_MC16d
    if Campaign == "MC16e":
        ChannelList = ChannelList_MC16e

    TreeList = ["nominal"]
    
    if "SYSLJ" in InputFolder:
        TreeList = SystTreeList

    InputFiles = glob.glob(InputFolder+"/*root*")

    for InputFile in InputFiles:

        OutputFile = InputFile.replace(InputFolder, OutputFolder)

        if os.path.exists(OutputFile):
            continue

        fF        = TFile(InputFile, "READ")


        fF_out = TFile(OutputFile, "RECREATE")

        # save sumWeights tree to new file
        fT_weight = fF.Get("sumWeights")
        fT_weight_out = fT_weight.CloneTree()

        fT_weight_out.Write()

        # save all bookkeeping histograms to new file
        for Channel in ChannelList:

            DIR = TDirectory()
            fF.GetObject(Channel, DIR)
            DIR.ReadAll()
            fF_out.mkdir(Channel)
            fF_out.cd(Channel)
            DIR_new = TDirectory()
            DIR.GetList().Write()
            DIR_new.Write()
            
            fF_out.cd()


        for TreeName in TreeList:

            print("---------------------------------------------------------------------------> Running over tree = ",TreeName)

            if TreeName == "nominal_SYST":
                continue

            fT      = fF.Get(TreeName)
            entries = fT.GetEntries()
            reader1 = TMVA.Reader()
            reader2 = TMVA.Reader()
            
            var_LL_1      = array('f',[0]) ; reader1.AddVariable("klfitter_logLikelihood[0]",    var_LL_1)
            var_EvtProb_1 = array('f',[0]) ; reader1.AddVariable("klfitter_eventProbability[0]", var_EvtProb_1)
            var_WhadPt_1  = array('f',[0]) ; reader1.AddVariable("klf_orig_Whad_pt",             var_WhadPt_1)
            var_WlepPt_1  = array('f',[0]) ; reader1.AddVariable("klf_orig_Wlep_pt",             var_WlepPt_1)
            var_ThadPt_1  = array('f',[0]) ; reader1.AddVariable("klf_orig_tophad_pt",           var_ThadPt_1)
            var_TlepPt_1  = array('f',[0]) ; reader1.AddVariable("klf_orig_toplep_pt",           var_TlepPt_1)
            var_j_n_1     = array('f',[0]) ; reader1.AddVariable("tma_njets",                    var_j_n_1)
            var_met_1     = array('f',[0]) ; reader1.AddVariable("tma_met",                      var_met_1)
            var_TTbarPt_1 = array('f',[0]) ; reader1.AddVariable("klf_orig_ttbar_pt",            var_TTbarPt_1)
            var_mwt_1     = array('f',[0]) ; reader1.AddVariable("tma_mtw",                      var_mwt_1)
            var_DRwjets_1 = array('f',[0]) ; reader1.AddVariable("klf_orig_dR_qq_W",             var_DRwjets_1)
            var_DRbjets_1 = array('f',[0]) ; reader1.AddVariable("klf_orig_dR_bb",               var_DRbjets_1)
        

            var_LL_2      = array('f',[0]) ; reader2.AddVariable("klfitter_logLikelihood[0]",    var_LL_2)
            var_EvtProb_2 = array('f',[0]) ; reader2.AddVariable("klfitter_eventProbability[0]", var_EvtProb_2)
            var_WhadPt_2  = array('f',[0]) ; reader2.AddVariable("klf_orig_Whad_pt",             var_WhadPt_2)
            var_WlepPt_2  = array('f',[0]) ; reader2.AddVariable("klf_orig_Wlep_pt",             var_WlepPt_2)
            var_ThadPt_2  = array('f',[0]) ; reader2.AddVariable("klf_orig_tophad_pt",           var_ThadPt_2)
            var_TlepPt_2  = array('f',[0]) ; reader2.AddVariable("klf_orig_toplep_pt",           var_TlepPt_2)
            var_j_n_2     = array('f',[0]) ; reader2.AddVariable("tma_njets",                    var_j_n_2)
            var_met_2     = array('f',[0]) ; reader2.AddVariable("tma_met",                      var_met_2)
            var_TTbarPt_2 = array('f',[0]) ; reader2.AddVariable("klf_orig_ttbar_pt",            var_TTbarPt_2)
            var_mwt_2     = array('f',[0]) ; reader2.AddVariable("tma_mtw",                      var_mwt_2)
            var_DRwjets_2 = array('f',[0]) ; reader2.AddVariable("klf_orig_dR_qq_W",             var_DRwjets_2)
            var_DRbjets_2 = array('f',[0]) ; reader2.AddVariable("klf_orig_dR_bb",               var_DRbjets_2)
            
        
            reader1.BookMVA("BDT", "TrainingSteffenChristmas/weights_noWindowCuts/MassTraining_BDT.weights.xml")
            reader2.BookMVA("BDT", "TrainingSteffenChristmas/weights_withWindowCuts/MassTraining_BDT.weights.xml")
            
            fT_out   = fT.CloneTree(0)
            d_noWC   = array( 'f', [0.])
            d_withWC = array( 'f', [0.])
    
            fT_out.Branch("bdtOutput_8TeVlike_noWC",   d_noWC,   'bdtOutput_8TeVlike_noWC/F')
            fT_out.Branch("bdtOutput_8TeVlike_withWC", d_withWC, 'bdtOutput_8TeVlike_withWC/F')
        
            for i in range(0, entries):
                fT.GetEntry(i)

                var_LL_1[0]      = fT.klfitter_logLikelihood[0]
                var_EvtProb_1[0] = fT.klfitter_eventProbability[0]
                var_WhadPt_1[0]  = fT.klf_orig_Whad_pt
                var_WlepPt_1[0]  = fT.klf_orig_Wlep_pt
                var_ThadPt_1[0]  = fT.klf_orig_tophad_pt
                var_TlepPt_1[0]  = fT.klf_orig_toplep_pt
                var_j_n_1[0]     = fT.tma_njets
                var_met_1[0]     = fT.tma_met
                var_TTbarPt_1[0] = fT.klf_orig_ttbar_pt
                var_mwt_1[0]     = fT.tma_mtw
                var_DRwjets_1[0] = fT.klf_orig_dR_qq_W
                var_DRbjets_1[0] = fT.klf_orig_dR_bb
                
                var_LL_2[0]      = fT.klfitter_logLikelihood[0]
                var_EvtProb_2[0] = fT.klfitter_eventProbability[0]
                var_WhadPt_2[0]  = fT.klf_orig_Whad_pt
                var_WlepPt_2[0]  = fT.klf_orig_Wlep_pt
                var_ThadPt_2[0]  = fT.klf_orig_tophad_pt
                var_TlepPt_2[0]  = fT.klf_orig_toplep_pt
                var_j_n_2[0]     = fT.tma_njets
                var_met_2[0]     = fT.tma_met
                var_TTbarPt_2[0] = fT.klf_orig_ttbar_pt
                var_mwt_2[0]     = fT.tma_mtw
                var_DRwjets_2[0] = fT.klf_orig_dR_qq_W
                var_DRbjets_2[0] = fT.klf_orig_dR_bb
                
                d_noWC[0]   = reader1.EvaluateMVA("BDT")
                d_withWC[0] = reader2.EvaluateMVA("BDT")

                #print d_noWC[0],"     ",d_withWC[0]
            
                fT_out.Fill()

            fT_out.Write()
        
        fF_out.Close()
        

