#include "common.h"

//将一个命令字符串分割为命令参数并存储在command_line中
//成功则返回拆分后的命令参数个数，失败返回-1
//command:存储命令和命令参数的结构体
//line
int split(struct command_line *command, char str[])
{
    int count = 0;
    int i = 0;
    int j = 0;

    bzero(command, sizeof(struct command_line));
    while('\0' != str[i])
    {
	if(' ' == str[i])
	    count++;	
	i++;
    }

    char *ret = strtok(str, " ");
    char *recv[2];

    recv[0] = (char *)malloc(10*sizeof(char));
    recv[1] = (char *)malloc(10*sizeof(char));

    strcpy(command->name, ret);
    //printf("%s\n", command->name);

    for(; j<count; j++)
    {
	ret = strtok(NULL, " ");
	strcpy(recv[j], ret);
    }

    if(count == 2)
    {
	strcpy(command->argv1,recv[0]);
	strcpy(command->argv2,recv[1]);
    }
    else if(count == 1)
    {
	strcpy(command->argv1,recv[0]);
    }

    //printf("%s\n", command->argv1);
    //printf("%s\n", command->argv2);
    return count;
}
