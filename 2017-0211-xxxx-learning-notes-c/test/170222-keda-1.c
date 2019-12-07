/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170222-keda-1.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-23 20:32
*   Describe:苏州科达上海研发部笔试
********************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void getPtr(char *p)
{
    p = (char *)malloc(20);
    if(NULL != p)
    {
	printf("strcpy\n");
	strcpy(p, "szkdc"); 
    }
}

void main()
{
    char *p = NULL;

    getPtr(p);
    if(NULL == p)
    {
	printf("logging: p get buf failed\n"); 
	return;
    }
    printf("p=%s\n", p);
}
/*********************************************************
输出logging:p get buf failed
解析：
p在getPtr函数内被改变，main函数的p没有改变，
如果想改变main中的p，要么使getPtr函数有返回值，
要么改变getPtr函数的入参为char **p
**********************************************************/
