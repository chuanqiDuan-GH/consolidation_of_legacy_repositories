#!/bin/bash
#使用比较命令ge和le时i, 一定要加‘-’
#使用a(与)和o(或)时,一定要加‘-’
read num
#判断输入的数字是否大于等于5，小于等于10
#-ge大于等于 -le小于等于 -gt大于 -lt小于 
if [ $num -gt 5 -a $num -le 10 ]
then
    echo yes
    exit
else
    echo no
fi
