/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:6-quickSort.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-04 21:53
*   Describe:
********************************************************/
#include <stdio.h>

void QuickSort(int *s, int left, int right)
{
    int i = left;
    int j = right;
    int x = s[left];

    if(left < right)
    {
	while(i < j)
	{
	    while(i < j && s[j] >= x)
		j--;	 
	    if(i < j)
		s[i++] = s[j];

	    while(i < j && s[i] < x)
		i++;     
	    if(i < j)
		s[j--] = s[i];
	}
	s[i] = x;
	QuickSort(s, left, i-1);
	QuickSort(s, i+1, right);
    }
}

int main()
{
    int i;
    int arr[] = {9, 10, 20, 0, 3};

    QuickSort(arr, 0, 4);
    for(i=0; i<sizeof(arr)/sizeof(int); i++)
	printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

