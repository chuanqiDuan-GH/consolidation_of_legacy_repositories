/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:1-3-getcPutc.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-13 21:22
*   Describe:用标准IO将标准输入复制到标准输出
********************************************************/
#include <stdio.h>

void main(int argc, char *argv[])
{
    int c;
    while((c = getc(stdin)) != EOF)
	if(putc(c, stdout) == EOF)
	    printf("putc error\n");	    	
    
    if(ferror(stdin))
	printf("getc error\n");
}
