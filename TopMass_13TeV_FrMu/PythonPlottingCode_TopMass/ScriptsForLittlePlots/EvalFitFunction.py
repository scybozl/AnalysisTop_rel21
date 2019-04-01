#! /usr/bin/python                                                                                                                                                                                                                                               
import os,sys
import glob
from array import array
from ROOT import *
from copy import copy

gROOT.ProcessLine('.L Fit_Functions.C')

NPARTOT   = 4*9
NPARTOT_W = 2*6
NPARTOT_R = 4*9

# for BDT
MinIntegralLimit=[125, 55,  0.3]
MaxIntegralLimit=[200, 110, 3.0]

PARs   = []
PARs_W = []
PARs_R = []

extSigPDF_1 = TF1()

def extSumPDF_1(x,  par):
    par=par
    sigval=extSigPDF_1.Eval(x[0])
    return sigval


extSigPDF1_1 = TF1()

def extSumPDF1_1(x,  par):
    par=par
    sigval=extSigPDF1_1.Eval(x[0])
    return sigval

extSigPDF2_1 = TF1()

def extSumPDF2_1(x,  par):
    par=par
    sigval=extSigPDF2_1.Eval(x[0])
    return sigval


def EvalFitFunction(mtop, jsf, bjsf, ic, BinWidth, InputFolder):

    data_INT = 1.0
    bf       = 0.0
    
    # Load PDF info
    filePARs   = InputFolder+"/mtop_pars.root"
    filePARs_W = InputFolder+"/mw_pars.root"
    filePARs_R = InputFolder+"/rbq_pars.root"

    fF1      = TFile(filePARs, "READ")
    fT1      = fF1.Get("pars")
    entries1 = fT1.GetEntries()
    
    fF2      = TFile(filePARs_W, "READ")
    fT2      = fF2.Get("pars")
    entries2 = fT2.GetEntries()

    fF3      = TFile(filePARs_R, "READ")
    fT3      = fF3.Get("pars")
    entries3 = fT3.GetEntries()

    fT1.GetEntry(0)
    for ipar in range(0, NPARTOT):
        PARs.append(fT1.Parameters[ipar])
        
    fT2.GetEntry(0)
    for ipar in range(0, NPARTOT_W):
        PARs_W.append(fT2.Parameters[ipar])

    fT3.GetEntry(0)
    for ipar in range(0, NPARTOT_R):
        PARs_R.append(fT3.Parameters[ipar])
  
    dMCpdf_1     = []
    
    for i in range(0, 3):
        test = TF1()
        if i == 0:
            test = TF1("", MC_pdf_gll,   MinIntegralLimit[0], MaxIntegralLimit[0], NPARTOT+4)
        if i == 1:
            test = TF1("", MC_pdf_mW,    MinIntegralLimit[1], MaxIntegralLimit[1], NPARTOT_W+2)
        if i == 2:
            test = TF1("", MC_pdf_R_ggl, MinIntegralLimit[2], MaxIntegralLimit[2], NPARTOT_R+4)

        dMCpdf_1.append(test)

    for ii in range(0, 3):
        dMCpdf_1[ii].SetNpx(10000)
  
    # Mtop PDF
    # ---------
    for ipar in range(0, 36):
        dMCpdf_1[0].SetParameter(ipar, PARs[ipar])
        
    dMCpdf_1[0].SetParameter(NPARTOT,   mtop) # mtop
    dMCpdf_1[0].SetParameter(NPARTOT+1, jsf)  # jes
    dMCpdf_1[0].SetParameter(NPARTOT+2, bjsf) # bjes
    dMCpdf_1[0].SetParameter(NPARTOT+3, 1.)   # normalization
    # Normalize MCpdf function
    Integral = dMCpdf_1[0].Integral(MinIntegralLimit[0], MaxIntegralLimit[0])
    
    dMCpdf_1[0].SetParameter(NPARTOT+3, 1./Integral*BinWidth  ) 
    #dMCpdf_1[0].SetParameter(NPARTOT+3, (1.-bf)*data_INT )     
        
    # MW PDF
    # ---------
    for ipar in range(0, 12):
        dMCpdf_1[1].SetParameter(ipar, PARs_W[ipar])
        
    dMCpdf_1[1].SetParameter(NPARTOT_W,   jsf) # jes
    dMCpdf_1[1].SetParameter(NPARTOT_W+1, 1.)  # normalization
    # Normalize MCpdf function
    Integral = dMCpdf_1[1].Integral(MinIntegralLimit[1],MaxIntegralLimit[1])
    dMCpdf_1[1].SetParameter(NPARTOT_W+1, 1./Integral*BinWidth  ) 

    
    # Rlb PDF
    # --------
    for ipar in range(0, 36):
        dMCpdf_1[2].SetParameter(ipar, PARs_R[ipar])
        
    dMCpdf_1[2].SetParameter(NPARTOT_R,   mtop) # mtop
    dMCpdf_1[2].SetParameter(NPARTOT_R+1, jsf)  # jes
    dMCpdf_1[2].SetParameter(NPARTOT_R+2, bjsf) # bjes
    dMCpdf_1[2].SetParameter(NPARTOT_R+3, 1.)   # normalization
    # Normalize MCpdf function
    Integral = dMCpdf_1[2].Integral(MinIntegralLimit[2],MaxIntegralLimit[2])
    #dMCpdf_1[2].SetParameter(NPARTOT_R+3, 1./Integral*BinWidth  )   
    dMCpdf_1[2].SetParameter(NPARTOT_R+3, 1.0/Integral*BinWidth)#/*histo[2].GetBinWidth(1) )     
    
    nomin = 1.0
    
    if (ic == 0):
        extSigPDF_1 = dMCpdf_1[ic]
        help1  = TF1("dSUMpdf_1[0]", extSumPDF_1, MinIntegralLimit[ic], MaxIntegralLimit[ic],0)
        return copy(dMCpdf_1[ic])
            
    if (ic==1):
        extSigPDF1_1=dMCpdf_1[ic]     
        help2 = TF1("dSUMpdf_1[1]", extSumPDF1_1, MinIntegralLimit[ic], MaxIntegralLimit[ic],0)
        return copy(dMCpdf_1[ic])
            
    if (ic==2):
        extSigPDF2_1=dMCpdf_1[ic]     
        help3 = TF1("dSUMpdf_1[2]", extSumPDF2_1, MinIntegralLimit[ic], MaxIntegralLimit[ic],0)
        return copy(dMCpdf_1[ic])
    

