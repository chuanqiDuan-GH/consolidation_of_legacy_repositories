#include "common.h"

Display display;

int main()
{	
    struct sockaddr_in src,dest;
    int len_dest=sizeof(struct sockaddr);
    int s_fd, c_fd, ret, m0_fd;
    pthread_t th_lcd = -1;
    pthread_t th_m0 = -1;
    pthread_t pthread = -1;

    bzero(&src, sizeof(struct sockaddr));
    bzero(&dest, sizeof(struct sockaddr));

    //赋值
    src.sin_family=AF_INET;
    src.sin_port=htons(8000);
    inet_pton(AF_INET, "192.168.1.3", &src.sin_addr);

    //返回文件文件描述符
    s_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(s_fd < 0)
    {
	perror("socket");
	return -1;
    }

    //绑定
    ret = bind(s_fd, (struct sockaddr *)&src, sizeof(src));
    if(ret < 0)
    {
	perror("socket");
	return -1;
    }

    //监听
    ret = listen(s_fd, 10);
    if(ret < 0)
    {
	perror("socket");
	return -1;
    }
    m0_fd = M0_init();
    init_cam("/dev/video0", "/tmp/pict"); 
    pthread_create(&th_m0, NULL, init_m0, (void *)&m0_fd);
    pthread_create(&th_lcd, NULL, init_lcd, NULL);    
    while(1)
    {
	//接收客户端连接
	c_fd = accept(s_fd, (struct sockaddr *)&dest, &len_dest);
	if(c_fd < 0)
	{
	    perror("accept");
	    return -1;
	}
	//多进程并发
	if(fork() == 0)
	{
	    cli_command(&c_fd, &m0_fd);	
	}
    }
    return 0;
}
