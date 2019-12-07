#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 64

int main()
{
    int fd;
    int ret;
    char buf[SIZE] = {0};
    pid_t pid;
    fd_set rfds;
    int i;

#ifdef BLOCK
    printf("BLOCK\n");
    fd = open("/dev/hello1", O_RDWR);
#else
    printf("NONBLOCK\n");
    fd = open("/dev/hello1", O_RDWR | O_NONBLOCK);
#endif
    if( -1==fd ) {
	perror("open");
	return -1;
    }

    printf("open successfully!\n");
    
#ifdef BLOCK
	read(fd, buf, 10);
	printf("read: %s\n", buf);
#else
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	FD_SET(0, &rfds);
	printf("before select\n");
	ret = select(fd+1, &rfds, NULL, NULL, NULL);
	printf("after select\n");
	if( -1==ret ) {
	    perror("select");
	    return -2;
	}
	else 
	{
	    for(i=0;i<fd+1;i++) {
		if( FD_ISSET(i, &rfds) ) {
		    read(i, buf, 10);
		    printf("read: %s\n", buf);	
		}
	    }
	}
#endif
    close(fd);

    return 0;
}
