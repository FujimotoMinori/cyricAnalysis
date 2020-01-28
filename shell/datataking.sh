#!/usr/bin/env zsh
#-----------------
#datataking.sh

latest=latest.txt

currentrun=`cat ./registerdata/runnumber.dat`
nextrun=` echo $currentrun + 1 | bc -l` 
echo $nextrun > ./registerdata/runnumber.dat

while [ ${#currentrun} -lt 5 ] ; do currentrun=0$currentrun ;done
echo $currentrun

#if [[ -e $latest ]]; then
#	rm $latest
#fi

n=3000
numbers=($(seq 1 $n))
for i in $numbers;do
step=${i}
while [ ${#step} -lt 5 ] ; do step=0$step ;done

#read register
fn=${currentrun}
DATETIME=`date +%Y%m%d_%H%M%S`
echo '#'$DATETIME > ./registerdata/run${fn}_GR${step}.txt
./bin/rd53a_readreganddecode >> ./registerdata/run${fn}_GR${step}.txt
DATETIME=`date +%Y%m%d_%H%M%S`
echo '#'$DATETIME >> ./registerdata/run${fn}_GR${step}.txt
echo "finished taking GR"

sleep 1

./bin/rd53a_readpixelreg3 -c ./registerdata/run${fn}_PR${step}.txt;
DATETIME=`date +%Y%m%d_%H%M%S`
echo '#'$DATETIME >> ./registerdata/run${fn}_PR${step}.txt
echo "finished taking PR"

#to know which the latest file is
echo run${fn}_PR${step}.txt >> ./registerresults/$latest

#sleep
#echo "sleeping"
#sleep 10

done

