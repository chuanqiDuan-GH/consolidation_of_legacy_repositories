#include"common.h"

//本程序中,数据库名为bracelet,注册信息表名为account,用户信息表名以用户注册的帐号名为准
int main()
{	
    struct sockaddr_in src,dest;
    int len_dest=sizeof(struct sockaddr);
    int s_fd,c_fd,ret;
    pthread_t pthread = -1;

    bzero(&src,sizeof(struct sockaddr));
    bzero(&dest, sizeof(struct sockaddr));

    //赋值
    src.sin_family=AF_INET;
    src.sin_port=htons(8000);
    inet_pton(AF_INET,"127.0.0.1",&src.sin_addr);

    //返回文件文件描述符
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    if(s_fd<0)
    {
	perror("socket");
	return -1;
    }

    //绑定
    ret = bind(s_fd,(struct sockaddr *)&src,sizeof(src));
    if(ret<0)
    {
	perror("socket");
	return -1;
    }

    //监听
    ret = listen(s_fd,10);
    if(ret<0)
    {
	perror("socket");
	return -1;
    }

    while(1)
    {
	//接收客户端连接
	c_fd = accept(s_fd,(struct sockaddr *)&dest,&len_dest);
	if(c_fd<0)
	{
	    perror("accept");
	    return -1;
	}
	//创建子线程
	pthread_create(&pthread,NULL,select_option,(void *)&c_fd);
	//线程分离，放到调用函数内处理
	//pthread_detach(pthread);
    }
    return 0;
}
