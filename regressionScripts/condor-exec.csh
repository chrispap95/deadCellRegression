#!/bin/tcsh
echo "Starting job on " `date` #Date/time of start of job
echo "Running on: `uname -a`" #Condor job is running on this node
echo "System software: `cat /etc/redhat-release`" #Operating System on that node
source /cvmfs/cms.cern.ch/cmsset_default.csh

# Input section
set layers=$1 # number of hidden layers
set nodes=$2 # number of nodes per hidden layer
set train=$3 # number of cells in the sample file
set CMSSW=$4
set energyRange=0to3000
set filename=root://cmseos.fnal.gov//store/user/${USER}/DeadCellsSamples/TrainingSamples/out_E0to650Eta1p7_converted.root
set sampleSize=1M  # How large is the sample you are using in terms of dead cells number
set UNIQUEID=training_E${energyRange}_4cores_${sampleSize}_${nodes}nodes_${layers}hiddenLayers

# Unpack, setup and execute the code
tar -xf ${CMSSW}.tgz
rm ${CMSSW}.tgz
setenv SCRAM_ARCH slc7_amd64_gcc820
cd ${CMSSW}/src/
scramv1 b ProjectRename
eval `scramv1 runtime -csh` # cmsenv is an alias not on the workers
cd deadCellRegression/regressionScripts
root -b TMVARegression.C\(\"${filename}\",\"${UNIQUEID}\",${},${layers},\"${nodes}\"\)

# Output stage
tar -czf ${UNIQUEID}.tar.gz dataset ${UNIQUEID}.root
xrdcp -f ${UNIQUEID}.tar.gz root://cmseos.fnal.gov//store/user/${USER}/trainedNNs/
cd ${_CONDOR_SCRATCH_DIR}
rm -rf ${CMSSW}
