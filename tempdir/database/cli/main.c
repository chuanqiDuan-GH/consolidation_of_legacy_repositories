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

    while(gets(cmd) != NULL)
    {
	bzero(cmd_buf, CMD_LEN);

	if(!strcasecmp(cmd, "connect"))
	{
	    do_connect(&s_fd);
	}
	else if(!strcasecmp(cmd, "signup") && (0 == cmd_flag))
	{
	    //to fin
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
	else if(!strcasecmp(cmd, "signin") && (0 == cmd_flag))
	{
	    //to fin	
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
	else if(!strcasecmp(cmd, "bye") && (0 == cmd_flag))
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
	else if(!strcasecmp(cmd, "insert") && (1 == cmd_flag))
	{
	    strcpy(cmd_buf, "insert");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send insert cmd err\n"); 
	    }

	    do_insert(s_fd);
	}
	else if(!strcasecmp(cmd, "delete") && (1 == cmd_flag))
	{
	    strcpy(cmd_buf, "delete");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send delete cmd err\n"); 
	    }

	    do_delete(s_fd);
	}
	else if(!strcasecmp(cmd, "show") && (1 == cmd_flag))
	{
	    strcpy(cmd_buf, "show");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send show cmd err\n"); 
	    }
	    do_show(s_fd);
	}
	else if(!strcasecmp(cmd, "signout") && (1 == cmd_flag))
	{
	    strcpy(cmd_buf, "signout");
	    ret = send(s_fd, cmd_buf, strlen(cmd_buf), 0);
	    if(-1 == ret)
	    {
		printf("send signout cmd err\n"); 

	    }
	    do_signout();
	}
	else
	{
	    printf("abnormal command\n");	
	}
    }
    return 0;
}
