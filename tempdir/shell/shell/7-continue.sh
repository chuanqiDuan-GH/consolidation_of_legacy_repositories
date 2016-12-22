#!/bin/bash

i=1

for i in 10
do
ret=`expr $i % 3`
    if [ $ret -eq 0 ]
    then
	i=`expr $i + 1`
	continue
    else
	echo "$i"
	i=`expr $i + 1`
    fi
done

