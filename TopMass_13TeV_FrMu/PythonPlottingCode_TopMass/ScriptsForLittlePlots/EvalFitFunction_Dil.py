#! /usr/bin/python                                                                                                                                                                                                                                               
import os,sys
import glob
from array import array
from ROOT import *
from copy import copy

gROOT.ProcessLine('.L Fit_Functions.C')

NPARTOT = 18

# for BDT
MinIntegralLimit=[30.0]
MaxIntegralLimit=[170.0]

PARs   = []

extSigPDF_1 = TF1()

def extSumPDF_1(x,  par):
    par=par
    sigval=extSigPDF_1.Eval(x[0])
    return sigval

def EvalFitFunction_mlb(mtop, BinWidth, InputFolder):

    data_INT = 1.0
    bf       = 0.0
    
    # Load PDF info
    filePARs   = InputFolder+"/mlb_pars.root"
 
    fF1      = TFile(filePARs, "READ")
    fT1      = fF1.Get("pars")
    entries1 = fT1.GetEntries()
    
    fT1.GetEntry(0)
    for ipar in range(0, NPARTOT):
        PARs.append(fT1.Parameters[ipar])
          
    dMCpdf_1     = []
    
    test = TF1()
    test = TF1("", MC_pdf_dilepton_triplegauss, MinIntegralLimit[0], MaxIntegralLimit[0], NPARTOT+2)
    
    dMCpdf_1.append(test)

    dMCpdf_1[0].SetNpx(10000)
  
    # Mlb PDF
    # ---------
    for ipar in range(0, NPARTOT):
        dMCpdf_1[0].SetParameter(ipar, PARs[ipar])
        
    dMCpdf_1[0].SetParameter(NPARTOT,   mtop) # mtop
    dMCpdf_1[0].SetParameter(NPARTOT+1, 1.)   # normalization
    Integral = dMCpdf_1[0].Integral(MinIntegralLimit[0], MaxIntegralLimit[0])
    
    dMCpdf_1[0].SetParameter(NPARTOT+1, 1./Integral*BinWidth) 

    extSigPDF_1 = dMCpdf_1[0]
    help1  = TF1("dSUMpdf_1[0]", extSumPDF_1, MinIntegralLimit[0], MaxIntegralLimit[0],0)
    return copy(dMCpdf_1[0])
            
    
