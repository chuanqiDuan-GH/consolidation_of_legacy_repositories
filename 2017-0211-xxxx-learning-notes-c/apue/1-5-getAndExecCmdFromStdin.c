/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:1-5-getAndExecCmdFromStdin.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-03-13 22:49
*   Describe:从标准输入读命令并执行
********************************************************/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 1024

void main(int argc, char *argv[])
{
    char buf[BUFSIZE];
    pid_t pid;//需要<unistd.h>头文件
    int status;

    printf("%% ");//printf requires %% to print %
    while(fgets(buf, BUFSIZE, stdin) != NULL)
    {
	if(buf[strlen(buf) - 1] == '\n')
	    buf[strlen(buf) - 1] = 0;//用NULL替换换行符
	if((pid = fork()) < 0)
	    printf("fork error\n");
	else if(pid == 0)
	{
	    execlp(buf, buf, (char *)0);	
	    printf("could't execute: %s\n", buf);
	    exit(127);//需要<stdlib.h>头文件
	}

	if((pid = waitpid(pid, &status, 0)) < 0)
	    printf("waitpid error\n");
	printf("%% ");
    }
}
