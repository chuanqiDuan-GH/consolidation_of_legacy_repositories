#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define CDEV_MAGIC  'C'
#define IOCTL_CMD_1 _IO(CDEV_MAGIC, 1)
#define IOCTL_CMD_2 _IOW(CDEV_MAGIC, 2, int)
#define IOCTL_CMD_3 _IO(CDEV_MAGIC, 3)

#define BUF_SIZE 64

int main()
{
    int fd;
    int ret;
    char buf[BUF_SIZE] = {'0'};

    fd = open("/dev/cdev1", O_RDWR);
    if(-1 == fd)
    {
	perror("open");
	return -1; 
    }

    //自定义命令
    ret = ioctl(fd, IOCTL_CMD_1);
    if(ret)
    {
	perror("ioctl"); 
	return -1;
    }

    //自定义带参命令
    ret = ioctl(fd, IOCTL_CMD_2, 666);
    if(ret)
    {
	perror("ioctl"); 
	return -1;
    }
    
    ret = ioctl(fd, IOCTL_CMD_3);
    if(ret)
    {
	perror("ioctl"); 
	return -1;
    }
    
    //读取从kernel传过来的数据
    //kernel通过copy_to_user()传数据到用户层
    ret = read(fd, buf, 64);
    if(-1 == ret)
    {
	perror("read");	 
	close(fd);
	return -2;
    }
    printf("read %d data form kernel :%s\n", ret, buf);

    //写数据到kernel
    //kernel通过copy_from_user()拿到从用户层传过来的数据
    ret = write(fd, "user ioctl data", 15);
    if(-1 == ret)
    {
	perror("write"); 
	close(fd);
	return -3;
    }
    printf("write %d data to kernel\n", ret);

    close(fd);
    return 0;
}
