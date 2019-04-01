#! /usr/bin/python

#OutputTable = sys.argv[1]
#nr_tables = len(sys.argv)-3

InputFolder = "../../../run/OutputFolder_PE_Syst_Plots/"

OutputTable = InputFolder+"/bla_JES_noBJES.tex"

InputTables = []
InputTables.append(["Uncertainties_1D_mtop_JES_noBJES.tex", "1D fit"])
InputTables.append(["Uncertainties_2D_mtop_JES_noBJES.tex", "2D fit"])

counter = 0

AllEntries = []

for entry in InputTables:
    #print entry
    infile = open(InputFolder+"/"+entry[0], "r")
    lines  = infile.readlines()
    liste  = []
    for line in lines:
        #print line
        line = line.replace("\\", "")
        liste.append(line.replace("\n", ""))
        
    AllEntries.append(liste)

    #    print line.split("&")
    #    print len(line.split("&"))

outfile = open(OutputTable, 'w')

lines = len(AllEntries[0])
dim   = len(AllEntries)

for i in range(0, lines):
    NewLine = AllEntries[0][i].split("&")
    if len(NewLine) == 1:
        outfile.write("\\"+AllEntries[0][i]+" \n")
    else:
        NewEntry = AllEntries[0][i]
        for j in range(1, dim):
            NewEntry += " & "+(AllEntries[j][i]).split("&")[1]
        NewEntry += " \\\\ \n"

        outfile.write(NewEntry)

outfile.close()
