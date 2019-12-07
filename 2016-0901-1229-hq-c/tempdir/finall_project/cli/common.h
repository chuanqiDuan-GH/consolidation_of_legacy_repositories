#ifndef _COMMOND_H_
#define _COMMOND_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8000   //端口号

#define CMD_LEN 64  //操作命令的长度
#define SID_LEN 12  //signin data len

//承载注册登录信息的结构体
typedef struct User_data
{
    char account[SID_LEN]; //账号
    char passwd[SID_LEN];   //密码
}UD, *pUD;

#endif	//_COMMOND_H_
