#!/bin/bash
######!/usr/bin/env zsh
#-----------------
#configure

./bin/rd53a_GRconfig
echo "configured"

./bin/rd53a_readreganddecode > GR.txt
echo "made first file of GR" 

sleep 1

./bin/rd53a_readpixelreg3 -c PR2.txt 
echo "made first file of PR" 
