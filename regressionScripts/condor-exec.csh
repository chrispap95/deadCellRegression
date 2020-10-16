#!/bin/tcsh
echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node
source /cvmfs/cms.cern.ch/cmsset_default.csh  ## if a bash script, use .sh instead of .csh
### for case 1. EOS have the following line, otherwise remove this line in case 2.
#xrdcp -s root://cmseos.fnal.gov//store/user/chpapage/CMSSW_10_6_3_patch1.tgz .
set CMSSW=$5
tar -xf ${CMSSW}.tgz
rm ${CMSSW}.tgz
setenv SCRAM_ARCH slc7_amd64_gcc820
cd ${CMSSW}/src/
scramv1 b ProjectRename
eval `scramv1 runtime -csh` # cmsenv is an alias not on the workers
cd deadCellRegression/regressionScripts
set layers=$1 # number of hidden layers
set nodes=$2 # number of nodes per hidden layer
set train=$3 # number of cells used for training
set test=$4 # number of cells used for testing
set energyRange=0to3000
set filename=root://cmseos.fnal.gov//store/user/${USER}/DeadCellsSamples/TrainingSamples/out_E0to650Eta1p7_converted.root
set sampleSize=1M  # How large is the sample you are using in terms of dead cells number
set UNIQUEID=training_E${energyRange}_4cores_${sampleSize}_${nodes}nodes_${layers}hiddenLayers
root -b TMVARegression.C\(\"${filename}\",\"${UNIQUEID}\",\"${train}\",\"${test}\",${layers},\"${nodes}\"\)
tar -czf ${UNIQUEID}.tar.gz dataset ${UNIQUEID}.root
xrdcp -f ${UNIQUEID}.tar.gz root://cmseos.fnal.gov//store/user/${USER}/trainedNNs/
cd ${_CONDOR_SCRATCH_DIR}
rm -rf ${CMSSW}
