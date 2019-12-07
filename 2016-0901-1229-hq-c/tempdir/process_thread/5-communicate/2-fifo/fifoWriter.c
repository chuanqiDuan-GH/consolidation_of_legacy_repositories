#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE	32
#define MASK	0666

int main(int argc, char *argv[])
{
    int fd;
    char buf[BUFSIZE];

    if(2 != argc)
    {
	printf("error argc\n"); 
	return -1;
    }

    if(mkfifo(argv[1], MASK)<0 && EEXIST != errno)
    {
	perror("error mkfifo\n");
	return -1;
    }
    #if 0
    if(0 > mkfifo(argv[1], MASK))
    {
	printf("error mkfifo\n"); 
	return -1;
    }
    #endif

    fd = open(argv[1], O_WRONLY, MASK);
    if(-1 == fd)
    {
	printf("error open\n"); 
	return -1;
    }

    while(1)
    {
	memset(buf, 0, BUFSIZE);
	gets(buf);
	write(fd, buf, BUFSIZE);
    }

    return 0;
}
