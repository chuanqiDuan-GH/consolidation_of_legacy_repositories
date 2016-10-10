#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>

#define MAX_LINE 1024	//向服务器端发送命令的最大长度
#define PORT 8000   //端口号
#define COMMAND_LINE 256    //用户输入客户端命令的最大长度
#define MAX_LENGTH 64	//  每个参数或命令的最大长度
#define DT_SIZE 1024	//每一次接收数据的大小
#define MAX_ARG 2   //参数个数
#define VRF_LEN 5	//验证消息长度

#if 0
typedef struct _Data
{
    char rc_buf[RC_SIZE];
    int f_size;
}Data, *pData;
Data data;
#endif

#if 0
struct command_line
{
   char *name; 
   char *argv[];
};
#endif

struct command_line
{
    char name[64];
    char argv1[64];
    char argv2[64];
};

int split(struct command_line *cl, char line[]);	//拆分命令

#endif	//_COMMON_H_

