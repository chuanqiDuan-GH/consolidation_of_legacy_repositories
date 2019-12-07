/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:2-clearerrTest.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-11 21:00
*   Describe:clearerr()函数测试
********************************************************/
#include <stdio.h>

int main()
{
    FILE *fp;
    char c;
    /*文件不存在或者文件执行权限不匹配都会输出错误打印*/
    fp = fopen("file.txt", "w");

    c = fgetc(fp);
    /*ferror()检测到错误标志返回非零，否则返回零*/
    if( ferror(fp) )
	printf("%d Error in reading from file : file.txt\n", __LINE__);

    /*clearerr()将错误标志和文件结束标志重置为0，所以27行的错误打印不输出*/
    clearerr(fp);       
    if( ferror(fp) )
	printf("%d Error in reading from file : file.txt\n", __LINE__);
    fclose(fp);

    return(0);
}
