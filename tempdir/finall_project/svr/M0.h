#ifndef __MM__
#define __MM__

#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <error.h>

#define BUF_SIZE 36

typedef struct Display
{
        int tmp ;//温度
        int hum ;//湿度
        int lig ;//光照
        int led ;
        int fan ;
        int buzz ;
}Display;//环境数据

typedef struct fLags
{
        int f1;
        int f2;
        int f3;
        int f4;
        int f5;
        int f6;
}fLags;//判断数据是否过大

fLags flags;

static char write_buf[5] = {0xdd,0x05,0x24,0x00,0x00};

int M0_init();
void M0_ctrl(int M0_fd, int ctrl);
int M0_flags(int data, int datalow, int datahig, int flags);
void M0_read(int M0_fd);
void M0_close(int M0_fd);

#endif //_MM_H_
