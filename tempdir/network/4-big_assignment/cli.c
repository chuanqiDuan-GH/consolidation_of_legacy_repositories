#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//#include "common.h"

#define SD_SIZE 16
#define RC_SIZE 4096

typedef struct _Data
{
    char rc_buf[RC_SIZE];
    int f_size;
}Data, *pData;

int main(int argc, char *argv[])
{
    int sd_fd;	//send
    int dst_fd;	//destnation
    int c_ret;	//connect
    int wr_ret;	//write
    int rf_size;
    int flag = 1;
    ssize_t s_ret;  //send
    ssize_t r_ret;  //recv

    struct sockaddr_in sd_addr; 
    Data data;
    int sd_len = sizeof(struct sockaddr_in);
    char sd_buf[SD_SIZE] = "";
    //char rc_buf[RC_SIZE] = "";

    //zero setting
    bzero(&sd_addr, sd_len);
    bzero(&data, sizeof(Data));

    //assignment
    sd_addr.sin_family = AF_INET;
    sd_addr.sin_port = htons(9527);
    inet_pton(AF_INET, "127.0.0.1", &sd_addr.sin_addr);

    //socket
    sd_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sd_fd)
    {
	printf("socket failed!\n"); 
	return -1;
    }

    //connect
    c_ret = connect(sd_fd, (struct sockaddr *)&sd_addr, sd_len); 

    //从命令行输入要打开的文件名
    strcpy(sd_buf ,argv[1]);

    //send filename
    s_ret = send(sd_fd, sd_buf, sizeof(sd_buf), 0);
    if(-1 == s_ret)
    {
	printf("send filename failed!\n"); 
	return -1;
    }
    
    //recv data
    do
    {
	r_ret = recv(sd_fd, &data, sizeof(Data), 0); 
	if(-1 == r_ret)
	{
	    printf("recv failed!\n"); 
	    return -1;
	}
	//printf("%d\n", data.f_size);
	
	if(flag)
	{
	    rf_size = data.f_size;
	    printf("%d\n", rf_size);
	    flag = 0;
	    rf_size -= RC_SIZE;
	}

	//文件不存在返回处理
	if(!strcmp("file not exist", data.rc_buf))
	{
	    printf("%s\n", data.rc_buf);
	    return -1;
	}

	//接收download的文件
	dst_fd = open("./recvFile", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if(dst_fd < 0)
	{
	    printf("open source failed.\n");
	    return -1; 
	}

	//write data
	wr_ret = write(dst_fd, data.rc_buf, RC_SIZE);
	if(-1 == wr_ret)
	{
	    printf("write file failed.\n");	
	    return -1;
	}
    }while(0 <= (rf_size -= RC_SIZE));

    //关闭文件描述符
    close(sd_fd);
    close(dst_fd);
    return 0;
}
