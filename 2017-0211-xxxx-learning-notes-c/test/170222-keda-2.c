/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:170222-keda-2.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-24 08:43
 *   Describe:苏州科达上海研发部笔试
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buff[] = {'h', 'e', 'l', 'l', 'o', '\0'};

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

void main()
{
    printf("%s\r\n", fun1());
    printf("%s\r\n", fun2());
    printf("%s\r\n", fun3());
    printf("%s\r\n", fun4());
} 

/********************************************************
解析：fun1输出hello，fun2输出乱码，fun3输出hello，fun4输出hello
fun1中hello存放在内存的全局区（静态区），生命周期为整个程序结束前，虽然变量ptr是存储在栈区，fun1结束时会被销毁，但不会影响内存中的hello，所以返回打印hello
fun2申请的空间在栈区，所以存储在栈区的hello在函数fun2结束时被销毁，所以打印乱码
fun3申请的空间在堆区，生命周期持续到整个程序结束，所以打印hello
fun4指向的buff存储在内存的全局区，所以返回打印hello
 ********************************************************/
