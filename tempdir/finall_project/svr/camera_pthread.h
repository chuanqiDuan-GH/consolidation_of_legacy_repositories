/*************************************************************************
    > File Name: camera_phtread.h
    > Author: huang yang
    > Mail: huangyangwork@sina.com 
    > Created Time: 2016年12月09日 星期五 11时38分32秒
 ************************************************************************/
#ifndef __CAMERA__PTHREAD__
#define __CAMERA__PTHREAD__

#include <stdlib.h>
#include <assert.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <linux/fb.h>
#include <unistd.h>
#include <asm/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include <errno.h>
#include "camera.h"

#define RATE 500000
#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480

typedef struct BUFFER {
	unsigned int length;
	void *start;
}BUF;

typedef struct {
	unsigned short bfType;
	unsigned long  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long bfoffbits;
}BMPFILEHEAD;

typedef struct {
	unsigned long biSize;
	unsigned long biWidth;
	unsigned long biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned long biCompression;
	unsigned long biSizeImage;
	unsigned long biXPelsPerMeter;
	unsigned long biYPelsPerMeter;
	unsigned long biClrUsed;
	unsigned long biClrImportant;
}BMPINFOHEAD;

void log_exit(char *);//出错时打印错误信息并结束线程
void open_device (char *devname);//打开设备文件
int init_device(char *devname);//初始化设备
void query_cap(void);//检查设备能力：查看是否具有V4L2_BUF_TYPE_VIDEO_CAPTURE能力
void set_size(void);//设置图片大小
void ckioctl(int fd,int macro,void *str);//调用ioctl失败直接退出,成功返回
void request_queue(void);//申请内存缓冲区
void init_buf(struct BUFFER ** buf);//初始化缓存映射保存区
void init_mmap(void);//缓冲队列映射
void add_queue(void);//缓存区加入采集等待队列
void start_capture(void);//开启视频采集
void collect_data(void);//采集图片数据

void stop_capture(void);//停止视频数据采集
void close_device(void);//关闭视频设备
void loop_handler(int signum);//sigalrm信号处理采集一张图片
void stop_handler(int signum);//停止信号处理函数
void add_bmphead(int);
void input_rgb(unsigned char,unsigned char ,unsigned char);
void yuyv2rgb(int);
int fd;
int picture_count ;
FILE *camera_log_error;
int buf_count ;
struct BUFFER *buf;
char *filename ;
unsigned int gbpos;
char *bufdata;
unsigned int bufdata_length;

#endif
