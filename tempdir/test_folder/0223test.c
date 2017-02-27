/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:0223test.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-23 15:34
 *   Describe:
 ********************************************************/
#include <stdio.h>
#include <string.h>

char buff[] = {'h', 'e', 'l', 'l', 'o'};

int *test(int arr[])
{
    printf("%d\n", sizeof(arr));
    return arr;
}

char *fun1()
{
    char *ptr = "hello";
    return ptr;
}

char *fun2()
{
    char ptr[32] = {0};
    strcpy(ptr, "hello");
    return ptr;
}

char *fun3()
{
    char *ptr = (char*)malloc(32);
    strcpy(ptr, "hello");
    return ptr;
}

char *fun4()
{
    char *ptr = buff;
    return ptr;
}

int main()
{
#if 0
    int arr[10] = {1, 2, 3}; 
    int *p = test(arr);
    printf("%d %d\n", sizeof(p), p[2]);
#endif    

    printf("%s\r\n", fun1());
    printf("%s\r\n", fun2());
    printf("%s\r\n", fun3());
    printf("%s\r\n", fun4());
    
    return 0;
}
