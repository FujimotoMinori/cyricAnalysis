#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#GRdataprocessing.sh

target=/home/pixeldaq/cyric/afterIrrad/src/registerdata

#for particular files in target directory
for f in `\find $target -name 'run00029_GR*.txt'`; do
    #root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/macros/checkflipbitGR.cxx("'$f'")'
    root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/macros/analyzeGR.cxx("'$f'")'
    #echo $f >> $processed 
    echo "processed file: $f"
done

