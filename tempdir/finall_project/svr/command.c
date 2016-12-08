#include "common.h"
#include "command.h"

void *cli_command(void *c_fd)
{
    fd=*(int *)c_fd;
    int ret=-1;

    pthread_detach(pthread_self()); //分离线程
    mysql_init(&conn);	//初始化数据库

    //连接数据库
    if( mysql_real_connect(&conn,"localhost","root","1","bracelet",0,NULL,0) )
    {
	printf("connect ok\n");
    }

    //处理注册表(表中数据包含account和passwd)的操作
    while(1)
    {	
	printf("please input command\n");
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

#if 1
	if(success) //登录成功后才可以进行其他操作
	{
	    success=0;
	    function();	//用户数据表操作函数
	}
	//处理client异常退出
#endif
	if(ret==0)
	{
	    break;
	}
    }
    close(fd);
    pthread_exit(0);
}

int signup()
{	
    int ret=-1;
    char temp_buf[TEMP_SIZE]="";
    int i;
    send(fd,"ok",2,0);	//确认消息
    bzero(&accbuf,sizeof(Account));

    //接收客户端注册表数据
    recv(fd,&accbuf,sizeof(Account),0);

    /*
       根据用户名查询要登录的帐号是否存在
       这个动组由三个步骤完成,query()查询,store_result()存储查询结果,num_rows()验证结果
       查询验证三步(1)
     */
    sprintf(temp_buf,"select * from account where name ='%s'",accbuf.name); //组合mysql命令
    ret = mysql_query(&conn,temp_buf);	//mysql_query()函数用来对数据库执行各种操作
    if(ret != 0)
    {
	perror("mysql_query");
	send(fd,"no",2,0);
	printf("%d signup no\n",__LINE__);
	return -1;
    }


    //查询验证三步(2)
    res_ptr = mysql_store_result(&conn);    //获得mysql_query()的结果并保存下来供后续操作
    if(res_ptr ==NULL )
    {
	perror("mysql_store_result");
	send(fd,"no",2,0);
	printf("%d signup no\n",__LINE__);
	return -1;
    }

    //查询验证三步(3)
    //返回查询结果的行数,如果返回大于1的值，证明要注册的帐号已经存在
    ret = mysql_num_rows(res_ptr);  
    if(ret != 0)
    {
	send(fd,"no",2,0);
	printf("%d signup no\n",__LINE__);
	return -1;
    }

    /*
       通过mysql_query()执行调用 mysql_store_result()存储调用那个结果 mysql_num_rows()查询是否已存在
       一系列操作,已经可以确定是否可以插入新帐号,下面即执行插入新帐号操作
     */
    bzero(temp_buf,sizeof(temp_buf));
    sprintf(temp_buf,"insert into account values('%s',%s)",accbuf.name,accbuf.passwd);
    ret=mysql_query(&conn,temp_buf);
    if(ret==0)
    {
	send(fd,"ok",3,0);
	printf("%d signup OK\n",__LINE__);
    }
    else
    {
	send(fd,"no",2,0);
	printf("%d signup no\n",__LINE__);
    }
    mysql_free_result(res_ptr);
    return 0;
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
    printf("%d get account \n",__LINE__);

    /*
       根据用户名查询要登录的帐号是否存在
       这个动组由三个步骤完成,query()查询,store_result()存储查询结果
       fetch_row()通过name获取passwd
       查询获取三步(1)
     */
    sprintf(temp_buf,"select * from account where name='%s'",accbuf.name);
    ret = mysql_query(&conn,temp_buf);
    if(ret != 0)
    {
	perror("mysql_query");
	send(fd,"no",2,0);
	printf("%d signin no\n",__LINE__);
	return -1;
    }
    //存储查询结果
    //查询获取三步(2)
    res_ptr = mysql_store_result(&conn);

    if(res_ptr == NULL )
    {
	perror("mysql_store_result");
	send(fd,"no",2,0);
	printf("%d signin no\n",__LINE__);
	return -1;
    }

    //通过name获取passwd
    //查询获取三步(3)
    sqlrow = mysql_fetch_row(res_ptr);
    if(sqlrow==NULL)
    {
	send(fd,"no",2,0);
	printf("%d signin no\n",__LINE__);
	return -1;
    }
    else
    {
	strcpy(getpasswd,sqlrow[1]);
	printf("passwd=%s\n",sqlrow[1]);
    }

    //对比用户输入的密码,正确通过,反之不通过
    if(strcmp(getpasswd,accbuf.passwd)==0)
    {
	success=1;
	bzero(name,SIZE);
	//验证成功的同时，会将用户名保存在name变量中做后续使用
	strcpy(name,accbuf.name);
	send(fd,"ok",2,0);
	printf("%d signin ok\n",__LINE__);
    }
    else
    {
	send(fd,"no",2,0);
	printf("passwd=%s\n",sqlrow[1]);
    }
    mysql_free_result(res_ptr);
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

#if 0
    //在做对应处理之前,先会验证登录的用户是否已有对应的用户数据表，如果没有则创建
    //显示已有的表(注册信息表和用户信息表在统一个数据库下)
    ret=mysql_query(&conn,"show tables");
    if(ret != 0)
    {
	perror("mysql_query");
	send(fd,"no",2,0);
	return -1;
    }
    res_ptr = mysql_store_result(&conn);
    if(res_ptr ==NULL )
    {
	perror("mysql_store_result");
	send(fd,"no",2,0);
	return -1;
    }

    /*遍历从res_ptr结果中取出show tabels操作的结果(这里的结果是取出了当前库中所有表的名字),
      sqlrow[0]代表第一个用户名,逐一拿到之后与当前客户端所输入的用户名作对比,
      之后会有两种处理逻辑:
      1->
      在遍历table表的名字过程中找到了登录所对应的用户名(即与name比较后相同),
      说明当前账户对应的用户数据表已经存在,不用新建对应表
      2->
      遍历完后没有在table中找到对应登录用户回数据表名,所以sqlrow等于NULL,
      这时就需要为当前用户创建一个对应的用户数据表
     */
    //处理逻辑1->
    while(sqlrow = mysql_fetch_row(res_ptr))
    {
	if(strcmp(name,sqlrow[0])==0)
	{
	    break;
	}
    }
    //处理逻辑2->
    if(sqlrow == NULL )
    {
	//创建用户数据表
	sprintf(temp_buf,"create table %s (time varchar(10) not null primary key,step varchar(16),km varchar(8),sleep varchar(8))",name);
	ret = mysql_query(&conn,temp_buf);
	if(ret != 0)
	{
	    perror("mysql_query");
	    send(fd,"no",2,0);
	    return -1;
	}
    }
    mysql_free_result(res_ptr);
#endif

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

