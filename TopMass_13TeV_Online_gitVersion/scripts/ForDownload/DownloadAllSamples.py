#! /usr/bin/python

import os,sys

fLocal = os.getcwd()

DL_List = []
DL_List.append(["Files_NOM_FS/",           "s3126*21258_V1_output.root"])
DL_List.append(["Files_NOM_AF/",           "a87*21258_V1_output.root"])
DL_List.append(["Files_TMPL_AF_100_098/",  "21258_V1_TMPL_output_100_098_root"])
DL_List.append(["Files_TMPL_AF_100_099/",  "21258_V1_TMPL_output_100_099_root"])
DL_List.append(["Files_TMPL_AF_100_0995/", "21258_V1_TMPL_output_100_0995_root"])
DL_List.append(["Files_TMPL_AF_100_100/",  "21258_V1_TMPL_output_100_100_root"])
DL_List.append(["Files_TMPL_AF_100_1005/", "21258_V1_TMPL_output_100_1005_root"])
DL_List.append(["Files_TMPL_AF_100_101/",  "21258_V1_TMPL_output_100_101_root"])
DL_List.append(["Files_TMPL_AF_100_102/",  "21258_V1_TMPL_output_100_102_root"])
DL_List.append(["Files_TMPL_AF_098_100/",  "21258_V1_TMPL_output_098_100_root"])
DL_List.append(["Files_TMPL_AF_099_100/",  "21258_V1_TMPL_output_099_100_root"])
DL_List.append(["Files_TMPL_AF_0995_100/", "21258_V1_TMPL_output_0995_100_root"])
DL_List.append(["Files_TMPL_AF_1005_100/", "21258_V1_TMPL_output_1005_100_root"])
DL_List.append(["Files_TMPL_AF_101_100/",  "21258_V1_TMPL_output_101_100_root"])
DL_List.append(["Files_TMPL_AF_102_100/",  "21258_V1_TMPL_output_102_100_root"])
DL_List.append(["Files_SYSLJ_FS/",         "s3126_r9364_p3629.21258_V1_SYSLJ_output.root"])
#DL_List.append(["Files_SYSDIL_FS/",        "s3126_r9364_p3629.21258_V1_SYSDIL_output.root"])
DL_List.append(["Files_SYSLJ_oldQG_FS/",   "s3126_r9364_p3629.21258_V1_SYSLJ_oldQG_output.root"])
DL_List.append(["Files_SYSLJ_BTAG_FS/",    "s3126_r9364_p3629.21258_V1_SYSLJ_BTAG_output.root"])


for entry in DL_List:
    DIR     = entry[0]
    Pattern = entry[1]
    os.system("mkdir -p "+DIR)
    #os.system("ls "+DIR)
    print "=================================================================================================================="
    print DIR
    os.system("cd "+DIR+"; pwd; "+"rucio download user.aknue.*"+Pattern+" ; cd "+fLocal)
    


#rucio download "user.aknue.*s3126*21258_V1_output.root"
