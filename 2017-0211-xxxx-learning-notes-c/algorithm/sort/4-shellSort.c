/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:4-shellSort.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-02 20:32
*   Describe:
********************************************************/
#include <stdio.h>

void ShellSort(int *arr, int len);
void ShellSort2(int *arr, int len);
void ShellSort3(int *arr, int len);

int main()
{
    int i;
    int arr[] = {9, 10, 20, 0, 3};

    ShellSort3(arr, sizeof(arr)/sizeof(int));
    for(i=0; i<sizeof(arr)/sizeof(int); i++)
	printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void ShellSort(int *arr, int len)
{
    if(NULL == arr || len <=1)
	return;

    int i;
    int j;
    int tmp;
    int gap;

    for(gap=len/2; gap>0; gap/=2)
    {
	for(i=gap; i<len; i++)
	{
	    for(j=i-gap; j>=0&&arr[j]>arr[j+gap]; j-=gap)
	    {
		tmp = arr[j];
		arr[j] = arr[j+gap];
		arr[j+gap]= tmp;
	    }
	}
    }
}

void ShellSort2(int *arr, int len)
{
    if(NULL == arr || len <=1)
	return;

    int i;
    int j;
    int tmp;
    int gap = len / 2;

    while(gap > 0)
    {
	for(i=gap; i<len; i++)
	{
	    for(j=i-gap; j>=0; j-=gap)
	    {
		if(arr[j+gap] < arr[j])
		{
		    tmp = arr[j];
		    arr[j] = arr[j+gap];
		    arr[j+gap]= tmp;
		}
	    }
	}
	gap /= 2;
    }
}

void ShellSort3(int *arr, int len)
{
    if(NULL == arr || len <=1)
	return;

    int i;
    int j;
    int tmp;
    int gap = len / 2;

    while(gap > 0)
    {
	for(i=gap; i<len; i++)
	{
	    tmp = arr[i];
	    j = i - gap;	
	    while(j >= 0 && arr[j] > tmp)
	    {
		arr[j+gap] = arr[j]; 
		j -= gap;
	    }
	    arr[j+gap] = tmp;
	}
	gap /= 2;
    }
}
