#include "common.h"
#include "command.h"

void *cli_command(void *c_fd)
{
    fd=*(int *)c_fd;
    int ret=-1;

    pthread_detach(pthread_self()); //分离线程

    //创建数据库
    if(sqlite3_open("./account.db", &account))
    {
	printf("error:%s\n", sqlite3_errmsg(account));
	return;
    }

    //创建表
    const char *sql = "CREATE TABLE IF NOT EXISTS account(name VARCHAR(64), passwd INTEGER);";
    if (sqlite3_exec(account,sql,NULL,NULL,&errmsg) != SQLITE_OK)    
    {    
	printf("%s\n",errmsg);    
	sqlite3_close(account);    
	return;    
    }

    //处理注册表(表中数据包含account和passwd)的操作
    while(1)
    {	
	printf("waiting for client command\n");
	bzero(buf,BUF_SIZE);
	ret=recv(fd,buf,BUF_SIZE,0);	//接收client发来的操作命令
	if(ret<0)
	{
	    perror("recv command");
	    send(fd,"no",2,0);
	    continue;
	}
	else if(strcmp(buf,"signup")==0)    //注册
	{
	    signup();
	}
	else if(strcmp(buf,"signin")==0)    //登录
	{
	    signin();
	}
	else if(strcmp(buf,"bye")==0)	//退出
	{
	    break;
	}

	if(success) //登录成功后才可以进行其他操作
	{
	    success=0;
	    function();	//数据获取与用户操作
	}
	//处理client异常退出
	if(ret==0)
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
    int ret=-1;
    char temp_buf[TEMP_SIZE]="";
    int i;
    send(fd,"ok",2,0);	//确认消息
    bzero(&accbuf,sizeof(Account));

    //接收客户端注册表数据
    recv(fd,&accbuf,sizeof(Account),0);

    //查询数据
    bzero(temp_buf,sizeof(temp_buf));
    printf("%s\n", accbuf.name);
    sprintf(temp_buf,"select * from account where name = '%s'", accbuf.name);
    printf("%s %d\n", __func__, __LINE__);
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
	    sprintf(temp_buf,"insert into account(name,passwd) VALUES('%s', '%s')",accbuf.name,accbuf.passwd);
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
    int ret=-1;
    char getpasswd[10]="";
    char temp_buf[TEMP_SIZE]="";
    send(fd,"ok",2,0);
    bzero(&accbuf,sizeof(Account));

    //接受客户端传过来的用户登录信息
    recv(fd,&accbuf,sizeof(Account),0);

    bzero(temp_buf,sizeof(temp_buf));
    sprintf(temp_buf,"select * from account where name = '%s' and passwd = '%s'", accbuf.name, accbuf.passwd);
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

void open_cam()
{

    //to do
}

void close_cam()
{

    //to do
}

void get_env_data()
{

    //to do
}
void get_run_time()
{

    //to do
}
void get_cam_data()
{
    //to do
}

void init_lcd()
{
    //to do
}

void send_pic_lcd()
{
    //to do
}

void recv_env_m0()
{
    //to do
}

void init_cam()
{
    //to do
}

void recv_pic_cam()
{
    //to do
}

int function()
{	
    char temp_buf[TEMP_SIZE]="";
    int ret=-1;
    char cmBuf[SIZE]="";

    //登录后的用户操作
    while(1)
    {
	bzero(cmBuf,BUF_SIZE);
	ret = recv(fd,cmBuf,BUF_SIZE,0);

	if(strcmp(cmBuf, "opencam") == 0)
	{
	    open_cam();
	}
	else if(strcmp(cmBuf, "closecam") == 0)
	{
	    close_cam(); 
	}
	else if(strcmp(cmBuf, "getenv") == 0)
	{
	    get_env_data();
	}       
	else if(strcmp(cmBuf, "getrtime") == 0)
	{	
	    get_run_time(); 
	}
	else if(strcmp(cmBuf, "getcam") == 0)
	{
	    get_cam_data();	
	}
	//处理当用户在登录成空后的强制退出操作
	if(ret ==0)
	{
	    break;
	}   
    }
}
