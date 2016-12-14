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
#include "camera_pthread.h"

#define CAMERA_DEV_FILE_LENGTH   256
#define START(filename)    start("/dev/video1",filename)

enum ERRO_CODE
{
	INVALID_INPUT = -2,
};

void *start_camera(void *);
int stop(void);
int condition;

#endif 
