#!/bin/bash

flag=1

while :
do

if [ $flag -eq 1 ]
then
sleep 5
echo aaa > /dev/hello1
flag=0

else
sleep 5
echo bbb > /dev/hello1
flag=1
fi 

done
