#!/bin/sh
USERBASE=`pwd`
rm ${CMSSW_VERSION}.tgz
cd ../../../../
echo "Creating tarball..."
tar --exclude="*.root" --exclude=${CMSSW_BASE}/src/ResolutionAnalyzer --exclude-vcs -zcf ${CMSSW_VERSION}.tgz ${CMSSW_VERSION}
mv ${CMSSW_VERSION}.tgz ${CMSSW_VERSION}/src/deadCellRegression
cd $USERBASE
if [ ! -f ${CMSSW_VERSION}.tgz ]; then
echo "Error: tarball doesn't exist!"
else
echo -n " Done!"
fi
