#include <stdio.h>
#include "common.h"
#include "command.h"
#include "menu.h"

int main()
{
    char cmd[CMD_LEN] = "";
    int s_fd;
    cmd_flag = 0;
    char cmd_buf[CMD_LEN] = "";
    int ret;
    int f_ret;

    bzero(cmd, CMD_LEN);
    bzero(cmd_buf, CMD_LEN);

    //操作命令判定,
    while(gets(cmd) != NULL)
    {
	bzero(cmd_buf, CMD_LEN);

	if(!strcasecmp(cmd, "connect"))	//连接
	{
	    do_connect(&s_fd);
	}
	else if(!strcasecmp(cmd, "signup") && (0 == cmd_flag))	//注册
	{
	    strcpy(cmd_buf, "signup");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send signup cmd err\n"); 
	    }

	    f_ret = do_signup(s_fd);  
	    if(-1 == f_ret)
	    {
		printf("signup failure in main func\n");
		continue;	
	    }
	}
	else if(!strcasecmp(cmd, "signin") && (0 == cmd_flag))	//登陆
	{
	    strcpy(cmd_buf, "signin");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send signup cmd err\n"); 
	    }

	    f_ret = do_signin(s_fd);  
	    if(-1 == f_ret)
	    {
		printf("signin failure in main func\n");
		continue;	
	    }
	}
	else if(!strcasecmp(cmd, "bye") && (0 == cmd_flag)) //断开与服务端连接
	{
	    strcpy(cmd_buf, "bye");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send bye cmd err\n"); 
		continue;
	    }
	    do_bye();
	    return 0;
	}
	else if(!strcasecmp(cmd, "insert") && (1 == cmd_flag))	//向用户数据表中插入数据
	{
	    strcpy(cmd_buf, "insert");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send insert cmd err\n"); 
	    }
	    do_insert(s_fd);
	}
	else if(!strcasecmp(cmd, "delete") && (1 == cmd_flag))	//删除数据
	{
	    strcpy(cmd_buf, "delete");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send delete cmd err\n"); 
	    }
	    do_delete(s_fd);
	}
	else if(!strcasecmp(cmd, "show") && (1 == cmd_flag))	//显示数据
	{
	    strcpy(cmd_buf, "show");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send show cmd err\n"); 
	    }
	    do_show(s_fd);
	}
	else if(!strcasecmp(cmd, "signout") && (1 == cmd_flag))	//注销登录
	{
	    strcpy(cmd_buf, "signout");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send signout cmd err\n"); 
	    }
	    do_signout();
	}
	else	//错误命令处理
	{
	    printf("abnormal command\n");	
	}
    }
    return 0;
}
