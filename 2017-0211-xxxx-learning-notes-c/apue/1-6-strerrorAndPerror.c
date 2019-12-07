/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:1-6-strerrorAndPerror.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-14 23:07
*   Describe:strerror和perror的使用示例
********************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>

void main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES:%s\n", strerror(EACCES));
    errno = ENOENT;

    perror(argv[0]);
}
