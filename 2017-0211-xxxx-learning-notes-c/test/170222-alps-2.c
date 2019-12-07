/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170222-alps-2.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-26 20:43
*   Describe:阿尔卑斯通信选择题
********************************************************/
#include <stdio.h>

void main()
{
    int i = 0;
    int j;

    for(; i<=3; j++)
    {
	j += i; 
    }
    printf("%d\n", j);
}

/********************************************************
解析：死循环
********************************************************/
