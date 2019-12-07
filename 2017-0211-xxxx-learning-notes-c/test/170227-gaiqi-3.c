/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170227-gaiqi-3.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-07 23:19
*   Describe:
********************************************************/
#include <stdio.h>

void main()
{

    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printf("%d\n", *(*(&arr[1]+2)));
}
