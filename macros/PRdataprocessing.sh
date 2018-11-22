#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#PRdataprocessing.sh

target=/home/pixeldaq/cyricdata/afterIrrad/src/registerdata

#for particular files in target directory
for f in `\find $target -name 'run00029_PR*.txt'`; do
    root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/cyricAnalysis/macros/analyzerowcol.cxx("'$f'")'
    echo "processed file: $f"
done


