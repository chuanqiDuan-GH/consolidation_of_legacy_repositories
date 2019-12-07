#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SIZE 64

int main()
{
    int fd;
    int ret;
    char buf[SIZE] = {0};
    fd_set rfds;
    int i;

    fd = open("/dev/myDev0", O_RDWR | O_NONBLOCK);
    if( -1==fd ) {
	perror("open");
	return -1;
    }

    printf("open successfully!\n");

    while(1)
    {
	FD_ZERO(&rfds); 
	FD_SET(fd, &rfds);
	FD_SET(0, &rfds);

	printf("before select\n");
	ret = select(fd+1, &rfds, NULL, NULL, NULL);
	printf("after select\n");

	if(-1 == ret){
	    perror("select");
	    return -2;
	}
	else{
	    for(i=0; i<fd+1; i++){
		if(FD_ISSET(i, &rfds)){
		    read(i, buf, 10);	
		    printf("read: %s\n", buf);
		}
	    }
	}
    }

    close(fd);

    return 0;
}
