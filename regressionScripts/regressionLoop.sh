#!/bin/bash

energies=(10 50 100 200 300 500)
deadFractions=(0 1 3 5 7)

for e in energies
do
for df in deadFractions
do
root -b -q -l TMVARegressionApplication.C\(e,df\)
done
done
