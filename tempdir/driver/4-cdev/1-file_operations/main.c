#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd;
    
    fd = open("/dev/cdev1", O_RDWR);
    if(-1 == fd)
    {
	perror("open"); 
	return -1;
    }

    close(fd);
    
    return 0;
}
