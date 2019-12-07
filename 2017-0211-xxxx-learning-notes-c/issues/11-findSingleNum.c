/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:11-findSingleNum.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-18 22:49
*   Describe:找到数组仅出现一次的数，其他数字均出现两次
********************************************************/
#include <stdio.h>

#define ARRLEN 9

int FindSingleNum(int arr[], int len)
{
    int ret = 0;
    int i;
    for(i=0; i<len; i++){
	ret ^= arr[i]; 
    }
    return ret;
}


void main()
{
    int arr[ARRLEN] = {1, 2, 3, 2, 1, 5, 6, 5, 6};
    printf("%d\n", FindSingleNum(arr, ARRLEN));
}


