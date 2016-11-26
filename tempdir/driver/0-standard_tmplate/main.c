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

    fd = open("/dev/myDev0", O_RDWR);
    if( -1==fd ) {
	perror("open");
	return -1;
    }

    printf("open successfully!\n");

    getchar();

    close(fd);

    return 0;
}
