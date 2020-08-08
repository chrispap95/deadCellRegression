#!/bin/sh
USERBASE=`pwd`
rm CMSSW_10_6_3_patch1.tgz
cd ../../../
tar --exclude="*.root" --exclude=CMSSW_10_6_3_patch1/src/deadCellRegression/cmsswTrain_full_E0to3000_4cores_5M_60nodes_3hl.tar.gz --exclude-vcs -zcvf CMSSW_10_6_3_patch1.tgz CMSSW_10_6_3_patch1/
# xrdcp -f CMSSW_10_6_3_patch1.tgz root://cmseos.fnal.gov//store/user/chpapage/CMSSW_10_6_3_patch1.tgz
mv CMSSW_10_6_3_patch1.tgz CMSSW_10_6_3_patch1/src/deadCellRegression
cd $USERBASE
