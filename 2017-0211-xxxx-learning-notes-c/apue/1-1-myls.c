/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:1-1-myls.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-03-12 19:55
 *   Describe:shell命令ls的简单实现
 ********************************************************/
#include <stdio.h>
#include <dirent.h>

void main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if(argc != 2)
    {
	printf("parameter error\n");  
	return;
    };

    if((dp = opendir(argv[1])) == NULL)
    {
	printf("can't open %s\n", argv[1]);	
	return;
    }

    while((dirp = readdir(dp)) != NULL)
	printf("%s\n", dirp->d_name); 
    
    closedir(dp);
}

