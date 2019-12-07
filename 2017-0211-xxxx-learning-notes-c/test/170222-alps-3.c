/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170222-alps-3.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-26 21:19
*   Describe:阿尔卑斯通信选择题
********************************************************/
#include <stdio.h>

void MyFunc()
{
    char *array = "1234567890";
    printf("%c, %c, %c\n", *array, *(char*)(((int*)array++)+1), array[0]);
}

void main()
{
    MyFunc();
}

/********************************************************
解析：输出2, 5, 1
********************************************************/
