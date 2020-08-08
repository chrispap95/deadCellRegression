#!/bin/bash

# requires 4 argument inputs:
# 1: UNIQUE_ID - any unique string identifier
# 2: CONDOR_PROCESS - condor process number
# RUN_DIR - running directory (CMSSW_X_Y_Z/subdir)
# mode.  should be 0 for background or 1 for signal

UNIQUE_ID=$1
CONDOR_PROCESS=$2
RUN_DIR=$3

START_TIME=`/bin/date`
echo "started at $START_TIME"

cd $RUN_DIR

cd ..
pwd
export USERBASE=`pwd`

#export ARCH = slc6_amd64_gcc700
#source /cvmfs/sft.cern.ch/lcg/external/gcc/4.6.3/x86_64-slc6/setup.sh "" #Needs fixing to gcc7

#cd /cvmfs/cms.cern.ch/${ARCH}/lcg/root/6.12.07/bin/
#source thisroot.sh
cd ${USERBASE}

pwd
cmsenv

FINAL_PREFIX_NAME=`echo ${UNIQUE_ID}_${CONDOR_PROCESS}`
FINAL_LOG=`echo $FINAL_PREFIX_NAME.log`

cd $RUN_DIR
pwd
echo $LD_LIBRARY_PATH
root -bl TMVARegression_layerSum.C\(\"DNN_CPU\"\) >> $FINAL_LOG 2>&1

echo ""
END_TIME=`/bin/date`
echo "finished at $END_TIME"
exit $exitcode
