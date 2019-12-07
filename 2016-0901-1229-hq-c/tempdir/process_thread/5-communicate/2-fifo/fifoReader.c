#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE	32	
#define MASK	0666

int main(int argc, char *argv[])
{
    int fd;
    char buf[BUFSIZE] = {'\0'};
    char tmp[1];
    
    if(argc != 2)
    {
	printf("error argc\n"); 
	return -1;
    }

    if(0 > mkfifo(argv[1], MASK) &&  EEXIST != errno)
    {
	printf("error mkfifo\n");
	return -1;
    }

    fd = open(argv[1], O_RDONLY, MASK);
    if(-1 == fd)
    {
	printf("error open\n"); 
	return -1;
    }

while(1)
{
    memset(buf, 0, BUFSIZE);
    gets(tmp);
    read(fd, buf, BUFSIZE); 
    printf("%s\n", buf);
}

    return 0;
}
