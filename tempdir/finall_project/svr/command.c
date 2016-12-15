#include "common.h"
#include "command.h"

Display display;

void cli_command(int *c_fd, int *m0_fd)
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
	ret = recv(fd, &cli_msg, cm_size, 0);
	if(ret<0)
	{
	    perror("recv command");
	    continue;
	}
	else if(cli_msg.cmd == SIGNUP)    //注册
	{
	    signup();
	}
	else if(cli_msg.cmd == SIGNIN)    //登录
	{
	    signin();
	}
	else if(cli_msg.cmd == GETCAM)
	{
	    //open_cam();
	    continue;
	}
	else if(cli_msg.cmd == GETENV)
	{
	    get_env_m0();
	}
	else if((cli_msg.cmd == CTRLM0) && (cli_msg.dev == LED))
	{
	    if(cli_msg.ctl)
	    {
		M0_ctrl(*m0_fd, LEDON);
	    }
	    else
	    {
		M0_ctrl(*m0_fd, LEDOFF);
	    }
	}	
	else if((cli_msg.cmd == CTRLM0) && (cli_msg.dev == BUZZ))
	{
	    if(cli_msg.ctl)
	    {
		M0_ctrl(*m0_fd, BUZZON);
	    }
	    else
	    {
		M0_ctrl(*m0_fd, BUZZOFF);
	    }
	}
	else if((cli_msg.cmd == CTRLM0) && (cli_msg.dev == FAN))
	{
	    if(cli_msg.ctl)
	    {
		M0_ctrl(*m0_fd, FANON);
	    }
	    else
	    {
		M0_ctrl(*m0_fd, FANOFF);
	    }
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
    bzero(svr_msg.sure, 10);
    bzero(&cli_msg, cm_size);

    //查询数据
    bzero(temp_buf, sizeof(temp_buf));
    printf("%s\n", cli_msg.name);
    sprintf(temp_buf, "select * from account where name = '%s'", cli_msg.name);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	strcpy(svr_msg.sure, "registno");
	send(fd, &svr_msg, sm_size, 0);
	printf("%s\n", errmsg); 
	sqlite3_close(account);
	return -1;
    }
    else
    {
	if(nrow > 0)
	{
	    strcpy(svr_msg.sure, "registno");
	    send(fd, &svr_msg, sm_size, 0);
	    printf("%s\n", errmsg); 
	    sqlite3_close(account);	
	    return -1;
	}
	else 
	{

	    //插入数据    
	    bzero(temp_buf,sizeof(temp_buf));
	    sprintf(temp_buf,"insert into account(name,passwd) VALUES('%s', '%s')", cli_msg.name, cli_msg.passwd);
	    if(sqlite3_exec(account, temp_buf, NULL, NULL, &errmsg))
	    {
		printf("%s\n", errmsg); 
		sqlite3_close(account);
		return -1;
	    }
	    strcpy(svr_msg.sure, "registyes");
	    send(fd, &svr_msg, sm_size, 0);
	    return 0;
	}
    }
}

int  signin()
{
    int ret = -1;
    char temp_buf[TEMP_SIZE] = "";
    bzero(svr_msg.sure, 10);
    bzero(&cli_msg, cm_size);

    //接受客户端传过来的用户登录信息
    recv(fd,&cli_msg, cm_size, 0);

    bzero(temp_buf,sizeof(temp_buf));
    sprintf(temp_buf, "select * from account where name = '%s' and passwd = '%s'", cli_msg.name, cli_msg.passwd);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	strcpy(svr_msg.sure, "loginno");
	send(fd, &svr_msg, sm_size, 0);
	printf("%s\n", errmsg); 
	sqlite3_close(account);
	return -1;
    }
    else
    {
	if(nrow > 0)
	{
	    strcpy(svr_msg.sure, "loginyes");
	    send(fd, &svr_msg, sm_size, 0);
	    return 0;
	}
	strcpy(svr_msg.sure, "loginno");
	send(fd, &svr_msg, sm_size, 0);	
	return -1;
    }
    return 0;
}

void get_env_m0()
{
    //to do
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
