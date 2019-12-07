#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define BUF_SIZE 20

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
	return -1;
    } 

    int rf_ret = open(argv[1], O_RDONLY, 0666);
    if(rf_ret < 0)
    {
	return -1; 
    }
    int wf_ret = open(argv[2], O_WRONLY, 0666);
    if(wf_ret < 0)
    {
	return -1; 
    }

    char buf[BUF_SIZE] = "0";
    int ret;
    while(0 <  (ret = read(rf_ret, buf, BUF_SIZE)))
    {
	write(wf_ret, buf, BUF_SIZE);
    }

    close(rf_ret);
    close(wf_ret);
    return 0;
}
