/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:1-findIn2DimensionArr.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-06 23:08
*   Describe:剑指offer-Q3-在二维数组中查找
********************************************************/
#include <stdio.h>

/*gcc -D WARN 加编译条件会有警告会有数据类型转换的警告*/
#ifdef WARN
int Find(int *arr, int row, int column, int num);
#else
int Find(int (*arr)[2], int row, int column, int num);
#endif

int main()
{
    int arr[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    int targetNum = 3;
    int res = Find(arr, 3, 2, targetNum);

    printf("%d\n", res);

    return 0;
}

#ifdef WARN
int Find(int *arr, int row, int column, int num)
#else
int Find(int (*arr)[2], int row, int column, int num)
#endif
{
    int i = 0;
    int j = column-1;

    if(NULL == arr || row <=0 || column <=0)
	return -1;

    while(i < row && j >= 0)
    {
#ifdef WARN
    	if(num == arr[i*column+j])
	    return 1;
	else if(num < arr[i*column+j])        
	    j--;
	else
	    i++;   
#else
	if(num == arr[i][j])
	    return 1;
	else if(num < arr[i][j])        
	    j--;
	else
	    i++;   
#endif
    }
    return 0;
}
