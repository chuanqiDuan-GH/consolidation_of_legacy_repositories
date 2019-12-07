/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:1-strMerge.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-01-05 20:35
 *   Describe:合并两个同向有序数组
 ********************************************************/
#include <stdio.h>

void StrMerge(int *finStr, int *str1, int len1, int *str2, int len2)
{
    if(len1 == 0 && len2 == 0)
	return; 

    if(len1 == 0) 
    {
	finStr = str2;
	return;
    }
    if(len2 == 0)
    {
	finStr = str1; 
	return;
    }

    int i = 0; 
    int j = 0;
    int k = 0;

    while(i < len1 && j < len2)
    {
	if(str1[i] < str2[j]) 
	    finStr[k++] = str1[i++];
	else
	    finStr[k++] = str2[j++];
    }

    while(i < len1)
	finStr[k++] = str1[i++];

    while(j < len2)
	finStr[k++] = str2[j++];
}

int main()
{
    int str1[3] = {1, 3, 5};
    int str2[4] = {2, 4, 6, 8};

    int finStr[7] = {0};
    int i;

    StrMerge(finStr, str1, 3, str2, 4);
    for(i=0; i<7; i++)
	printf("%d ", finStr[i]); 
    printf("\n");

    return 0;
}

