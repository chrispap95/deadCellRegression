#!/bin/tcsh
echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node
source /cvmfs/cms.cern.ch/cmsset_default.csh  ## if a bash script, use .sh instead of .csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
#xrdcp -s root://cmseos.fnal.gov//store/user/chpapage/CMSSW_10_6_3_patch1.tgz .
tar -xf CMSSW_10_6_3_patch1.tgz
rm CMSSW_10_6_3_patch1.tgz
setenv SCRAM_ARCH slc7_amd64_gcc820
cd CMSSW_10_6_3_patch1/src/
scramv1 b ProjectRename
eval `scramv1 runtime -csh` # cmsenv is an alias not on the workers
cd deadCellRegression
set nodes=$1
set train=$2
set test=$3
set UNIQUEID=cmsswTrain_full_E0to3000_4cores_12M_${nodes}nodes_3hl_excludeDead
root -b TMVARegression_layerSum.C\(\"${UNIQUEID}\",\"${train}\",\"${test}\",\"${nodes}\",\"\"\)
tar -czf ${UNIQUEID}.tar.gz dataset ${UNIQUEID}.root
xrdcp -f ${UNIQUEID}.tar.gz root://cmseos.fnal.gov//store/user/chpapage/trainedNNs/
cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_6_3_patch1
