/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:10-bigOrLittleEndian.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-23 17:37
 *   Describe:验证大小端
 ********************************************************/
#include <stdio.h>

union temp
{
    short int a;
    char b;
}temp;

int WhichEndian()
{
    short int a = 0x1122;//十六进制，一个数值占4位
    char b = *(char *)&a;//通过将short(2字节)强制类型转换成char单字节，b指向的起始字节(低字节)
    if(b == 0x11)//低字节存的是数据的高字节数据
	return 1;//大端模式    
    else
	return 0;//小端模式
}

/*******************************************************
联合体union的存放顺序是所有成员都从低地址开始存放，
而且所有成员共享存储空间
********************************************************/
int WhichEndian2()
{
    temp.a = 0x1122;
    if(temp.b == 0x11) 
	return 1;
    else
	return 0;
}


void main(int argc, char *argv[])
{
    if(WhichEndian())
	printf("big endian\n");
    else
	printf("little endian\n");


    if(WhichEndian2())
	printf("big endian\n");
    else
	printf("little endian\n");
}
