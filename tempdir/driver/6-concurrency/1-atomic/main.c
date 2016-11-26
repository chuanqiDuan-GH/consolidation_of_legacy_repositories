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
    
    getchar();
    ret = read(fd, buf, 32);
    if(-1 == ret)
    {
	perror("read"); 
	close(fd);
	return -1;
    }

    ret = write(fd, "i'm user message", 32);
    if(-1 == ret)
    {
	perror("write"); 
	close(fd);
	return -1;
    }
    
    close(fd);

    return 0;
}
