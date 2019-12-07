/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:3-random.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-19 23:00
*   Describe:随机函数的测试
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MyRandom(int low, int up)
{
    int ret;
    ret = rand()%up+low; 
    return ret;
}

int main()
{
    srand((unsigned)time(NULL));
    printf("%d\n", MyRandom(1, 5)); 
    printf("%d\n", MyRandom(1, 5)); 
    printf("%d\n", MyRandom(1, 5)); 
    return 0;
}
