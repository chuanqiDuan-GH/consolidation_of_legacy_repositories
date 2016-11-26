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

    fd = open("/dev/semdev", O_RDWR);
    if( -1==fd ) {
	perror("open");
	return -1;
    }

    pid = fork();
    if(pid<0) { 
	perror("fork");
	close(fd);
	return -1;
    }else if(0==pid) { // child process
	ret = read(fd, buf, 110);
	if( -1==ret ) {
	    perror("read");
	    close(fd);
	    return -2;
	}
	printf("read %d bytes: %s\n", ret, buf);	    
    }
    else { // parent process
	sleep(10);
	ret = write(fd, "hello world", 11);
	if( -1==ret ) {
	    perror("write");
	    close(fd);
	    return -3;
	}
	printf("write %d bytes\n", ret);	
    }

    close(fd);

    return 0;
}
