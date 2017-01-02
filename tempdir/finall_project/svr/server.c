#include "common.h"

int main()
{	
    struct sockaddr_in src,dest;
    int len_dest=sizeof(struct sockaddr);
    int s_fd, c_fd, ret, m0_fd;
    int shmid;	//共享内存 
    pthread_t th_lcd = -1;
    pthread_t th_m0 = -1;
    pthread_t th_apm = -1;
    int opt = 1;

    bzero(&src, sizeof(struct sockaddr));
    bzero(&dest, sizeof(struct sockaddr));

    //赋值
    src.sin_family=AF_INET;
    src.sin_port=htons(6666);
    inet_pton(AF_INET, "192.168.1.3", &src.sin_addr);

    //返回文件文件描述符
    s_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(s_fd < 0)
    {
	perror("socket");
	return -1;
    }

    setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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


    m0_fd = M0_init();	//初始化m0
    init_cam("/dev/video0", "/tmp/pict");   //初始化并拉起摄像头
    pthread_create(&th_m0, NULL, init_m0, (void *)&m0_fd);  //拉起m0
    pthread_create(&th_lcd, NULL, init_lcd, NULL);    //初始化并拉起显示屏
    //pthread_create(&th_apm, NULL, init_apm, (void *)&m0_fd);	//拉起自动处理系统
                                                        
    while(1)
    {
	//接收客户端连接
	c_fd = accept(s_fd, (struct sockaddr *)&dest, &len_dest);
	//printf("%d-----%d %d %d\n", __LINE__, display.tmp, display.hum, display.lig);
	if(c_fd < 0)
	{
	    perror("accept");
	    return -1;
	}
	//多进程并发
	if(fork() == 0)
	{
	    printf("waiting for client command\n");
	    cli_command(&c_fd, &m0_fd);	
	}
    }
    return 0;
}
