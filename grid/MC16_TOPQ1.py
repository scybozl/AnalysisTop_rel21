# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration

import TopExamples.grid

TopExamples.grid.Add("TOPQ1_ttbar_PowPy8").datasets = [
    "mc16_13TeV.410501.PowhegPythia8EvtGen_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_TOPQ1.e5458_s3126_r9364_r9315_p3404"
#    "mc16_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_TOPQ1.e6337_e5984_a875_r9364_r9315_p3554"
#   "mc16_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_TOPQ1.e6337_e5984_s3126_r9364_r9315_p3554"
#    "mc16_13TeV.410557.PowhegHerwig7EvtGen_H7UE_tt_hdamp258p75_704_SingleLep.deriv.DAOD_TOPQ1.e6366_e5984_a875_r10201_r10210_p3554"
    ]

TopExamples.grid.Add("TOPQ1_ttbar_dil_PowPy8").datasets = [
    'mc16_13TeV.410503.PowhegPythia8EvtGen_A14_ttbar_hdamp258p75_dil.deriv.DAOD_TOPQ1.e5475_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_tchan_lep_PowPy6").datasets = [
    'mc16_13TeV.410011.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_top.deriv.DAOD_TOPQ1.e3824_s3126_r9364_r9315_p3215',
    'mc16_13TeV.410012.PowhegPythiaEvtGen_P2012_singletop_tchan_lept_antitop.deriv.DAOD_TOPQ1.e3824_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_Wt_inc_PowPy6").datasets = [
    'mc16_13TeV.410013.PowhegPythiaEvtGen_P2012_Wt_inclusive_top.deriv.DAOD_TOPQ1.e3753_s3126_r9364_r9315_p3215',
    'mc16_13TeV.410014.PowhegPythiaEvtGen_P2012_Wt_inclusive_antitop.deriv.DAOD_TOPQ1.e3753_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_schan_noAllHad_PowPy6").datasets = [
    'mc16_13TeV.410025.PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_top.deriv.DAOD_TOPQ1.e3998_s3126_r9364_r9315_p3215',
    'mc16_13TeV.410026.PowhegPythiaEvtGen_P2012_SingleTopSchan_noAllHad_antitop.deriv.DAOD_TOPQ1.e3998_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_tZ_noAllHad_PowPy6").datasets = [
    'mc16_13TeV.410560.MadGraphPythia8EvtGen_A14_tZ_4fl_tchan_noAllHad.deriv.DAOD_TOPQ1.e5803_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_tZ_trilepton_PowPy6").datasets = [
    'mc16_13TeV.410550.MadGraphPythia8EvtGen_A14_tZ_4fl_tchan_trilepton.deriv.DAOD_TOPQ1.e5803_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_tWZ").datasets = [
    'mc16_13TeV.410217.aMcAtNloHerwigppEvtGen_UEEE5_CTEQ6L1_CT10ME_260000_tWZDR.deriv.DAOD_TOPQ1.e4851_s3126_r9364_r9315_p3215',
    ]


TopExamples.grid.Add("TOPQ1_ttbargamma").datasets = [
    'mc16_13TeV.410082.MadGraphPythia8EvtGen_A14NNPDF23LO_ttgamma_noallhad.deriv.DAOD_TOPQ1.e4404_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_photons").datasets = [
    'mc16_13TeV.301535.Sherpa_CT10_eegammaPt10_35.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                  
    'mc16_13TeV.301536.Sherpa_CT10_mumugammaPt10_35.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                
    'mc16_13TeV.301899.Sherpa_CT10_eegammaPt35_70.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                  
    'mc16_13TeV.301900.Sherpa_CT10_eegammaPt70_140.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                 
    'mc16_13TeV.301901.Sherpa_CT10_eegammaPt140.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                    
    'mc16_13TeV.301902.Sherpa_CT10_mumugammaPt35_70.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                
    'mc16_13TeV.301903.Sherpa_CT10_mumugammaPt70_140.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                               
    'mc16_13TeV.301904.Sherpa_CT10_mumugammaPt140.deriv.DAOD_TOPQ1.e3952_s3126_r9364_r9315_p3215',                                  
    'mc16_13TeV.364510.Sherpa_222_NNPDF30NNLO_tautaugamma_pty_7_15.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                 
    'mc16_13TeV.364511.Sherpa_222_NNPDF30NNLO_tautaugamma_pty_15_35.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                
    'mc16_13TeV.364512.Sherpa_222_NNPDF30NNLO_tautaugamma_pty_35_70.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                
    'mc16_13TeV.364513.Sherpa_222_NNPDF30NNLO_tautaugamma_pty_70_140.deriv.DAOD_TOPQ1.e5982_s3126_r9364_r9315_p3215',               
    'mc16_13TeV.364514.Sherpa_222_NNPDF30NNLO_tautaugamma_pty_140_E_CMS.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',            
    'mc16_13TeV.364517.Sherpa_222_NNPDF30NNLO_nunugamma_pty_35_70.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                  
    'mc16_13TeV.364518.Sherpa_222_NNPDF30NNLO_nunugamma_pty_70_140.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                 
    'mc16_13TeV.364519.Sherpa_222_NNPDF30NNLO_nunugamma_pty_140_E_CMS.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',              
    'mc16_13TeV.364521.Sherpa_222_NNPDF30NNLO_enugamma_pty_7_15.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                    
    'mc16_13TeV.364523.Sherpa_222_NNPDF30NNLO_enugamma_pty_35_70.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                   
    'mc16_13TeV.364524.Sherpa_222_NNPDF30NNLO_enugamma_pty_70_140.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                  
    'mc16_13TeV.364525.Sherpa_222_NNPDF30NNLO_enugamma_pty_140_E_CMS.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',               
    'mc16_13TeV.364526.Sherpa_222_NNPDF30NNLO_munugamma_pty_7_15.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                   
    'mc16_13TeV.364528.Sherpa_222_NNPDF30NNLO_munugamma_pty_35_70.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                  
    'mc16_13TeV.364529.Sherpa_222_NNPDF30NNLO_munugamma_pty_70_140.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                 
    'mc16_13TeV.364530.Sherpa_222_NNPDF30NNLO_munugamma_pty_140_E_CMS.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',              
    'mc16_13TeV.364531.Sherpa_222_NNPDF30NNLO_taunugamma_pty_7_15.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                  
    'mc16_13TeV.364533.Sherpa_222_NNPDF30NNLO_taunugamma_pty_35_70.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                 
    'mc16_13TeV.364534.Sherpa_222_NNPDF30NNLO_taunugamma_pty_70_140.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',                
    'mc16_13TeV.364535.Sherpa_222_NNPDF30NNLO_taunugamma_pty_140_E_CMS.deriv.DAOD_TOPQ1.e5928_s3126_r9364_r9315_p3215',             
    ]

TopExamples.grid.Add("TOPQ1_diboson_Sherpa").datasets = [
    'mc16_13TeV.363355.Sherpa_221_NNPDF30NNLO_ZqqZvv.deriv.DAOD_TOPQ1.e5525_s3126_r9364_r9315_p3215',                               
    'mc16_13TeV.363356.Sherpa_221_NNPDF30NNLO_ZqqZll.deriv.DAOD_TOPQ1.e5525_s3126_r9364_r9315_p3215',                               
    'mc16_13TeV.363357.Sherpa_221_NNPDF30NNLO_WqqZvv.deriv.DAOD_TOPQ1.e5525_s3126_r9364_r9315_p3215',                               
    'mc16_13TeV.363358.Sherpa_221_NNPDF30NNLO_WqqZll.deriv.DAOD_TOPQ1.e5525_s3126_r9364_r9315_p3215',                               
    'mc16_13TeV.363359.Sherpa_221_NNPDF30NNLO_WpqqWmlv.deriv.DAOD_TOPQ1.e5583_s3126_r9364_r9315_p3215',                             
    'mc16_13TeV.363360.Sherpa_221_NNPDF30NNLO_WplvWmqq.deriv.DAOD_TOPQ1.e5583_s3126_r9364_r9315_p3215',                             
    'mc16_13TeV.363360.Sherpa_221_NNPDF30NNLO_WplvWmqq.deriv.DAOD_TOPQ1.e5983_s3126_r9364_r9315_p3215',                             
    'mc16_13TeV.363489.Sherpa_221_NNPDF30NNLO_WlvZqq.deriv.DAOD_TOPQ1.e5525_s3126_r9364_r9315_p3215',                               
    'mc16_13TeV.363494.Sherpa_221_NNPDF30NNLO_vvvv.deriv.DAOD_TOPQ1.e5332_s3126_r9364_r9315_p3215', 
    'mc16_13TeV.364250.Sherpa_222_NNPDF30NNLO_llll.deriv.DAOD_TOPQ1.e5894_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364253.Sherpa_222_NNPDF30NNLO_lllv.deriv.DAOD_TOPQ1.e5916_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364254.Sherpa_222_NNPDF30NNLO_llvv.deriv.DAOD_TOPQ1.e5916_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364255.Sherpa_222_NNPDF30NNLO_lvvv.deriv.DAOD_TOPQ1.e5916_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_Zjets_Sherpa221").datasets = [                                
    'mc16_13TeV.364100.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364101.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_CFilterBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364102.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',           
    'mc16_13TeV.364103.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CVetoBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364104.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_CFilterBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364105.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV70_140_BFilter.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',         
    'mc16_13TeV.364106.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CVetoBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364107.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CFilterBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364108.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_BFilter.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364109.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CVetoBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364110.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_CFilterBVeto.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364111.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV280_500_BFilter.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364112.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV500_1000.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',               
    'mc16_13TeV.364113.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV1000_E_CMS.deriv.DAOD_TOPQ1.e5271_s3126_r9364_r9315_p3215',             
    'mc16_13TeV.364114.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',          
    'mc16_13TeV.364115.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_CFilterBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364116.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',             
    'mc16_13TeV.364117.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CVetoBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364118.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_CFilterBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364119.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV70_140_BFilter.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',           
    'mc16_13TeV.364120.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CVetoBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364121.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_CFilterBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364122.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV140_280_BFilter.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',          
    'mc16_13TeV.364123.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CVetoBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364124.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_CFilterBVeto.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364125.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV280_500_BFilter.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',          
    'mc16_13TeV.364126.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV500_1000.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',                 
    'mc16_13TeV.364127.Sherpa_221_NNPDF30NNLO_Zee_MAXHTPTV1000_E_CMS.deriv.DAOD_TOPQ1.e5299_s3126_r9364_r9315_p3215',               
    'mc16_13TeV.364128.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364129.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_CFilterBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364130.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',         
    'mc16_13TeV.364131.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CVetoBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364132.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_CFilterBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',  
    'mc16_13TeV.364133.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV70_140_BFilter.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364134.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CVetoBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364135.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_CFilterBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215', 
    'mc16_13TeV.364136.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV140_280_BFilter.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364137.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CVetoBVeto.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364138.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_CFilterBVeto.deriv.DAOD_TOPQ1.e5313_s3126_r9364_r9315_p3215', 
    'mc16_13TeV.364139.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV280_500_BFilter.deriv.DAOD_TOPQ1.e5313_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364140.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV500_1000.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',             
    'mc16_13TeV.364141.Sherpa_221_NNPDF30NNLO_Ztautau_MAXHTPTV1000_E_CMS.deriv.DAOD_TOPQ1.e5307_s3126_r9364_r9315_p3215',           
    'mc16_13TeV.364198.Sherpa_221_NN30NNLO_Zmm_Mll10_40_MAXHTPTV0_70_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364199.Sherpa_221_NN30NNLO_Zmm_Mll10_40_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364200.Sherpa_221_NN30NNLO_Zmm_Mll10_40_MAXHTPTV70_280_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364201.Sherpa_221_NN30NNLO_Zmm_Mll10_40_MAXHTPTV70_280_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364202.Sherpa_221_NN30NNLO_Zmm_Mll10_40_MAXHTPTV280_E_CMS_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364203.Sherpa_221_NN30NNLO_Zmm_Mll10_40_MAXHTPTV280_E_CMS_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364204.Sherpa_221_NN30NNLO_Zee_Mll10_40_MAXHTPTV0_70_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364205.Sherpa_221_NN30NNLO_Zee_Mll10_40_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364206.Sherpa_221_NN30NNLO_Zee_Mll10_40_MAXHTPTV70_280_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364207.Sherpa_221_NN30NNLO_Zee_Mll10_40_MAXHTPTV70_280_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364208.Sherpa_221_NN30NNLO_Zee_Mll10_40_MAXHTPTV280_E_CMS_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364209.Sherpa_221_NN30NNLO_Zee_Mll10_40_MAXHTPTV280_E_CMS_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364210.Sherpa_221_NN30NNLO_Ztt_Mll10_40_MAXHTPTV0_70_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364211.Sherpa_221_NN30NNLO_Ztt_Mll10_40_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364212.Sherpa_221_NN30NNLO_Ztt_Mll10_40_MAXHTPTV70_280_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364213.Sherpa_221_NN30NNLO_Ztt_Mll10_40_MAXHTPTV70_280_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364214.Sherpa_221_NN30NNLO_Ztt_Mll10_40_MAXHTPTV280_E_CMS_BVeto.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    'mc16_13TeV.364215.Sherpa_221_NN30NNLO_Ztt_Mll10_40_MAXHTPTV280_E_CMS_BFilter.deriv.DAOD_TOPQ1.e5421_s3126_r9364_r9315_p3215',
    ]

TopExamples.grid.Add("TOPQ1_Wjets_Sherpa221").datasets = [
    'mc16_13TeV.364156.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364157.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364158.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',           
    'mc16_13TeV.364159.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364160.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364161.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV70_140_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',         
    'mc16_13TeV.364162.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364163.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364164.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV140_280_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364165.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364166.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364167.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV280_500_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364168.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV500_1000.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',               
    'mc16_13TeV.364169.Sherpa_221_NNPDF30NNLO_Wmunu_MAXHTPTV1000_E_CMS.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',             
    'mc16_13TeV.364170.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',         
    'mc16_13TeV.364171.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364172.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',            
    'mc16_13TeV.364173.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364174.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364175.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV70_140_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',          
    'mc16_13TeV.364176.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364177.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364178.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV140_280_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',         
    'mc16_13TeV.364179.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',      
    'mc16_13TeV.364180.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364181.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV280_500_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',         
    'mc16_13TeV.364182.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV500_1000.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',                
    'mc16_13TeV.364183.Sherpa_221_NNPDF30NNLO_Wenu_MAXHTPTV1000_E_CMS.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',              
    'mc16_13TeV.364184.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364185.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364186.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV0_70_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',          
    'mc16_13TeV.364187.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',     
    'mc16_13TeV.364188.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',   
    'mc16_13TeV.364189.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV70_140_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',        
    'mc16_13TeV.364190.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364191.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',  
    'mc16_13TeV.364192.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV140_280_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364193.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CVetoBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',    
    'mc16_13TeV.364194.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_CFilterBVeto.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',  
    'mc16_13TeV.364195.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV280_500_BFilter.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',       
    'mc16_13TeV.364196.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV500_1000.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',              
    'mc16_13TeV.364197.Sherpa_221_NNPDF30NNLO_Wtaunu_MAXHTPTV1000_E_CMS.deriv.DAOD_TOPQ1.e5340_s3126_r9364_r9315_p3215',            
    ]

TopExamples.grid.Add("TOPQ1_ttV").datasets = [
    'mc16_13TeV.410081.MadGraphPythia8EvtGen_A14NNPDF23_ttbarWW.deriv.DAOD_TOPQ1.e4111_s3126_r9364_r9315_p3215',                    
    'mc16_13TeV.410155.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttW.deriv.DAOD_TOPQ1.e5070_s3126_r9364_r9315_p3215',                 
    'mc16_13TeV.410156.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZnunu.deriv.DAOD_TOPQ1.e5070_s3126_r9364_r9315_p3215',             
    'mc16_13TeV.410157.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttZqq.deriv.DAOD_TOPQ1.e5070_s3126_r9364_r9315_p3215',               
    'mc16_13TeV.410218.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttee.deriv.DAOD_TOPQ1.e5070_s3126_r9364_r9315_p3215',                
    'mc16_13TeV.410219.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_ttmumu.deriv.DAOD_TOPQ1.e5070_s3126_r9364_r9315_p3215',              
    'mc16_13TeV.410220.aMcAtNloPythia8EvtGen_MEN30NLO_A14N23LO_tttautau.deriv.DAOD_TOPQ1.e5070_s3126_r9364_r9315_p3215',            
    ]         
