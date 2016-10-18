#ifndef _common_h_
#define _common_h_

#include <sys/types.h>			
#include <sys/socket.h>
#include<netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include<stdio.h>
#include<mysql/mysql.h>

void * select_option(void * c_fd);  //操作选择函数

#endif

