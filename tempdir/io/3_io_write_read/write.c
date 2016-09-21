#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	char wri_buf[] = "hello linux";	
	int wri_ret = 0;	
	char red_buf[128] = "";
	int red_ret = 0;		
	fd = open("./a.c", O_TRUNC | O_RDWR);
	
	if(fd < 0)
	{
		printf("open file failure.\n");			
		return -1;
	}
	printf("open file succeed fd=%d.\n", fd);
	
	wri_ret = write(fd, wri_buf, sizeof(wri_buf));	
	lseek(fd, 0, SEEK_SET);	
	red_ret = read(fd, red_buf, 128);
	printf("red_buf=%s\n", red_buf);	
	close(fd);	
	
	return 0;
}
