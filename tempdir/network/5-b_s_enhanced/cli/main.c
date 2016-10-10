#include <stdio.h>
#include "common.h"
#include "command.h"

int main( )
{   
    int sock_fd;	//send sock
    int ret; 
    char cline[COMMAND_LINE]="";//缓冲区，存储用户输入的命令
    struct command_line command;//命令结构，存储分解后的命令
    int i, j;

    while(gets(cline) != NULL)/*得到一行命令*/
    {
	//调用input.c程序中的split解析命令    
	//将命令拆分为命令名和参数的形式
	if( (i=split(&command,cline)) == -1)
	{
	    exit(-1);
	}

	//根据命令名作命令处理，比较命令名和每个合法命令，匹配则处理
	if ( strcasecmp(command.name, "get") == 0 )//get命令
	{

	    //发送get xxx xxx命令语句,交互四次握手(1)
	    ret = send(sock_fd, &command, sizeof(struct command_line), 0);
	    if(ret == 0)
		printf("send failed.\n");

	    //函数调用
	    if ( do_get(command.argv1, command.argv2, sock_fd ) == -1)
	    {
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name,"put") == 0)//put命令
	{
	    ret = send(sock_fd, &command, sizeof(struct command_line), 0);
	    if(ret == 0)
		printf("send failed.\n");

	    if ( do_put(command.argv1, command.argv2, sock_fd )  == -1)
	    {
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name, "cd") == 0)//cd命令
	{
	    if ( do_cd(command.argv1) == -1 )
	    {
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name, "!cd") == 0)//!cd命令
	{
	    ret = send(sock_fd, &command, sizeof(struct command_line), 0);
	    if(ret == 0)
		printf("send failed.\n");

	    if ( do_serv_cd(command.argv1,sock_fd) == -1 )
	    {
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name, "ls") == 0)//ls命令
	{
	    if(NULL == command.argv1)
	    {
		printf("please input path\n"); 
		continue;
	    }
	    if ( do_ls(command.argv1) == -1 )
	    {
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name, "!ls") == 0)//!ls命令
	{
	    ret = send(sock_fd, &command, sizeof(struct command_line), 0);
	    if(ret == 0)
		printf("send failed.\n");

	    if ( do_serv_ls(command.argv1, sock_fd) == -1 )
	    {
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name, "connect") == 0)//connect命令
	{
	    ret = send(sock_fd, &command, sizeof(struct command_line), 0);
	    if(ret == 0)
		printf("send failed.\n");

	    if ( do_connect(command.argv1,&sock_fd) == -1 )
	    {
		printf("connect failed\n");
		//exit(1);
	    }
	}
	else if ( strcasecmp(command.name, "bye") == 0)//bye命令
	{
	    ret = send(sock_fd, &command, sizeof(struct command_line), 0);
	    if(ret == 0)
		printf("send failed.\n");

	    if ( do_bye(sock_fd) == -1 )
	    {
		exit(1);
	    }
	    break;//向服务器发送退出请求，跳出循环，退出程序
	}
	else
	{
	    //错误命令，打印程序的用法
	    printf("wrong command\n");
	    printf("usage : command arg1, arg2, ... argn\n");
	}
	printf("myftp$: ");//再次打印提示符号，准备接收新的命令
	fflush(stdout);
    }
    return 0;
}
