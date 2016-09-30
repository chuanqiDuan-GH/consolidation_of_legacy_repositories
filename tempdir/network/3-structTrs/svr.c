#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdlib.h>
#include <pthread.h>

void *ThreadFunc(void *arg);

int main()
{
    //char ipaddr[40]="";
    struct sockaddr_in s_addr, c_addr;
    int rev;
    int sfd, cfd;
    int s_len = sizeof(s_addr);
    int c_len = sizeof(c_addr);
    int i = 0;
    pthread_t tID;

    //结构体清零
    bzero(&s_addr, s_len);
    bzero(&c_addr, c_len);

    //设置地址结构
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(6666); 
    inet_pton(AF_INET, "127.0.0.1",&s_addr.sin_addr);

    //定义socket描述符
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("rev %d\n", sfd );

    //绑定ip port address
    rev = bind(sfd, (struct sockaddr *)&s_addr, s_len);
    printf("bind %d\n",rev);

    //在端口上监听用户的访问
    listen(sfd, 5);

    while(1)
    {
	//接收客户端的连接请求
	cfd = accept(sfd, (struct sockaddr *)&c_addr, &c_len);
	if(cfd < 0)
	{
	    perror("Err in accept\n");
	    exit(1);
	}

	//与客户端通信
	//write read
	//recv send
	//创建线程
	if(0 != pthread_create(&tID, NULL, ThreadFunc, (void *)&cfd))
	{
	    printf("create pthread err\r\n");
	    return -1;
	}
	//让主线程阻塞等待子线程结束
	//pthread_join(tID, NULL);
	//分离线程，不分离运行时表面上看起来没有区别，但是线程结束后资源不会自动释放与回收
	pthread_detach(tID);
    }

    close(sfd);
    return 0;
}

//线程调用函数
void *ThreadFunc(void *arg)
{
    if(NULL == arg)
    {
	return   (void *)NULL;
    }
    int rev;
    //char rbuf[50] = "";  
    int cfd = *(int *)arg;
    typedef struct _ST
    {
	char c1[5];
	char c2[4];
	int n;
    }ST;
    //int ret;
    ST rbuf;
    rev = recv(cfd, &rbuf, sizeof(ST), 0);
    //ret = atoi(rbuf);
    printf("recv from client value %s %s %d\n", rbuf.c1, (rbuf.c2), rbuf.n);

    send(cfd, "thankyou", 8, 0);
    close(cfd);
}
