# deadCellRegression

Repository for ML study on dead Si cells rechit regression.

for use with root 6.10.04 (CMSSW_9_3_2)


setup a cmssw release
```bash
cmsrel CMSSW_9_3_2
cd CMSSW_9_3_2/src
cmsenv
```

get the repository
```bash 
git clone https://github.com/chrispap95/deadCellRegression.git
```

cd to the area
```bash
cd ToyRegress
```

run the regression
```bash
root -l TMVARegression.C
```

to use the result 
```bash
root -l TMVARegressionApplication.C
```
