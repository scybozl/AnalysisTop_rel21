# PythonPlottingCode_TopMass

This project is built to produce first simple plots from the output ntuples from AnalysisTop (release 20 and 21)

# First time setup

You get the code when setting up AnalysisTop and checkout the TopMass_13TeV_FrMu package. 
If you only want to use the plotting code, please do:


```
cd TopMass_13TeV_FrMu/PythonPlottingCode_TopMass/
source setup.sh
```

This will setup ROOT, which is all you need to run this code. 

In the folder you find several scripts, and an additional folder called "SortingScripts".
In this folder you find the python files that have all sorting information, such as DSID lists,
lists with variables to plot, etc. 

The main script to modify is DoRunPlottingCode.py , 
where you have to point to the folder with your downloaded files (make sure you do not have FS and AFII files in the same folder!).
The code will automatically split the folders into MC16a and MC16c, depending on their r-tags. 

To fill the histogram files, set the following:
* MainInputFolder -> both for Rel20 and Rel21
* ReleaseFlag -> Rel20 or Rel21
* FillHistos   = True
* MergeHistos  = False
* MakePlots    = False
* PersonalOutputFolderPrefix -> path to a directory where you have writing rights

and add to "List" the configuration you want to run. For each selection, you need to specify the channel, additional cuts, name of the input folder, flag for the name of the output folder and flag (Template, ControlPlots).  
                                                                   
The channel can be either lepjets or dilepton at the moment. If the flag is set to "Template", only the distributions needed for the parametrisation and the actual analysis will be written out, this allows to produce these inputs a lot faster.

---> now run the script:

```
python DoRunPlottingCode.py
```

If you want to check the output of your batch jobs, do:

```
squeue -u $USER
```

Since we have produced the ntuples with 1 b-tag inclusive at the moment, the ttbar jobs can run up to 4h, this will be improved in the future.


You will see that the slurm system will give you a log file per job. In case your job crashes, this will give you useful information 
about why this was the case. 


---> ONLY if the files are successfully filled on the batch cluster then set the other two flags above also to "True" and make the control plots

---> if there are problems with the running on the batch system, please check the syntax in SubmitFillCluster.py

---> files always also contain the cutflow histograms, this will be useful to compare directly with later production rounds

For now we can only used the MakeControlPlot_NominalOnly.py script, I will fix the one with systematics once we have processed all of them.

The folder "ScriptsForLittlePlots" contains litte python scripts to make useful plots, such as the template parametrisation.
