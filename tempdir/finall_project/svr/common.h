#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <sys/types.h>			
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include "camera_pthread.h"
#include <sqlite3.h>
#include "camera.h"
#include "M0.h"

void cli_command(int *c_fd);   //处理客户端命令

//cam    
int init_cam(char *, char *);//初始化摄像头

//lcd
void *init_lcd(void *args);//初始化lcd

//m0
void *init_m0(void *args);//初始化m0

#endif	//__COMMON_H__
