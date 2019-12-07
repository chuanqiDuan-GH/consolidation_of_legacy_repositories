/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:1-4-getpid.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-13 22:20
*   Describe:打印进程ID
********************************************************/
#include <stdio.h>

void main(int argc, char *argv[])
{
    printf("the program process ID: %d\n", getpid());
}
