#! /usr/bin/python                                                                                                                                                                      

import os,sys
import glob
import BDTSuperScript

InputFolder  = sys.argv[1]
OutputFolder = sys.argv[2]

#InputFolder  = "../../../../Downloads_21.2.58/Files_SYSLJ_FS/user.aknue.410659.PhPy8EG.DAOD_TOPQ1.e6671_s3126_r9364_p3629.21258_V1_SYSLJ_output.root/"
#OutputFolder = "../../../../Downloads_21.2.58_withBDT/Files_SYSLJ_FS/user.aknue.410659.PhPy8EG.DAOD_TOPQ1.e6671_s3126_r9364_p3629.21258_V1_SYSLJ_output.root/"

BDTSuperScript.ApplyDNN(InputFolder, OutputFolder)

