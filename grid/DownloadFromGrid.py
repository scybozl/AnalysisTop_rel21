#!/usr/bin/env python

# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
import TopExamples.grid
import sys
import os

scope          = 'mc16_13TeV'
datasetPattern = sys.argv[1]
seed           = sys.argv[2]
directory      = './'

dataset = datasetPattern + '_' + "{:06d}".format(int(seed)) + ".pool.root.1"

cmd = 'rucio download %s:%s --dir %s' % (scope, dataset, directory)
print 'Downloading file ' + dataset

os.system(cmd)

h = open('input.txt','w')
h.write(scope + '/' + dataset)
h.close()
