/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:1-2-stdinCopyToStdout.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-12 20:53
*   Describe:将标准输入复制到标注输出
********************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE	64

void main(int argc, char *argv[])
{
    int charNum;
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    
    while((charNum = read(STDIN_FILENO, buf, BUFSIZE)))
	if(write(STDOUT_FILENO, buf, charNum) != charNum)	 
	    printf("write error\n");		 

    if(charNum < 0)
	printf("read error\n");	
}

/********************************************************
两个常量STDIN_FILENO和STDOUT_FILENO定义在<unistd.h>头文件中,
它们指定了标准输入和标准输出的文件描述符,它们的典型值分别为0和1,
但考虑移植行,将使用新名字.
********************************************************/
