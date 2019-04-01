#! /usr/bin/python

import os,sys

os.system("mkdir -p TemplatePlots")

InputFolderParam = "../../Rel21_AnalysisTop_21.2.38_MTOP/run/combfit_output/"
InputFolderHists = "../../Rel21_AnalysisTop_21.2.38_MTOP/run/InputFiles_Parametrisation_21.2.38_V2/"

File1 = InputFolderHists+"/Files_2015_16_100_100/Merge_ttbar_171_MC16a.root"
File2 = InputFolderHists+"/Files_2015_16_100_100/Merge_ttbar_MC16a.root"
File3 = InputFolderHists+"/Files_2015_16_100_100/Merge_ttbar_174_MC16a.root"

#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_mtop_param TemplatePlots "+File1+" "+File2+" "+File3+" mtop -b")
#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_mw_orig TemplatePlots "+File1+" "+File2+" "+File3+" mtop -b")
#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_rbq_orig TemplatePlots "+File1+" "+File2+" "+File3+" mtop -b")

File1 = InputFolderHists+"/Files_2015_16_098_100/Merge_ttbar_MC16a.root"
File2 = InputFolderHists+"/Files_2015_16_100_100/Merge_ttbar_MC16a.root"
File3 = InputFolderHists+"/Files_2015_16_102_100/Merge_ttbar_MC16a.root"

#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_mtop_param TemplatePlots "+File1+" "+File2+" "+File3+" JSF -b")
#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_mw_orig TemplatePlots "+File1+" "+File2+" "+File3+" JSF -b")
#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_rbq_orig TemplatePlots "+File1+" "+File2+" "+File3+" JSF -b")

File1 = InputFolderHists+"/Files_2015_16_100_098/Merge_ttbar_MC16a.root"
File2 = InputFolderHists+"/Files_2015_16_100_100/Merge_ttbar_MC16a.root"
File3 = InputFolderHists+"/Files_2015_16_100_102/Merge_ttbar_MC16a.root"

#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_mtop_param TemplatePlots "+File1+" "+File2+" "+File3+" bJSF -b")
#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_mw_orig TemplatePlots "+File1+" "+File2+" "+File3+" bJSF -b")
#os.system("python PlotTemplateFunctions.py "+InputFolderParam+" h_rbq_orig TemplatePlots "+File1+" "+File2+" "+File3+" bJSF -b")

InputFolderParam = "../InputParamBen/"
InputFolderHists = "../InputParamBen/"

File1 = InputFolderHists+"/Merge_ttbar_171_MC16a.root"
File2 = InputFolderHists+"/Merge_ttbar_MC16a.root"
File3 = InputFolderHists+"/Merge_ttbar_174_MC16a.root"

os.system("python PlotTemplateFunctions_Dil.py "+InputFolderParam+" h_mlb TemplatePlots "+File1+" "+File2+" "+File3+" mtop -b")
