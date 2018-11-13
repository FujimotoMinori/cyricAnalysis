#!/bin/zsh

numbers=($(seq 0 800))

for i in $numbers;do;
	root -l -b -q 'analyze2.cxx("../../YARR/src/registerdata/test'$i'.txt")'
        root -l -b -q  total.cxx
done



