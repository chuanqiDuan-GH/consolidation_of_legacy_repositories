/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:3-selectSort.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-02 19:58
*   Describe:
********************************************************/
#include <stdio.h>

void SelectSort(int *arr, int len);

int main()
{
    int i;
    int arr[] = {9, 10, 20, 0, 3};

    SelectSort(arr, sizeof(arr)/sizeof(int));
    for(i=0; i<sizeof(arr)/sizeof(int); i++)
	printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void SelectSort(int *arr, int len)
{
    if(NULL == arr || len <= 1)
	return; 

    int	i;
    int j;
    int min;
    int tmp;

    for(i=0; i<len; i++)
    {
	min = i;
	for(j=i; j<len; j++)
	{
	    if(arr[j] < arr[min])
		min  = j;
	}

	tmp = arr[i];	
	arr[i] = arr[min];
	arr[min] = tmp;
    }
}
