/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:4-biSearch.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-20 10:11
 *   Describe:二分查找（折半查找）
 ********************************************************/
#include <stdio.h>

/*二分查找指定元素并反回所查找元素下标*/
int BiSearch(int *arr, int value, int len)
{
    if(NULL == arr || len == 0)
	return -1;
    int start = 0;
    int end = len-1;
    int mid = (start+end)/2;

    while(start < end)
    {
	if(value < arr[mid]) 
	    end = mid;
	else if(value > arr[mid])
	    start = mid;
	else
	    break;

	mid = (start+end)/2;
    }

    if(value == arr[mid])
	return mid;

    return -1;
}


int main()
{
    int arr[9] = {1, 3, 5, 6, 9, 100, 102, 200, 999}; 
    int len = sizeof(arr)/sizeof(int);
    int value; 
    printf("please input a number you want to find:\n");
    scanf("%d", &value);

    int ret = BiSearch(arr, value, len);
    if(ret < 0)
    {
	printf("not found\n");
	return -1; 
    }

    printf("%d\n", ret);
    return 0;
}
