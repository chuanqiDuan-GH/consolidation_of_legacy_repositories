/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:9-decimalToBinary.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-22 18:30
 *   Describe:十进制转换二进制
 ********************************************************/
#include <stdio.h>

#define BINARYSIZE 32
int digit = 0;

void DecimalToBinary(int deNum, int *arr)
{
    if(NULL == arr) 
	return;

    if(deNum == 0)
    {
	arr[0] = 0;
	return;
    }

    while(deNum/2)
    {
	arr[digit++] = deNum % 2;
	deNum /= 2;
    }
    arr[digit] = 1;
}

int main()
{
    int arr[BINARYSIZE] = {'\0'};
    int input;
    scanf("%d", &input);

    DecimalToBinary(input, arr);

    do
    {
	printf("%d ", arr[digit]); 
    }while(digit--);

    return 0;
}
