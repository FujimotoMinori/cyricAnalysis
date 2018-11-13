#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#PRdataprocessing.sh

target=/home/pixeldaq/cyric/afterIrrad/src/registerdata

#for particular files in target directory
for f in `\find $target -name 'run00029_PR*.txt'`; do
    #root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/macros/checkflipbitGR.cxx("'$f'")'
    root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/macros/analyze2.cxx("'$f'")'
    #root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/macros/checkflipbitFE.cxx("'$f'")'
    #root -l -b -q '/home/pixeldaq/YARR_rd53a/cyric/macros/analyzerowcol.cxx("'$f'")'
    echo "processed file: $f"
done


