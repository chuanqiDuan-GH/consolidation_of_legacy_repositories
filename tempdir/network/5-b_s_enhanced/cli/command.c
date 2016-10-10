#include "command.h"
#include "common.h"

int do_connect(char *ip, int *sock_fd)
{ 
    struct sockaddr_in sd_addr; 
    int sd_len = sizeof(struct sockaddr_in);
    bzero(&sd_addr, sd_len);
    //printf("%s %s\n", __func__, ip);

    //assignment
    sd_addr.sin_family = AF_INET;
    sd_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &sd_addr.sin_addr);

    *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = connect(*sock_fd, (struct sockaddr *)&sd_addr, sd_len); 
    printf("connect ret:%d\n", ret);
    return ret;
}

int do_get(const char *src, const char *dst, int sock_fd)
{
    char vrf_buf[VRF_LEN] = "";
    int ret;
    char rc_buf[DT_SIZE];

    //接受验证消息，交互四次握手(2)
    ret = recv(sock_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv verify message err\n"); 
	return -1;
    }
    printf("vrf_buf:%s\n", vrf_buf);
    //处理验证消息，ok或no
    if(!strcasecmp(vrf_buf, "no"))  //no处理
    {
	return -1;	 
    }
    else if(!strcasecmp(vrf_buf, "ok"))	//ok处理
    {
	//反馈red状态给服务器，准备接受数据
	bzero(vrf_buf, VRF_LEN);
	strcpy(vrf_buf, "red");

	//发送red，交互四次握手(3)
	ret = send(sock_fd, vrf_buf, strlen(vrf_buf), 0);
	//printf("%s\n", vrf_buf);
	if(-1 == ret)
	{
	    printf("send verify message err\n");	
	    return -1;
	}

	//准备接受数据
	//打开文件，没有就创建
	FILE *fp = fopen(dst, "w+");
	if(NULL == fp)
	{
	    printf("file:\t%s can not open to write\n", dst);
	    return -1;;
	}
	else
	{
	    printf("fopen succeed.\n"); 
	}

	// 从服务器接收数据到rc_buf中
	// 每接收一段数据，便将其写入文件中，循环直到文件接收完并写完为止

	bzero(rc_buf, DT_SIZE);	//清空接收buf
	int length = 0;	//recv返回的数据长度

	//循环接收数据, 交互四次握手(4)
	while((length = recv(sock_fd, rc_buf, DT_SIZE, 0)) > 0)
	{
	    //判断是否接收完毕
	    if(!strcasecmp(rc_buf, "fin"))
	    {
		printf("recv data finish\n"); 
		break;
	    }

	    //写入文件
	    if(fwrite(rc_buf, sizeof(char), length, fp) < length)
	    {
		printf("file:%s write failed\n", dst);
		break;
	    }
	    bzero(rc_buf, DT_SIZE);
	}
	//关闭文件指针
	fclose(fp);
	printf("close fp\n");
    }

    //关闭文件描述符
    close(sock_fd);
    printf("close sock_fd\n");

    return ret;
}

int do_put(const char *src, const char *dst, int sock_fd)
{
    char vrf_buf[VRF_LEN] = "";  
    char sd_buf[DT_SIZE];
    int ret;
     
    ret = recv(sock_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv verify message err\n");	
    }
    printf("vrf_buf:%s\n", vrf_buf);

    if(!strcasecmp(vrf_buf, "no"))
    {
	return -1;
    }
    else if(!strcasecmp(vrf_buf, "red"))
    {		 
	FILE *fp = fopen(src, "r");
	if(NULL == fp)
	{
	    printf("File:%s Not Found\n", src);
	}
	else
	{
	    bzero(sd_buf, DT_SIZE);
	    int length = 0;
	    // 每读取一段数据，便将其发送给客户端，循环直到文件读完为止
	    while((length = fread(sd_buf, sizeof(char), DT_SIZE, fp)) > 0)
	    {
		printf("%s\n", sd_buf);
		if(send(sock_fd, sd_buf, length, 0) < 0)
		{
		    printf("Send File:%s Failed./n", sd_buf);
		    break;
		}
		bzero(sd_buf, DT_SIZE);
	    }
	    bzero(vrf_buf, VRF_LEN);
	    strcpy(vrf_buf, "fin");
	    ret = send(sock_fd, vrf_buf, VRF_LEN, 0);
	    if(-1 == ret)
	    {
		printf("send verify message err\n");
		return -1;
	    }
	    printf("%d\n", __LINE__);
	    // 关闭文件
	    fclose(fp);
	    //printf("File:%s Transfer Successful!\n", src);
	}
    }
    return 1;
}

int do_cd(char *path)
{
    int ret;
    char cp[64] = "";

    ret = chdir(path);
    if(-1 == ret)
    {
	printf("chdir err\n");
    }
    //getcwd(cp,64);
    //printf("%s\n", cp);
}

int do_ls(char *path)
{    
    DIR *dir = opendir(path);
    if(!dir)
    {
	printf("open failure\n"); 
	return -1; 
    }

    struct dirent *tmp = NULL;
    while(tmp = readdir(dir))
    {
	printf("%s\n", tmp->d_name);
    }

    closedir(dir);
}

int do_serv_cd(char *path, int sock_fd)
{
    //do nothing
}

int do_serv_ls(char *path, int sock_fd)
{
    char rc_buf[DT_SIZE];
    int ret;
    bzero(rc_buf, DT_SIZE);
    //接收服务器发送过来的文件列表buf
    ret = recv(sock_fd, rc_buf, DT_SIZE, 0);
    if(-1 == ret)
    {
	printf("!ls recv buf err\n"); 
	return -1;
    }
    //打印服务器想查看的目录
    printf("%s\n", rc_buf);

}

int do_bye(int sock_fd)
{
    close(sock_fd);
    return -1;
    //to do
}


