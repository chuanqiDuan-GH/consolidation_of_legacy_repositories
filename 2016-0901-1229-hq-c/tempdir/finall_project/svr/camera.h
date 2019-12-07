/*************************************************************************
    > File Name: camera.h
    > Author: huang yang
    > Mail: huangyangwork@sina.com 
    > Created Time: 2016年12月07日 星期三 19时11分43秒
 ************************************************************************/
#ifndef  __CAMERA_H_
#define  __CAMERA_H_

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "camera.h"
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
#include <semaphore.h>

#define CAMERA_DEV_FILE_LENGTH   256
#define START(filename)    start("/dev/video1",filename)
#define RATE 50000
#define IMAGE_WIDTH  640
#define IMAGE_HEIGHT 480

enum ERRO_CODE
{
	INVALID_INPUT = -2,
};

typedef struct BUFFER {
	unsigned int length;
	void *start;
}BUF;

typedef struct {
	unsigned short bfType;
	unsigned long  bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned long  bfoffbits;
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

int  start(char *,char *);//开始摄像头的外部接口
void *start_camera(void *);//开始摄像头的线程开始函数
int stop(void);//关闭摄像头的外部接口
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
void add_bmphead(int);//向bmp文件写入文件头
void input_rgb(unsigned char,unsigned char ,unsigned char);//转换格式写入buf
void yuyv2rgb(int);//格式转换
int init_sem(void);//初始化信号量
int condition; //控制采集信息循环的变量
char path_buf[CAMERA_DEV_FILE_LENGTH];//传入的设备文件名和信息存储路径名
pthread_t camera_pthread;//摄像头线程的线程号
int fd;//设备文件描述符
int picture_count ;//采集图片的张数
FILE *camera_log_error;//错误日志文件流
int buf_count ;//申请采集信息buf数量
struct BUFFER *buf;//信息采集buf映射信号保存变量
char *filename ;//采集视频保存路径指针
unsigned int gbpos;//每一张图片的像素位置变量
char *bufdata;//rgb像素信息存储buf
unsigned int bufdata_length;//rgb像素信息存储你buf长度

sem_t sem_camera;//摄像头访问bufdata的信号量
sem_t sem_lcd;//lcd访问bufdata的信号量

#endif 
