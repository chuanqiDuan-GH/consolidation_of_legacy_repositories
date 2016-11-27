#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "common.h"

main()
{
    int fd;

    fd = open("/dev/beep",O_RDWR);
    if(fd<0)
    {
	perror("open fail \n");
	return ;
    }

    ioctl(fd,BEEP_ON);
    sleep(2);
    ioctl(fd,BEEP_OFF); 

    close(fd);
}

