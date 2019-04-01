#!/bin/bash
# job_setup.sh 04 Mar 2019 12:49:29

export VO_ATLAS_SW_DIR=/cvmfs/atlas.cern.ch/repo/sw
if [ -f $VO_ATLAS_SW_DIR/local/setup.sh ]; then
  source $VO_ATLAS_SW_DIR/local/setup.sh
fi

export PANDA_RESOURCE="ANALY_AGLT2_SL7-condor";
export ROOT_TTREECACHE_SIZE=1;
export FRONTIER_ID="[17303704_4265075871]";
export CMSSW_VERSION=$FRONTIER_ID;
export RUCIO_APPID="panda-client-0.6.15-jedi-run";
export RUCIO_ACCOUNT="pilot";
export ROOTCORE_NCPUS=1;
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase;
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh --quiet;
source $AtlasSetup/scripts/asetup.sh AnalysisTop,21.2.61,notest --platform x86_64-slc6-gcc62-opt --makeflags="$MAKEFLAGS";
 export MAKEFLAGS="-j1 QUICK=1 -l1";
export X509_USER_PROXY=/tmp/condor/execute/dir_3997942/jhovercernprodProxy;
./runGen-00-00-02 -j '' --sourceURL https://aipanda011.cern.ch:25443 -r ./ -p top-xaod%20UpfoldingRecoLevel.txt%20in.txt -l panda.0304123808.803789.lib._17303704.16751001456.lib.tgz -o '{'"'"'output.root'"'"': '"'"'panda.um.user.lscyboz.17303704._000002.output.root'"'"'}' -i '['"'"'DAOD_TOPQ1.12770053._000005.pool.root.1'"'"', '"'"'DAOD_TOPQ1.12770053._000006.pool.root.1'"'"', '"'"'DAOD_TOPQ1.12770053._000007.pool.root.1'"'"', '"'"'DAOD_TOPQ1.12770053._000008.pool.root.1'"'"']' --useAthenaPackages --useCMake --writeInputToTxt IN:in.txt --inputGUIDs "[]" --usePFCTurl --directIn

