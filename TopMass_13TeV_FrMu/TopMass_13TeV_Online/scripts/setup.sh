#! /bin/bash                                                                                                                                                                                              

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh --quiet

setupATLAS
localSetupPandaClient
localSetupRucioClients
voms-proxy-init --voms atlas

localSetupPyAMI