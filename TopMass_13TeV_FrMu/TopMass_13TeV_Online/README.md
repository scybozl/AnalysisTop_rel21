
# Derivation lists

The data derivation list has to be updated by hand, please check below for the container names, GRL, Lumi etc:
https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopDerivationMC16aList

If you want to re-make the derivation list with the latest ptag, delete all the "DerivationList_MC*" files.
In "RunSubmission.py" please set the doMakeDerivationLists flag to True and all others to False,
and tell the script what ptag you are looking for. Then run:

```
localSetupPyAMI
python RunSubmission.py
```

This step will take a while, since it is using pyAMI to check if the derivations do exist.


