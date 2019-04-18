export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh

asetup AnalysisTop,21.2.61,here

lsetup panda
export RUCIO_ACCOUNT=$USER
lsetup rucio
lsetup pyami
