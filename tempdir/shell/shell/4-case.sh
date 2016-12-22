#!/bin/bash
#等于是-eq 不是-e

if [ $# -eq 0 ]
then
    echo "you must chose your operation"
    exit
fi
#相当于c语言switch函数
#shell中所有变量都是字符串
case $1 in
    open)
	echo "open file"
	;;
    read)
	echo "read file"
	;;
    write)
	echo "write file"
	;;
    close)
	echo "close file"
	;;
	*)
	echo "wrong operation" 
esac

