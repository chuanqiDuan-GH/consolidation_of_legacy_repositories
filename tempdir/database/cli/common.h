#ifndef _COMMOND_H_
#define _COMMOND_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8000

#define CMD_LEN 64
#define SID_LEN 12  //signin data len

typedef struct User_data
{
    char account[SID_LEN]; 
    char passwd[SID_LEN];
}UD, *pUD;

#endif	//_COMMOND_H_
