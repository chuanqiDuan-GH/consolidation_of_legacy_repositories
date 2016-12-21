#include "common.h"
#include "command.h"

int cm_size = sizeof(C2S);  //接收客户端的数据的结构体大小
int sm_size = sizeof(S2C);  //发送给客户端数据的结构体大小

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

    //创建共享内存
    //shmget
    int shmid;
    Display *shmaddr = NULL;
    int key = ftok(FTOK_FILE, IPCKEY);
    printf("%d-----%d\n", __LINE__, key);                                         
    if(-1 == (shmid = shmget(key, SM_SIZE, OPEN_MODE|IPC_EXCL)))
    {
	printf("%s shmget failre!!!\n", __FILE__); 
	return;
    }

    //建立进程与共享内存的联系(映射)
    //shmat
    if(NULL == (shmaddr = (Display *)shmat(shmid, NULL, 0)))
    {
	printf("%s shmmat failure!!!\n", __FILE__); 
	return;
    }

    //客户端指令处理
    while(1)
    {	
	bzero(&cli_msg, cm_size);
	/*接收客户端命令*/
	ret = read(fd, &cli_msg, cm_size);

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
	else if(cli_msg.cmd == GETCAM)	//客户端查看视频
	{
	    printf("GETCAM\n");
	    get_vdo_cam(fd);
	}
	else if(cli_msg.cmd == GETENV)	//给客户端发送环境箱内系
	{
	    printf("GETENV\n");
	    get_env_m0(fd, *shmaddr);
	}
	else if((cli_msg.cmd == CTRLM0) && (cli_msg.dev == LED))    //LED灯控制
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
	else if((cli_msg.cmd == CTRLM0) && (cli_msg.dev == BUZZ))   //蜂鸣器控制
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
	else if((cli_msg.cmd == CTRLM0) && (cli_msg.dev == FAN))    //风扇控制
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
    char temp_buf[SQLCMD_SIZE] = "";
    bzero(svr_msg.sure, 10);

    //查询数据
    bzero(temp_buf, sizeof(temp_buf));
    printf("%s %s\n", cli_msg.name, cli_msg.passwd);
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
    printf("into signin\n");
    int ret = -1;
    char temp_buf[SQLCMD_SIZE] = "";
    bzero(svr_msg.sure, 10);

    printf("%s %s\n", cli_msg.name, cli_msg.passwd);
    bzero(temp_buf,sizeof(temp_buf));
    sprintf(temp_buf, "select * from account where name = '%s' and passwd = '%s'", cli_msg.name, cli_msg.passwd);
    if(sqlite3_get_table(account, temp_buf, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
    {
	printf("");
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

void get_env_m0(int e_fd, Display display)
{
    printf("%d-----%d %d %d\n", __LINE__,  display.tmp, display.hum, display.lig);
    bzero(svr_msg.sure, 10);
    svr_msg.tem = display.tmp;
    svr_msg.hum = display.hum;
    svr_msg.light = display.lig;
    strcpy(svr_msg.sure, "envinfo");
    send(e_fd, &svr_msg, sm_size, 0);
}

void get_vdo_cam(int v_fd)
{
    int pic_num = 0;
    char path_header[32] = "/tmp/pict";
    char pic_path[128] = "/0";
    sprintf(pic_path, "%s%d.bmp", path_header, pic_num%1);
    pic_num++;

    FILE *rd = fopen(pic_path,"r");

    int len;
    char buf[VDOPIC_SIZE]="";
    while((len=fread(buf, 1, VDOPIC_SIZE, rd))>0)
    {
	printf("len:%d buf:%d\n", len, sizeof(buf));
	send(v_fd,buf,len,0);
	if(len < sizeof(buf))
	{
	    printf("%d\n", __LINE__);
	    fclose(rd);
	    bzero(buf,sizeof(buf));
	    break;
	}	     
    }
}

void *init_m0(void *args)
{
    printf("%d\n", __LINE__);
    pthread_detach(pthread_self());
    int m0_fd = *(int *)args;
    M0_read(m0_fd);

    pthread_exit(NULL);
}

//automatic processing mechanism自动处理机制
#if 0
void *init_apm(void *args)
{
    pthread_detach(pthread_self());
    int m0_fd = *(int *)args;

    while(1)
    {
	sleep(30);
	if(display.tmp > TMPUPPERLIMIT)
	{
	    M0_ctrl(m0_fd, BUZZON);
	}
	if(display.tmp > TMPLOWERLIMIT)
	{
	    M0_ctrl(m0_fd, BUZZON);
	}

	if(display.hum > HUMUPPERLIMIT)
	{
	    M0_ctrl(m0_fd, FANON);
	}
	if(display.hum > HUMLOWERLIMIT)
	{
	    M0_ctrl(m0_fd, FANOFF);
	}

	if(display.hum > LIGUPPERLIMIT)
	{
	    M0_ctrl(m0_fd, LEDOFF);
	}
	if(display.hum > LIGLOWERLIMIT)
	{
	    M0_ctrl(m0_fd, LEDON);
	}
    }

    pthread_exit(NULL);
}
#endif
