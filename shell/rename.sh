#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#rename.sh


currentrun=`cat ./registerdata/runnumber.dat`
lastrun=` echo $currentrun - 1 | bc -l` 

while [ ${#lastrun} -lt 5 ] ; do lastrun=0$lastrun ;done

fn=${lastrun}

mv ./registerresults/summary.txt ./registerresults/summary_run${fn}.txt
echo "renamed summary.txt" 
mv ./registerresults/sumplace.txt ./registerresults/sumplace_run${fn}.txt
echo "renamed sumplace.txt" 

sleep 1

mv ./registerresults/summaryoutput.root  ./registerresults/summaryoutput_run${fn}.root
echo "renamed summaryoutput.root" 
mv ./registerresults/summaryrowcol.root  ./registerresults/summaryrowcol_run${fn}.root
echo "renamed summaryrowcol.root" 


