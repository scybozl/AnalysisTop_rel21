#! /usr/bin/python

def ReturnTTbarList_Mass(Mass):

    if Mass == 169:
        return ["411044", "411052"]
    elif Mass == 171:
        return ["411045", "411053"]
    elif Mass == 172:
        return ["411046", "411054"]
    elif Mass == 172.25:
        return ["411047", "411055"]
    elif Mass == 172.75:
        return ["411048", "411056"]
    elif Mass == 173:
        return ["411049", "411057"]
    elif Mass == 174:
        return ["411050", "411058"]
    elif Mass == 176:
        return ["411051", "411059"]
    

def ReturnTTbarList(Flag):
    
    PowhegPy8List = ["410470"]

    PowhegPy8List_Rad = ["410480", "410482"]

    PowhegPy8List_dil = ["410472"]

    PowhegPy6List = ["410000"]

    PowhegH7List = ["410557", "410558"]

    aMCatNLOList = ["410464", "410465"]
    
    SherpaList = ["410250", "410251", "410252"]

    if Flag == "H7":
        return PowhegH7List
    elif Flag == "Sherpa":
        return SherpaList
    elif Flag == "PP6":
        return PowhegPy6List
    elif Flag == "aMC":
        return aMCatNLOList
    elif Flag == "PP8_Rad":
        return PowhegPy8List_Rad
    elif Flag == "PP8_dil":
        return PowhegPy8List_dil
    else:
        return PowhegPy8List


def ReturnSingleTopList_PP8(Mass):

    if Mass == 169:
        return ["411091", "411092", "411107", "411108", "410644", "410645", "410560", "410408"]
    elif Mass == 171:
        return ["411093", "411094", "411109", "411110", "410644", "410645", "410560", "410408"]
    elif Mass == 172:
        return ["411095", "411096", "411111", "411112", "410644", "410645", "410560", "410408"]
    elif Mass == 172.25:
        return ["411097", "411098", "411113", "411114", "410644", "410645", "410560", "410408"]
    elif Mass == 172.5:
        return ["410658", "410659", "410646", "410647", "410644", "410645", "410560", "410408"]
    elif Mass == 172.75:
        return ["411099", "411100", "411115", "411116", "410644", "410645", "410560", "410408"]
    elif Mass == 173:
        return ["411101", "411102", "411117", "411118", "410644", "410645", "410560", "410408"]
    elif Mass == 174:
        return ["411103", "411104", "411119", "411120", "410644", "410645", "410560", "410408"]
    elif Mass == 176:
        return ["411105", "411106", "411121", "411122", "410644", "410645", "410560", "410408"]


def ReturnSingleTopList_PH7():
    
    return ["411032", "411033", "411036", "411037", "411034", "411035", "410560", "410408"] # the last two processes are tZ and tWZ, so I will not change them

def ReturnSingleTopList_DS():
    return ["410658", "410659", "410654", "410655", "410644", "410645", "410560", "410408"]


# keep in mind for later
#mc16_13TeV.412004.aMcAtNloPy8EG_tchan_NLO.deriv.DAOD_TOPQ1.e6888_a875_r9364_p3629
#mc16_13TeV.412002.aMcAtNloPythia8EvtGen_HThalfscale_tW_inclusive.deriv.DAOD_TOPQ1.e6794_a875_r9364_p3629


def ReturnTTVList():

    # includes also 4 tops
    # keep in mind for systematic variations: 410142, 410143, 410144

    MadgraphList = [
        "410155", "410156", "410157", "410218", "410219", "410220",
        "410276", "410277", "410278", "412045", 
        ]
    
    return MadgraphList


def ReturnDibosonList():

    SherpaList = [
        "364250", "364253", "364254", "364255", "364288", "364289", "364290", "363355", "363356", "363357", 
        "363358", "363359", "363360", "363489", "363494", "364283", "364284", "364285", "364287", "345705", "345706", "345723"
        ]

    return SherpaList

def ReturnZjetsList():
    
    # 60 files

    SherpaList = [
        "364114", "364115", "364116", "364117", "364118", "364119", "364120", "364121", "364122", "364123", "364124", "364125", "364126", "364127", # Zee
        "364128", "364129", "364130", "364131", "364132", "364133", "364134", "364135", "364136", "364137", "364138", "364139", "364140", "364141", # Ztautau        
        "364100", "364101", "364102", "364103", "364104", "364105", "364106", "364107", "364108", "364109", "364110", "364111", "364112", "364113", # Zmumu
        "364198", "364199", "364200", "364201", "364202", "364203", "364204", "364205", "364206", "364207", "364208", "364209", "364210", "364211", 
        "364212", "364213", "364214", "364215"

        # removed the following from list since they are nunu samples: 364142 -- 364155
        #"364142", "364143", "364144", "364145", "364146", "364147", "364148", "364149", "364150", "364151", "364152", "364153", "364154", "364155",

        ]

    return SherpaList


def ReturnWjetsList():

    # 42 files
    
    SherpaList = [
        "364156", "364157", "364158", "364159", 
        "364160", "364161", "364162", "364163", "364164", "364165", "364166", "364167", "364168", "364169",
        "364170", "364171", "364172", "364173", "364174", "364175", "364176", "364177", "364178", "364179",
        "364180", "364181", "364182", "364183", "364184", "364185", "364186", "364187", "364188", "364189",
        "364190", "364191", "364192", "364193", "364194", "364195", "364196", "364197", 
        ]

    return SherpaList



def ReturnTTHList(Generator):

    List16a_aMCatNLO = ["343365", "343366", "343366"]    
    List16a_Powheg   = ["345873", "345874", "345875"]

    if Generator == "aMCatNLO":
        return List16a_aMCatNLO
    else:
        return List16a_Powheg


def ReturnDataList2018():
    DataList = ["grp18"]
    return DataList

def ReturnDataList2017():
    DataList = ["grp17"]
    return DataList

def ReturnDataList2016():
    DataList = ["grp16"]
    return DataList

def ReturnDataList2015():
    DataList = ["grp15"]
    return DataList

def ReturnDataList2015_2016():
    DataList = ["grp15", "grp16"]
    return DataList

#def ReturnDataListAll():
#    DataList = ["data15_13TeV", "data16_13TeV", "data17_13TeV", "data18_13TeV"]
#    return DataList
