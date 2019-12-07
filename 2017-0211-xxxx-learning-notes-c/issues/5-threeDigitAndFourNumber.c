/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:5-threeDigitAndFourNumber.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-20 11:05
*   Describe:打印四个数字组成不重复且数字不复用的三位数
********************************************************/
#include <stdio.h>

int main()
{
    int i=0, j=0, q=0;
    /*1 2 3 4能够组成的所有符合提议的三位数*/
    for(i=1; i<5; i++)
    {
	//保证数字不复用
	if(i==j || i==q)
	    continue;
	
	for(j=1; j<5; j++)
	{
	    if(j==i || j==q)
		continue;

	    for(q=1; q<5; q++)
	    {
		if(q==i || q==j)
		    continue;

		printf("%d%d%d\n", i, j, q); 
	    }
	}
    }
    return 0;
}
