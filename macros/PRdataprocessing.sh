#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#PRdataprocessing.sh

target=/home/pixeldaq/cyric/afterIrrad/src/registerdata

#for particular files in target directory
for f in `\find $target -name 'run00052_PR*.txt'`; do
    root -l -b -q '/home/pixeldaq/cyric/cyricAnalysis/macros/analyze2.cxx("'$f'")'
    echo "processed file: $f"
done


