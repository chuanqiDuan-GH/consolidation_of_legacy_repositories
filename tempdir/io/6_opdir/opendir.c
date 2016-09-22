#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    //这里opendir的参数如果填'.' 调用时
    DIR *dir = opendir(".");
    if(!dir)
    {
	printf("open failure\n"); 
	return -1; 
    }

    struct dirent *tmp = NULL;
    while(tmp = readdir(dir))
    {
	printf("i'm in read\n"); 
	printf("%s\n", tmp->d_name);
    }

    closedir(dir);
    return 0;
}
