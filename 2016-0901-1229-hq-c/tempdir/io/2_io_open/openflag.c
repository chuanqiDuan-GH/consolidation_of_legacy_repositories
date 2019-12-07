#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd;
	fd = open("./a.c", O_CREAT| O_EXCL | O_RDWR, 0777);
	if(fd < 0)
	{
		printf("creat file failure.\n");			
		return -1;
	}
	printf("creat file succeed fd=%d.\n", fd);
	close(fd);	
	
	return 0;
}
