#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main()
{
    //创建一个子进程
    pid_t pid = -1;
    pid = fork();
    if(pid > 0)
    {
	exit(0); 
    }
    if(pid == -1)
    {
	return -1;
    }
#if 0
    if(pid > 0)
    {
	exit(0); 
    }
    else if(pid < 0)
    {
	exit(1); 
    }
#endif

    //创建新会话（脱离控制终端，登录进程组和会话）
    setsid();
#if 0
    if(pid > 0)
    {
	exit(0); 
    }
    else if(pid < 0)
    {
	exit(1); 
    }
#endif

    //关闭从创建该子进程的父进程那继承的文件
    for(int i=0; i < getdtablesize(); i++)
    {
	close(i); 
    }

    //进程活动时，其工作目录所在的文件系统不能卸下，改变工作目录到/tmp
    chdir("/");

    //重设文件创建掩码
    umask(0);

    sleep(10);
    return 0;
}
