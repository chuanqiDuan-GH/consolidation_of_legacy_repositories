/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170222-alps-4.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-26 22:18
*   Describe:阿尔卑斯通信选择题
********************************************************/
#include <stdio.h>

void main()
{
    int i = 0x12345678;
    unsigned char *array = (unsigned char*)&i;
    printf("0x%x%x%x%x\n", array[0], array[1], array[2], array[3]);
}

/********************************************************
解析：小端输出0x78563412
********************************************************/
