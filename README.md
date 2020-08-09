# deadCellRegression

Repository for ML study on dead Si cells rechit regression.
For use with ROOT > 6.10.04 (CMSSW_9_3_2)

## Initial setup

Setup latest CMSSW release
```bash
cmsrel CMSSW_11_2_0_pre2
cd CMSSW_11_2_0_pre2/src
cmsenv
```

Get the repository
```bash
git clone https://github.com/chrispap95/deadCellRegression.git
```

cd to the area
```bash
cd deadCellRegression/regressionScripts
```

Train the algorithm
```bash
root -l TMVARegression.C\(\"someSample.root\",\"testRun\",\"10000\",\"2500\"\)
```

to use the result
```bash
root -l TMVARegressionApplication.C\(100,1\)
```

## Explanation of main algorithms

To get an idea of what the inputs are:
```bash
root -l TMVARegression.C\(\"inputFile.root\",\"uniqueIDstring\",\"nTrain\",\"nTest\",nHiddenLayers,\"nodesPerLayer\"\)
root -l TMVARegressionApplication.C\(energy,deadFraction\)
```

The training script can be also submitted through condor using `prepareCondor.sh`,`condor-exec.csh`,`condor.jdl`.
When the files are configured properly, submit using
```bash
condor_submit condor.jdl
```

## Keras regression

Use `deadCellsRegression*.py` scripts for Keras based regression. You will need to add the input/output names in the scripts.
Ultimate goal is to make these the default scripts for regression.

## Fit and plot resolution

The script `rechitSumLooper.C` can be used for easy fitting of the discrete energy samples. Run it as follows:
```bash
root -l rechitSumLooper.C\(deadFraction,\"methodToUse\"\)
```
The available methods are `none`,`MLregr`,`aver` and `LSaver`.
Finally, to combine multiple plots into one, you can use `plotComparison.C`. It uses the root files from the previous step as input.
