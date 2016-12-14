#include "common.h"
#include "command.h"

Display display;

void cli_command(int *c_fd)
{
    fd = *c_fd;
    int ret = -1;

    //创建数据库
    if(sqlite3_open("./account.db", &account))
    {
	printf("error:%s\n", sqlite3_errmsg(account));
	return;
    }

    //创建表
    const char *sql = "CREATE TABLE IF NOT EXISTS account(name VARCHAR(64), passwd INTEGER);";
    if (sqlite3_exec(account, sql, NULL, NULL, &errmsg) != SQLITE_OK)    
    {    
	printf("%s\n", errmsg);    
	sqlite3_close(account);    
	return;    
    }

    //处理注册表(表中数据包含account和passwd)的操作
    while(1)
    {	
	printf("waiting for client command\n");
	bzero(cli_buf, CLICMD_BUF);
	ret=recv(fd, cli_buf, CLICMD_BUF, 0);	//接收client发来的操作命令
	if(ret<0)
	{
	    perror("recv command");
	    send(fd, "no", 2, 0);
	    continue;
	}
	else if(strcmp(cli_buf, "signup") == 0)    //注册
	{
	    signup();
	}
	else if(strcmp(cli_buf, "signin") == 0)    //登录
	{
	    signin();
	}
	else if(strcmp(cli_buf, "bye") == 0)	//退出
	{
	    break;
	}

	if(success) //登录成功后才可以进行其他操作
	{
	    success = 0;
	    fun_command();	//数据获取与用户操作
	}
	//处理client异常退出
	if(ret == 0)
	{
	    break;
	}
    }
    close(fd);
    pthread_exit(0);
}

//注册接口实现
int signup()
{	
    int ret = -1;
    char temp_buf[TEMP_SIZE] = "";
    int i;
    send(fd, "ok", 2, 0);	//确认消息
    bzero(&accbuf, sizeof(Account));

    //接收客户端注册表数据
    recv(fd, &accbuf, sizeof(Account), 0);

    //查询数据
    bzero(temp_buf, sizeof(temp_buf));
    printf("%s\n", accbuf.name);
    sprintf(temp_buf, "select * from account where name = '%s'", accbuf.name);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	send(fd, "no", 2, 0);
	printf("%s\n", errmsg); 
	sqlite3_close(account);
	return -1;
    }
    else
    {
	if(nrow > 0)
	{
	    send(fd, "no", 2, 0);	
	    return -1;
	}
	else 
	{
	    send(fd, "ok", 2, 0);
	    //插入数据    
	    bzero(temp_buf,sizeof(temp_buf));
	    sprintf(temp_buf,"insert into account(name,passwd) VALUES('%s', '%s')", accbuf.name, accbuf.passwd);
	    if(sqlite3_exec(account, temp_buf, NULL, NULL, &errmsg))
	    {
		send(fd, "no", 2, 0);
		printf("%s\n", errmsg); 
		sqlite3_close(account);
		return -1;
	    }
	    send(fd, "ok", 2, 0);
	    return 0;
	}
    }
}

int  signin()
{
    int ret = -1;
    char getpasswd[10] = "";
    char temp_buf[TEMP_SIZE] = "";
    send(fd, "ok", 2, 0);
    bzero(&accbuf,sizeof(Account));

    //接受客户端传过来的用户登录信息
    recv(fd,&accbuf,sizeof(Account),0);

    bzero(temp_buf,sizeof(temp_buf));
    sprintf(temp_buf, "select * from account where name = '%s' and passwd = '%s'", accbuf.name, accbuf.passwd);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	send(fd, "no", 2, 0);
	printf("%s\n", errmsg); 
	sqlite3_close(account);
	return -1;
    }
    else
    {
	if(nrow > 0)
	{
	    send(fd, "ok", 2, 0);
	    return 0;
	}
	send(fd, "no", 2, 0);	
	return -1;
    }
    return 0;
}

void get_env_m0()
{
    printf("%d", display.tmp);
    printf("%d", display.hum);
    printf("%d", display.lig);
}

void get_vdo_cam()
{
    //to do
}
void *init_m0(void *args)
{
    pthread_detach(pthread_self());
    int m0_fd = *(int *)args;
    M0_read(m0_fd);

    pthread_exit(NULL);
}

int fun_command()
{	
    char temp_buf[TEMP_SIZE] = "";
    int ret = -1;
    char cmBuf[SIZE] = "";

    //登录后的用户操作
    while(1)
    {
	bzero(cmBuf, CLICMD_BUF);
	ret = recv(fd, cmBuf, CLICMD_BUF, 0);

	if(strcmp(cmBuf, "opencam") == 0)
	{
	    //open_cam();
	}
	else if(strcmp(cmBuf, "closecam") == 0)
	{
	    //close_cam(); 
	}
	else if(strcmp(cmBuf, "getenv") == 0)
	{
	    get_env_m0();
	}       
	else if(strcmp(cmBuf, "getvdo") == 0)
	{
	    get_vdo_cam();	
	}
	//处理当用户在登录成空后的强制退出操作
	if(ret == 0)
	{
	    break;
	}   
    }
}
