/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170227-gaiqi-2.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-07 23:05
*   Describe:
********************************************************/
#include <stdio.h>

void main()
{
    int a, b, c, d;
    a = 10;
    //printf("%d %d %d\n", a++, ++a, (10*a++));
    b = a++;
    c = ++a;
    d = 10 * a++;
    printf("%d %d %d\n", b, c, d);
}
