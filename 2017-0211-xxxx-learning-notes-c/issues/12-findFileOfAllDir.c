/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:12-findFileOfAllDir.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-20 21:11
*   Describe:列出指定目录下的所有文件，包含子目录中的文件
********************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void Traverse(char *sourceFilePath)
{
    DIR *dir = opendir(sourceFilePath);
    struct dirent *ptr;
    if(!dir)
    {
	printf("open error\n"); 
	return;
    }

    while((ptr=readdir(dir)) != NULL)
    {
	if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
	    continue;
	else if(ptr->d_type == DT_REG)
	{
	    printf("reg:%s\n", ptr->d_name);
	}
	else if(ptr->d_type == DT_DIR)
	{
	    printf("dir:%s\n", ptr->d_name);
	    Traverse(ptr->d_name);
	}
    }
    closedir(dir);
}

void main(int argc, char *argv[])
{
    if(argc != 2)
    { 
	printf("parameter error\n");
	return;
    }
    Traverse(argv[1]);
}
