/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170227-gaiqi-1.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-07 22:54
*   Describe:
********************************************************/
#include <stdio.h>


int func(int a)
{
    int b;
    switch(a)
    {
	case 1 : b = 30;
	case 2 : b = 20;
	case 3 : b = 10;
	default : b = 0;
    }
    return 0;

}

void main()
{
    printf("%d\n", func(3));
}
