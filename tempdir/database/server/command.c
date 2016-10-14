#include"common.h"
#include"command.h"


void * select_option(void *c_fd)
{
    fd=*(int *)c_fd;
    int ret=-1;

    pthread_detach(pthread_self()); //分离线程
    mysql_init(&conn);	//初始化数据库

    //链接数据库
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

	if(success) //如果success置1,即可以进行用户数据表(包含time/step/km等数据)的处理
	{
	    success=0;
	    function();	//用户数据表操作函数
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
    //查询获取三步(2)
    //存储查询结果
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

int insert()
{
    bzero(buf,BUF_SIZE);
    recv(fd,buf,BUF_SIZE,0);
    char temp_buf[TEMP_SIZE]="";
    sprintf(temp_buf,"insert into %s values(%s)",name,buf); //look here
    int ret=-1;
    //调用插入语句
    ret = mysql_query(&conn,temp_buf);
    printf(" %d get data\n",__LINE__);
    if(ret != 0)
    {
	perror("mysql_query");
	send(fd,"no",2,0);
	printf(" %d insert no \n",__LINE__);
	return -1;
    }
    else
    {
	send(fd,"ok",2,0);
	printf(" %d insert ok \n",__LINE__);
    }
    return 0;
}

int delet ()
{
    bzero(buf,BUF_SIZE);
    recv(fd,buf,BUF_SIZE,0);
    char temp_buf[TEMP_SIZE]="";
    sprintf(temp_buf,"delete from %s where time =%s",name,buf);
    printf("%s\n", temp_buf);
    int ret=-1;
    //调用删除语句
    ret = mysql_query(&conn,temp_buf);
    if(ret != 0)
    {
	perror("mysql_query");
	send(fd,"no",2,0);
	printf(" %d delet no \n",__LINE__);
	return -1;
    }
    else
    {
	send(fd,"ok",2,0);
	printf(" %d delet ok \n",__LINE__);
    }
    return 0;
}

int show()
{
    char temp_buf[TEMP_SIZE]="";
    sprintf(temp_buf,"select * from %s ",name);
    int ret=-1;
    int i;
    ret = mysql_query(&conn,temp_buf);
    if(ret != 0)
    {
	perror("mysql_query");
	send(fd,"no",2,0);
	printf(" %d show no\n",__LINE__);
	return -1;
    }
    res_ptr = mysql_store_result(&conn);
    if(res_ptr == NULL )
    {
	perror("mysql_store_result");
	send(fd,"no",2,0);
	printf(" %d show no\n",__LINE__);
	return -1;
    }

    while(sqlrow = mysql_fetch_row(res_ptr))
    {	
	for(i=0;i<4;i++)
	{
	    send(fd,sqlrow[i],16,0);
	}
    }
    send(fd,"fin",3,0);
    printf(" %d show ok\n",__LINE__);
    mysql_free_result(res_ptr);
    return 0;
}

int function()
{	
    char temp_buf[TEMP_SIZE]="";
    int ret=-1;
    char vbuf[SIZE]="";

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

    while(sqlrow = mysql_fetch_row(res_ptr))
    {
	if(strcmp(name,sqlrow[0])==0)
	{
	    break;
	}
    }
    if(sqlrow == NULL )
    {
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

    while(1)
    {
	printf("input command\n");
	bzero(vbuf,BUF_SIZE);
	ret = recv(fd,vbuf,BUF_SIZE,0);
	if(strcmp(vbuf,"insert")==0)
	{
	    insert();
	}
	else if(strcmp(vbuf,"delete")==0)
	{
	    delet(); 
	}
	else if(strcmp(vbuf,"show")==0)
	{
	    show();
	}       

	else if(strcmp(vbuf,"signout")==0)
	{	
	    printf("siginout %s\n",vbuf);
	    break;
	}

	if(ret ==0)
	{
	    break;
	}   
    }
    printf("down\n");
}

