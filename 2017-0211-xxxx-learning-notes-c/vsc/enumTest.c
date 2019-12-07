/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:enumTest.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-11-13 22:35
*   Describe:
********************************************************/
#include <stdio.h>

enum E
{
    apple,
    pear,
    orange
}e;

union U
{
    char a;
    float b;
    int c;
}u;

void func ()
{
    //32位机,枚举的大小为4
    printf("%u\n", sizeof(e));
    printf("%u\n", sizeof(u));
}

void main ()
{
    func();    
}
