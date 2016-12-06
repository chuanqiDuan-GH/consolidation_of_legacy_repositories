/*用fread()读取文件时需要注意上次读取在buf中遗留的数据的处理
  用fwrite()从buf中写出数据到文件描述符指向的空间时，fwrite()可以接受fread()的返回值
  作为参数，但要注意最后一次读buf时，可能会有问题，在每次读取前清空缓存即可*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    if(3 != argc)
    {
	printf("wrong input\n");
	return -1;	
    }

    FILE *rf = fopen(argv[1], "r");
    if(!rf)
    {
	printf("open read file failure\n");
	return -1;
    }
    FILE *wf = fopen(argv[2], "w+");
    if(!wf)
    {
	printf("open write file failure\n");
	return -1;	
    }
    
    char buf[200] = "0";
    while(fgets(buf, sizeof(buf), rf) != NULL)
    {
	fputs(buf, wf); 
    }

    return 0;

}
