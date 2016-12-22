#!/bin/bash
#注意if和fi是搭配使用的

if [ -d $1 ]
then
    echo $1 is directoy
    exit
else
    if [ -f $1 ]
    then
	echo $1 is file
    else
	echo find nothing
    fi
fi
