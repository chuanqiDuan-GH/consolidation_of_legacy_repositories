#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>

#define SIZE 64

int fd;
char buf[SIZE] = {0};

//信号处理
void sigio_handler(int signo)
{
    read(fd, buf, SIZE);
    printf("user read:%s\n", buf);
}

int main()
{
    int ret;
    pid_t pid;

    signal(SIGIO, sigio_handler);

    fd = open("/dev/myDev0", O_RDWR | O_NONBLOCK);
    if( -1==fd ) {
	perror("open");
	return -1;
    }
    printf("open successfully!\n");

    //启动信号驱动机制,这两句一定要放在打开文件之后
    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);

    sleep(3);

    while(1);

    close(fd);
    return 0;
}
