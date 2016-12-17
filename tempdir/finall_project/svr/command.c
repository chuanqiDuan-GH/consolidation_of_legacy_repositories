#include "common.h"
#include "command.h"

Display display;
int cm_size = sizeof(C2S);
int sm_size = sizeof(S2C);

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
	printf("%d\n", cm_size);
	printf("%d\n", sm_size);

	bzero(&cli_msg, cm_size);
	ret = read(fd, &cli_msg, cm_size);
	//printf("name:%s passwd:%s", cli_msg.name, cli_msg.passwd);
	if(ret<0)
	{
	    perror("recv command");
	    continue;
	}
	else if(cli_msg.cmd == SIGNUP)    //注册
	{
	    printf("SIGNUP\n");
	    signup();
	}
	else if(cli_msg.cmd == SIGNIN)    //登录
	{
	    printf("SIGNIN\n");
	    signin();
	}
	else if(cli_msg.cmd == GETCAM)
	{
	    get_vdo_cam(&fd);
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
}

int signup()
{	
    int ret = -1;
    char temp_buf[TEMP_SIZE] = "";
    bzero(svr_msg.sure, 10);

    //查询数据
    bzero(temp_buf, sizeof(temp_buf));
    printf("%s %s\n", cli_msg.name, cli_msg.passwd);
    sprintf(temp_buf, "select * from account where name = '%s'", cli_msg.name);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	printf("%d\n", __LINE__);
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
	    printf("%d\n", __LINE__);
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
	    printf("%d\n", __LINE__);
	    strcpy(svr_msg.sure, "registyes");
	    send(fd, &svr_msg, sm_size, 0);
	    return 0;
	}
    }
}

int  signin()
{
    printf("into signin\n");
    int ret = -1;
    char temp_buf[TEMP_SIZE] = "";
    bzero(svr_msg.sure, 10);

    //接受客户端传过来的用户登录信息
    //recv(fd,&cli_msg, cm_size, 0);

    printf("%s %s\n", cli_msg.name, cli_msg.passwd);
    bzero(temp_buf,sizeof(temp_buf));
    sprintf(temp_buf, "select * from account where name = '%s' and passwd = '%s'", cli_msg.name, cli_msg.passwd);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	printf("");
	strcpy(svr_msg.sure, "loginno");
	printf("%d %s\n", __LINE__, svr_msg.sure);
	send(fd, &svr_msg, sm_size, 0);
	printf("%s\n", errmsg); 
	sqlite3_close(account);
	return -1;
    }
    else
    {
	if(nrow > 0)
	{
	    printf("signin success\n");
	    strcpy(svr_msg.sure, "loginyes");
	    send(fd, &svr_msg, sm_size, 0);
	    return 0;
	}
	strcpy(svr_msg.sure, "loginno");
	printf("%d %s\n", __LINE__, svr_msg.sure);
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

void get_vdo_cam(int *ifd)
{
#if 0
    static int n=0;
    char *bmp[]={"1.bmp","2.bmp","3.bmp"};
    if(n>=3)
    {
	n=0;
    }
#endif
    FILE * rd = fopen("/tmp/pict0.bmp","r");

    int len;
    char buf[BUF_SIZE]="";
    while((len=fread(buf,1,sizeof(buf),rd))>0)
    {
	send(*ifd,buf,len,0);
	if(len < sizeof(buf))
	{
	    fclose(rd);
	    bzero(buf,sizeof(buf));
	    break;
	}	     
    }
}

void *init_m0(void *args)
{
    pthread_detach(pthread_self());
    int m0_fd = *(int *)args;
    M0_read(m0_fd);

    pthread_exit(NULL);
}

//automatic processing mechanism自动处理机制
#if 0
void a_p_m()
{
    if(display.tmp > TMPUPPERLIMIT)
    {
	M0_ctrl(*m0_fd, BUZZON);
    }
    if(display.tmp > TMPLOWERLIMIT)
    {
	M0_ctrl(*m0_fd, BUZZON);
    }

    if(display.hum > HUMUPPERLIMIT)
    {
	M0_ctrl(*m0_fd, FANON);
    }
    if(display.hum > HUMLOWERLIMIT)
    {
	M0_ctrl(*m0_fd, FANOFF);
    }

    if(display.hum > LIGUPPERLIMIT)
    {
	M0_ctrl(*m0_fd, LEDOFF);
    }
    if(display.hum > LIGLOWERLIMIT)
    {
	M0_ctrl(*m0_fd, LEDON);
    }
}
#endif
