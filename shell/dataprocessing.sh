#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#dataprocessing.sh

processed=./registerresults/processed.txt
latest=./registerresults/latest.txt

numlatestfile=0
while :
do

#check the latest file
#latest_files=($(cat $latest))
latest_files=`wc -l $latest | awk '{print $1}'`

if [ ! $numlatestfile -eq ${latest_files} ]
then
    numlatestfile=`wc -l ${latest} | awk '{print $1}'`
    echo "${numlatestfile} files"
#    echo "${#latest_files} files"
#    numlatestfile=${#latest_files}
fi


#check if the latest file exists in processed files
#if not exist, process the file
########files_processed=($(cat $processed))
#########echo "${#files_processed} files"
########files_notexist=()
########for f in $latest_files; do
########	i1=${files_processed[(ie)$f]}
########        if [[ ${i1} -gt ${#files_processed} ]]; then
########	files_notexist=($files_notexist $f)
########  	fi
########done

nlatest=`wc -l $latest  | awk '{print $1}'`
nprocessed=`wc -l $processed | awk '{print $1}'`
nprocess=`echo $nlatest - $nprocessed | bc -l`
files_notexist=`tail -$nprocess $latest`


for f in $files_notexist; do
    GRfile=`echo $f | sed s/PR/GR/g`
    root -l -b -q '/home/atlasj/work/XpressK7_RD53A/YARR_ocha/YARR_rd53a/cyric/macros/analyze2.cxx("/home/atlasj/work/XpressK7_RD53A/YARR/src/registerdata/'$f'")'
    root -l -b -q '/home/atlasj/work/XpressK7_RD53A/YARR_ocha/YARR_rd53a/cyric/macros/analyzeGR.cxx("/home/atlasj/work/XpressK7_RD53A/YARR/src/registerdata/'$GRfile'")'
    root -l -b -q '/home/atlasj/work/XpressK7_RD53A/YARR_ocha/YARR_rd53a/cyric/macros/analyzerowcol.cxx("/home/atlasj/work/XpressK7_RD53A/YARR/src/registerdata/'$f'")'
    echo $f >> $processed 
    echo "processed file: $f"
done

done
