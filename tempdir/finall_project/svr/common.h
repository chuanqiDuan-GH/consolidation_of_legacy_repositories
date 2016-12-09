#ifndef __COMMON_H__
#define __COMMON_H_

#include <sys/types.h>			
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <sqlite3.h>

void *cli_command(void *c_fd);   //处理客户端命令

#endif	//__COMMON_H__
