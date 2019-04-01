#! /usr/bin/python

import os,subprocess
import glob
from DefineSamples import *


SampleDict  = {           # List, RunNominal, RunTemplate, RunSYSTDil, RunSYSTLjets, Test                                                                                                                   
    ("ttbar_PH7"):        [ReturnTTbarList("H7"),        True,  False,  False,  False,  False],
    ("ttbar_Sherpa"):     [ReturnTTbarList("Sherpa"),    True,  False,  False,  False,  False],
    ("ttbar_aMCPy8"):     [ReturnTTbarList("aMC"),       True,  False,  False,  False,  False],
    ("ttbar_PP8_Rad"):    [ReturnTTbarList("PP8_Rad"),   True,  False,  False,  False,  False],
    ("ttbar_PP8"):        [ReturnTTbarList("PP8"),       True,  True,   True,   True,   True],
    ("ttbar_PP8_169"):    [ReturnTTbarList_Mass(169),    True,  False,  False,  False,  False],
    ("ttbar_PP8_171"):    [ReturnTTbarList_Mass(171),    True,  False,  False,  False,  False],
    ("ttbar_PP8_172"):    [ReturnTTbarList_Mass(172),    True,  False,  False,  False,  False],
    ("ttbar_PP8_172p25"): [ReturnTTbarList_Mass(172.25), True,  False,  False,  False,  False],
    ("ttbar_PP8_172p75"): [ReturnTTbarList_Mass(172.75), True,  False,  False,  False,  False],
    ("ttbar_PP8_173"):    [ReturnTTbarList_Mass(173),    True,  False,  False,  False,  False],
    ("ttbar_PP8_174"):    [ReturnTTbarList_Mass(174),    True,  False,  False,  False,  False],
    ("ttbar_PP8_176"):    [ReturnTTbarList_Mass(176),    True,  False,  False,  False,  False],

    # use only dilepton samples                                                                                                                                                                           
    ("ttbar_dil_PP8"):        [ReturnTTbarList("PP8_dil"),          True,  False,   True,  False,  False],
    ("ttbar_dil_PP8_169"):    [[(ReturnTTbarList_Mass(169))[1]],    True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_171"):    [[(ReturnTTbarList_Mass(171))[1]],    True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_172"):    [[(ReturnTTbarList_Mass(172))[1]],    True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_172p25"): [[(ReturnTTbarList_Mass(172.25))[1]], True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_172p75"): [[(ReturnTTbarList_Mass(172.75))[1]], True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_173"):    [[(ReturnTTbarList_Mass(173))[1]],    True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_174"):    [[(ReturnTTbarList_Mass(174))[1]],    True,  False,  False,  False,  False],                                                                                                 
    ("ttbar_dil_PP8_176"):    [[(ReturnTTbarList_Mass(176))[1]],    True,  False,  False,  False,  False],                                                                                                 

    ("ST_PP8"):        [ReturnSingleTopList_PP8(172.5),  True,  True,   True,   True,   False],
    ("ST_PP8_169"):    [ReturnSingleTopList_PP8(169),    True,  False,  False,  False,  False],
    ("ST_PP8_171"):    [ReturnSingleTopList_PP8(171),    True,  False,  False,  False,  False],
    ("ST_PP8_172"):    [ReturnSingleTopList_PP8(172),    True,  False,  False,  False,  False],
    ("ST_PP8_172p25"): [ReturnSingleTopList_PP8(172.25), True,  False,  False,  False,  False],
    ("ST_PP8_172p75"): [ReturnSingleTopList_PP8(172.75), True,  False,  False,  False,  False],
    ("ST_PP8_173"):    [ReturnSingleTopList_PP8(173),    True,  False,  False,  False,  False],
    ("ST_PP8_174"):    [ReturnSingleTopList_PP8(174),    True,  False,  False,  False,  False],
    ("ST_PP8_176"):    [ReturnSingleTopList_PP8(176),    True,  False,  False,  False,  False],
    ("ST_PH7"):        [ReturnSingleTopList_PH7(),       True,  False,  False,  False,  False],
    ("ST_PP8_DS"):     [ReturnSingleTopList_DS(),        True,  False,  False,  False,  False],

    # for now do not run systematics or templates for the backgrounds                                                                                                                                     
    ("TTV_Madgraph"): [ReturnTTVList(),           True,  False,  False,  False,  False],
    ("Dibos_Sherpa"): [ReturnDibosonList(),       True,  False,  False,  False,  False],
    ("Wjets_Sherpa"): [ReturnWjetsList(),         True,  False,  False,  False,  False],
    ("Zjets_Sherpa"): [ReturnZjetsList(),         True,  False,  False,  False,  False],
    #("TTH_aMCatNLO"): [ReturnTTHList("aMCatNLO"), True,  False,  False,  False,  False],                                                                                                                
   
    ("TTH_Powheg"):   [ReturnTTHList("Powheg"),   True,  False,  False,  False,  False],

    ("data_2015"):    [ReturnDataList2015(),      True,  False,  False,  False,  False],
    ("data_2016"):    [ReturnDataList2016(),      True,  False,  False,  False,  False],
    ("data_2017"):    [ReturnDataList2017(),      True,  False,  False,  False,  False],
    ("data_2018"):    [ReturnDataList2018(),      True,  False,  False,  False,  False],

    ("data_2015_16"):    [ReturnDataList2015_2016(), True,  False,  False,  False,  False],


    }




ChannelDict = {("lepjets_2015_16",  "MC16a"): [("ejets_2015",   "ejets_2016", "mujets_2015", "mujets_2016"), "lepton+jets", "2015+2016", "lepjets"],
               ("ejets_2015_16",    "MC16a"): [("ejets_2015",   "ejets_2016"),  "e+jets",   "2015+2016", "lepjets"],
               ("mujets_2015_16",   "MC16a"): [("mujets_2015",  "mujets_2016"), "#mu+jets", "2015+2016", "lepjets"],
               ("ejets_2015",       "MC16a"): [("ejets_2015",),  "e+jets",   "2015", "lepjets"],
               ("mujets_2015",      "MC16a"): [("mujets_2015",), "#mu+jets", "2015", "lepjets"],
               ("ejets_2016",       "MC16a"): [("ejets_2016",),  "e+jets",   "2016", "lepjets"],
               ("mujets_2016",      "MC16a"): [("mujets_2016",), "#mu+jets", "2016", "lepjets"],
               ("dilepton_2015_16", "MC16a"): [("ee_2015", "ee_2016", "emu_2015", "emu_2016", "mumu_2015", "mumu_2016"), "dilepton", "2015+2016", "dilepton"],
               ("dilepton_2015",    "MC16a"): [("ee_2015", "emu_2015", "mumu_2015"), "dilepton", "2015", "dilepton"],
               ("dilepton_2016",    "MC16a"): [("ee_2016", "emu_2016", "mumu_2016"), "dilepton", "2016", "dilepton"],
               ("ee_2015_16",       "MC16a"): [("ee_2015", "ee_2016"),     "ee",     "2015+2016", "dilepton"],
               ("emu_2015_16",      "MC16a"): [("emu_2015", "emu_2016"),   "e#mu",   "2015+2016", "dilepton"],
               ("mumu_2015_16",     "MC16a"): [("mumu_2015", "mumu_2016"), "#mu#mu", "2015+2016", "dilepton"],
               ("ee_2015",     "MC16a"): [("ee_2015",),   "ee",     "2015", "dilepton"],
               ("emu_2015",    "MC16a"): [("emu_2015",),  "e#mu",   "2015", "dilepton"],
               ("mumu_2015",   "MC16a"): [("mumu_2015",), "#mu#mu", "2015", "dilepton"],
               ("ee_2016",     "MC16a"): [("ee_2016",),   "ee",     "2016", "dilepton"],
               ("emu_2016",    "MC16a"): [("emu_2016",),  "e#mu",   "2016", "dilepton"],
               ("mumu_2016",   "MC16a"): [("mumu_2016",), "#mu#mu", "2016", "dilepton"],
               
               ("lepjets_2018",  "MC16e"): [("ejets_2018", "mujets_2018"), "lepton+jets", "2018", "lepjets"],
               ("lepjets_2017",  "MC16d"): [("ejets_2017", "mujets_2017"), "lepton+jets", "2017", "lepjets"],
               ("lepjets_2016",  "MC16a"): [("ejets_2016", "mujets_2016"), "lepton+jets", "2016", "lepjets"],
               ("lepjets_2015",  "MC16a"): [("ejets_2015", "mujets_2015"), "lepton+jets", "2015", "lepjets"],
               

               ("ejets_2017",    "MC16d"): [("ejets_2017",),  "e+jets",   "2017", "lepjets"],
               ("mujets_2017",   "MC16d"): [("mujets_2017",), "#mu+jets", "2017", "lepjets"],
               ("dilepton_2017", "MC16d"): [("ee_2017", "emu_2017", "mumu_2017"), "dilepton", "2017", "dilepton"],
               ("ee_2017",       "MC16d"): [("ee_2017",),   "ee",     "2017", "dilepton"],
               ("emu_2017",      "MC16d"): [("emu_2017",),  "e#mu",   "2017", "dilepton"],
               ("mumu_2017",     "MC16d"): [("mumu_2017",), "#mu#mu", "2017", "dilepton"],

               ("ejets_2018",    "MC16d"): [("ejets_2018",),  "e+jets",   "2018", "lepjets"],
               ("mujets_2018",   "MC16d"): [("mujets_2018",), "#mu+jets", "2018", "lepjets"],
               ("dilepton_2018", "MC16d"): [("ee_2018", "emu_2018", "mumu_2018"), "dilepton", "2018", "dilepton"],
               ("ee_2018",       "MC16d"): [("ee_2018",),   "ee",     "2018", "dilepton"],
               ("emu_2018",      "MC16d"): [("emu_2018",),  "e#mu",   "2018", "dilepton"],
               ("mumu_2018",     "MC16d"): [("mumu_2018",), "#mu#mu", "2018", "dilepton"],

               }



def ReturnChannelList(Flag, DataMCFlag):
    return ChannelDict[Flag, DataMCFlag][0]

def ReturnChannelLabel(Flag, DataMCFlag):
    return ChannelDict[Flag, DataMCFlag][1]

def ReturnYearLabel(Flag, DataMCFlag):
    return ChannelDict[Flag, DataMCFlag][2]

def ReturnVariableFlag(Flag, DataMCFlag):
    return ChannelDict[Flag, DataMCFlag][3]

#print ChannelDict["lepjets", "MC16a"]
#print ChannelDict["lepjets", "MC16a"][1]

