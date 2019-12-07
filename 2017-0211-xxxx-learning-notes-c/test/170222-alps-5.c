/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:170222-alps-5.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-02-27 08:53
*   Describe:阿尔卑斯通信选择题
********************************************************/
#include <stdio.h>

void  MySubFunc(int *array, int n)
{
    int myArray[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x0};
    //array[n] = myArray[n];
}

void MyFunc()
{
   unsigned char tstArray[10] = {0}; 
   int n = 0;
   for(; n<10; n++)
   {
	MySubFunc((int*)tstArray, n); 
   }
}

void main()
{
    MyFunc();
}

/********************************************************
A.MySubFunc中，myArray是局部变量，其中的值不能返回给调用者
B.MySubFunc中，对myArray的操作回越界
C.MySubFunc中，对array的操作会越界
D.MyFunc中，tstArray初始化操作错误
解析：答案为C
打开15行的注释，编译不会出错，运行会报错stack smashing detected
********************************************************/






















