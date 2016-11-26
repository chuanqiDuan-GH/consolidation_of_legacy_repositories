#!/bin/bash

gcc -D BLOCK test.c -o block.out
gcc test.c -o nonblock.out

sudo ./echoToFile.sh

flag=1

while :
do

if [ $flag -eq 1 ]
then
echo "condition1"
./block.out 
flag=0

else
echo "condition2"
./nonblock.out 
flag=1
fi

done
