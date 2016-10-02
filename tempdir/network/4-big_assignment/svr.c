#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define RC_SIZE 16
#define SD_SIZE 16
typedef struct stat Stat;

int CheckFilename(char *filename);

int main()
{
    int sr_fd;
    int cl_fd;
    int b_ret;
    int l_ret;
    int s_ret;
    int r_ret;
    struct sockaddr_in sr_addr;
    struct sockaddr_in cl_addr;
    int s_len = sizeof(struct sockaddr_in);
    int c_len = sizeof(struct sockaddr_in);
    char rc_buf[RC_SIZE] = "";
    char sd_buf[SD_SIZE] = "";

    //zeor setting
    bzero(&sr_addr, s_len);
    bzero(&cl_addr, c_len);

    //assignment
    sr_addr.sin_family = AF_INET;
    sr_addr.sin_port = htons(9527);
    inet_pton(AF_INET, "127.0.0.1", &sr_addr.sin_addr);

    //sokcet
    sr_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sr_fd)
    {
	printf("socket failed!\n"); 
	return -1;
    }

    //bind
    b_ret = bind(sr_fd, (struct sockaddr *)&sr_addr, s_len);
    if(0 != b_ret)
    {
	printf("bind failed!\n");
	return -1; 
    }

    //listen
    l_ret = listen(sr_fd, 5);
    if(-1 == l_ret)
    {
	printf("listen failed!\n"); 
	return -1;
    }

    while(1)
    {
	//accept
	cl_fd = accept(sr_fd, (struct sockaddr *)&cl_addr, &c_len);
	if(-1 == cl_fd)
	{
	    printf("accept failed!\n");	
	    return -1;
	}

	//recv
	r_ret = recv(cl_fd, rc_buf, RC_SIZE, 0); 
	if(-1 == r_ret)
	{
	    printf("recv failed!\n"); 
	    return -1;
	}

	//检查文件是否存在
	CheckFilename(rc_buf);

	printf("rc_buf:%s\n", rc_buf);

	//send
	strcpy(sd_buf, rc_buf);
	s_ret = send(cl_fd, sd_buf, SD_SIZE, 0);
	if(-1 == s_ret)
	{
	    printf("send filename failed!\n"); 
	    return -1;
	}
    }

    return 0;
}

int CheckFilename(char *filename)
{
    DIR *dir = opendir(".");
    if(!dir)
    {
	printf("open failure\n"); 
	return; 
    }

    //Stat *file_info = (Stat*)malloc(sizeof(Stat));
    Stat *file_info;
    struct dirent *rf = NULL;

    memset(file_info, 0, sizeof(stat));
    //printf("%s\n", filename);
    while(rf = readdir(dir))
    {
	//printf("%s\n", rf->d_name);
	if(!strcmp(filename, rf->d_name))
	{
	    printf("file %s exist.\n", filename);	
	    return 0;
	}
    }

    printf("file not exist.\n"); 
    return -1; 
}

