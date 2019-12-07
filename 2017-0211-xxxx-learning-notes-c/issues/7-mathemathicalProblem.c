/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:7-mathemathicalProblem.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-21 22:01
 *   Describe:PI = 4*(1-1/3+1/5-1/7+...)10000项内PI的值
 ********************************************************/
#include <stdio.h>

double sumOfPI(int n)
{
    int i;
    int flag = 1;
    double sum = 0;
    double tmp;

    for(i=0; i<n; i++)
    {
	/********************************************************
	  分子或分母中有实型数字(1.0),那么就会将结果转化成实型
	  1/2 = 0
	  1.0/2 = 0.5
	  1/2.0 = 0.5
	  1.0/2.0 = 0.5
	 ********************************************************/
	tmp = 1.0/(2*i+1)*flag; 
	sum += tmp; 
	flag = -flag;
    }
    return sum;
}

int main()
{
    printf("%lf", 4*sumOfPI(10000));
    return 0;
}
