#!/bin/bash

#如果不存在home/backup文件 执行mkdir
if [ ! -d home/backup ]
then
	sudo mkdir /home/backup
fi
#``反引号使用来引用结果的
flist=`ls`
for fname in $flist
do
	if [ $# = 1 ]
	then
		if [ $1 = $fname ]	
		then
			echo "$fname found"
			exit
		fi
	else
		sudo cp $fname $HOME/backup
		echo $fname copied
	fi
done
