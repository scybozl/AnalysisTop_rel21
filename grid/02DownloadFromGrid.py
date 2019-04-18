#!/usr/bin/env python

# Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
import TopExamples.grid

scope          = 'user.lscyboz'
datasetPattern = '*test_02-03-45a_output.root'
directory      = '/tmp/lscyboz/DownloadFolder/'

TopExamples.grid.download(scope, datasetPattern, directory)
