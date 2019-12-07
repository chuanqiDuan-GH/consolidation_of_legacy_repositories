#ifndef _command_h_
#define _command_h_
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




#define MAX_ARG 2
#define MAX_LINE 1024
#define MAX_LENGTH 64
#define NO_FIND_FILE -1
#define BUF_SIZE 1024
typedef struct COMMAND_LINE
{
	char name[MAX_LENGTH];
	char argv1[MAX_LENGTH];
	char argv2[MAX_LENGTH];
}command_line;
int fd;

int do_get(const char *src, const char *dst, int sock_fd);//�����û���PUT����
int do_put(const char *src, const char *dst, int sock_fd);//�����û���GET����
int do_cd(char *path); //�����û���CD����
int do_ls(char *path); //�����û���LS ����
void * select_option(void * c_fd);


#endif
