#! /usr/bin/python

import os,subprocess
import glob
from DefineSamples import *

SampleDict  = {
    ("ttbar_PH7"):    ReturnTTbarList("H7"),
    ("ttbar_Sherpa"): ReturnTTbarList("Sherpa"),
    ("ttbar_aMC"):    ReturnTTbarList("aMC"),
    ("ttbar_PP8_Rad"):    ReturnTTbarList("PP8_Rad"),
    ("ttbar_PP8"):        ReturnTTbarList("PP8"),
    ("ttbar_PP8_169"):    ReturnTTbarList_Mass(169),
    ("ttbar_PP8_171"):    ReturnTTbarList_Mass(171),
    ("ttbar_PP8_172"):    ReturnTTbarList_Mass(172),
    ("ttbar_PP8_172p25"): ReturnTTbarList_Mass(172.25),
    ("ttbar_PP8_172p75"): ReturnTTbarList_Mass(172.75),
    ("ttbar_PP8_173"):    ReturnTTbarList_Mass(173),
    ("ttbar_PP8_174"):    ReturnTTbarList_Mass(174),
    ("ttbar_PP8_176"):    ReturnTTbarList_Mass(176),
    
    # use only dilepton samples
    ("ttbar_dil_PP8"):        ReturnTTbarList("PP8_dil"),
    ("ttbar_dil_PP8_169"):    [(ReturnTTbarList_Mass(169))[1]],
    ("ttbar_dil_PP8_171"):    [(ReturnTTbarList_Mass(171))[1]],
    ("ttbar_dil_PP8_172"):    [(ReturnTTbarList_Mass(172))[1]],
    ("ttbar_dil_PP8_172p25"): [(ReturnTTbarList_Mass(172.25))[1]],
    ("ttbar_dil_PP8_172p75"): [(ReturnTTbarList_Mass(172.75))[1]],
    ("ttbar_dil_PP8_173"):    [(ReturnTTbarList_Mass(173))[1]],
    ("ttbar_dil_PP8_174"):    [(ReturnTTbarList_Mass(174))[1]],
    ("ttbar_dil_PP8_176"):    [(ReturnTTbarList_Mass(176))[1]],

    ("ST_PP8"):        ReturnSingleTopList_PP8(172.5),
    ("ST_PP8_169"):    ReturnSingleTopList_PP8(169),
    ("ST_PP8_171"):    ReturnSingleTopList_PP8(171),
    ("ST_PP8_172"):    ReturnSingleTopList_PP8(172),
    ("ST_PP8_172.25"): ReturnSingleTopList_PP8(172.25),
    ("ST_PP8_172.75"): ReturnSingleTopList_PP8(172.75),
    ("ST_PP8_173"):    ReturnSingleTopList_PP8(173),
    ("ST_PP8_174"):    ReturnSingleTopList_PP8(174),
    ("ST_PP8_176"):    ReturnSingleTopList_PP8(176),

    # merge all signal samples
    ("Signal_PP8"):        ReturnTTbarList("PP8")+ReturnSingleTopList_PP8(172.5),
    ("Signal_PP8_169"):    ReturnTTbarList_Mass(169)+ReturnSingleTopList_PP8(169.0),
    ("Signal_PP8_171"):    ReturnTTbarList_Mass(171)+ReturnSingleTopList_PP8(171.0),
    ("Signal_PP8_172"):    ReturnTTbarList_Mass(172)+ReturnSingleTopList_PP8(172.0),
    ("Signal_PP8_172p25"): ReturnTTbarList_Mass(172.25)+ReturnSingleTopList_PP8(172.25),
    ("Signal_PP8_172p75"): ReturnTTbarList_Mass(172.75)+ReturnSingleTopList_PP8(172.75),
    ("Signal_PP8_173"):    ReturnTTbarList_Mass(173)+ReturnSingleTopList_PP8(173.0),
    ("Signal_PP8_174"):    ReturnTTbarList_Mass(174)+ReturnSingleTopList_PP8(174.0),
    ("Signal_PP8_176"):    ReturnTTbarList_Mass(176)+ReturnSingleTopList_PP8(176.0),

    ("TTV_Madgraph"): ReturnTTVList(),
    ("Dibos_Sherpa"): ReturnDibosonList(),
    ("Wjets_Sherpa"): ReturnWjetsList(),
    ("Zjets_Sherpa"): ReturnZjetsList(), 
    ("TTH_aMCatNLO"): ReturnTTHList("aMCatNLO"),
    ("TTH_Powheg"):   ReturnTTHList("Powheg"),

    ("data2015_16"): ReturnDataList2015_2016(),
    ("data2017"): ReturnDataList2017(),
    ("data2015_16_17"): ReturnDataList2015_2016()+ReturnDataList2017(),
    # (""): [],

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
               
               ("lepjets_2017",  "MC16d"): [("ejets_2017", "mujets_2017"), "lepton+jets", "2017", "lepjets"],
               ("lepjets_2016",  "MC16a"): [("ejets_2016", "mujets_2016"), "lepton+jets", "2016", "lepjets"],
               ("lepjets_2015",  "MC16a"): [("ejets_2015", "mujets_2015"), "lepton+jets", "2015", "lepjets"],
               ("ejets_2017",    "MC16d"): [("ejets_2017",),  "e+jets",   "2017", "lepjets"],
               ("mujets_2017",   "MC16d"): [("mujets_2017",), "#mu+jets", "2017", "lepjets"],
               ("dilepton_2017", "MC16d"): [("ee_2017", "emu_2017", "mumu_2017"), "dilepton", "2017", "dilepton"],
               ("ee_2017",       "MC16d"): [("ee_2017",),   "ee",     "2017", "dilepton"],
               ("emu_2017",      "MC16d"): [("emu_2017",),  "e#mu",   "2017", "dilepton"],
               ("mumu_2017",     "MC16d"): [("mumu_2017",), "#mu#mu", "2017", "dilepton"],

               ("lepjets_2015_16",  "MC15"): [("ejets_2015",   "ejets_2016", "mujets_2015", "mujets_2016"), "lepton+jets", "2015+2016", "lepjets"],

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

