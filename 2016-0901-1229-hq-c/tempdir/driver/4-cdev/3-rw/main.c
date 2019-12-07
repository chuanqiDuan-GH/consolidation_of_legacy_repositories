#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

#define SIZE 64

int main()
{
    int fd;
    int ret;
    char buf[SIZE] = {'0'};

    fd = open("/dev/mydev", O_RDWR);
    if(-1 == fd)
    {
	perror("open"); 
	return -1;
    }

    ret = read(fd, buf, SIZE);
    if(-1 == ret)
    {
	perror("read"); 
	//读数据失败，要关闭文件描述符
	close(fd);
	return -1;
    }
    printf("data from kernel space %s\n", buf);

    ret = write(fd, "hi i'm user", 32);
    if(-1 == ret)
    {
	perror("write"); 
	//写数据失败，要关闭文件描述符
	close(fd);
	return -1;
    }
    printf("write %d bytes\n", ret);

    close(fd);

    return 0;
}
