#! /usr/bin/python

import os,subprocess
import glob
from DefineSamples import *

SampleDict  = {           # List, RunNominal, RunTemplate, RunSYSTDil, RunSYSTLjets, Test  
    ("ttbar_PH7"):        [ReturnTTbarList("H7"),        True,  False,  False,  False,  False],
    ("ttbar_Sherpa"):     [ReturnTTbarList("Sherpa"),    True,  False,  False,  False,  False],
    ("ttbar_aMC"):        [ReturnTTbarList("aMC"),       True,  False,  False,  False,  False],
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
    #("ttbar_dil_PP8_169"):    [[(ReturnTTbarList_Mass(169))[1]],    True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_171"):    [[(ReturnTTbarList_Mass(171))[1]],    True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_172"):    [[(ReturnTTbarList_Mass(172))[1]],    True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_172p25"): [[(ReturnTTbarList_Mass(172.25))[1]], True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_172p75"): [[(ReturnTTbarList_Mass(172.75))[1]], True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_173"):    [[(ReturnTTbarList_Mass(173))[1]],    True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_174"):    [[(ReturnTTbarList_Mass(174))[1]],    True,  False,  False,  False,  False],
    #("ttbar_dil_PP8_176"):    [[(ReturnTTbarList_Mass(176))[1]],    True,  False,  False,  False,  False],

    ("ST_PP8"):        [ReturnSingleTopList_PP8(172.5),  True,  True,   True,   True,   False],
    ("ST_PP8_169"):    [ReturnSingleTopList_PP8(169),    True,  False,  False,  False,  False],
    ("ST_PP8_171"):    [ReturnSingleTopList_PP8(171),    True,  False,  False,  False,  False],
    ("ST_PP8_172"):    [ReturnSingleTopList_PP8(172),    True,  False,  False,  False,  False],
    ("ST_PP8_172.25"): [ReturnSingleTopList_PP8(172.25), True,  False,  False,  False,  False],
    ("ST_PP8_172.75"): [ReturnSingleTopList_PP8(172.75), True,  False,  False,  False,  False],
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

    }


#ConfigDict = {
#
#    ("MC16a", ):        [,  True,  False,  False,  False,  False],
#    }


#MC16a, Nominal, Templates, SysDil, SysLjets, Test

#AFII oder FS

