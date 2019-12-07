/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:6-minNumOfGyrateArr.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-01-13 22:58
 *   Describe:剑指offer-Q8-旋转数组的最小数字
 ********************************************************/
#include <stdio.h>

/*特殊情况遍历所有找最小*/
void ergodicFind(int *arr, int len)
{
    int min = *arr;
    int i = 0;
    while(i < len)
    {
	if(*(arr+i) < min)
	    min = *(arr+i);
	i++;
    }
    printf("min num: %d\n", min);
}

/*普通情况处理*/
void findMinNumOfGyrateArr(int *arr, int len)
{
    if(NULL == arr || len == 0)
    {
	printf("fatal error\n"); 
	return;
    }

    int posFront = 0;
    int posRear = len-1;
    int posMid = len/2;

    while(posFront < posRear-1)
    {
	if(arr[posFront] == arr[posRear] == arr[posMid])
	{
	    ergodicFind(arr, len);
	    return;
	} 
	if(arr[posFront] < arr[posMid])
	    posFront = posMid;	
	else
	    posRear = posMid;

	posMid = (posRear-posFront)/2 + posFront;
    }
    printf("min num: %d\n", arr[posRear]);
}

int main()
{
    //普通情况
    //int arr[7] = {4, 5, 6, 7, 1, 2, 3};

    //特殊情况
    int arr[7] = {1, 1, 1, 1, 1, 0, 1};
    
    int len = sizeof(arr)/sizeof(int);
    findMinNumOfGyrateArr(arr, len);
    return 0;
}

