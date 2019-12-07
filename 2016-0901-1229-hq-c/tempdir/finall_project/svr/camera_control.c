/*************************************************************************
    > File Name: camera_control.c
    > Author: huang yang
    > Mail: huangyangwork@sina.com 
    > Created Time: 2016年12月09日 星期五 10时35分24秒
 ************************************************************************/
//函数功能：开启camera
//函数参数：devname camera设备文件路径名，filename采集图片存储路径名
//返回值  ：成功返回0，失败返回负值
#include"camera.h"
int init_cam(char *devname,char *filename)
{
	if(NULL == devname || NULL == filename)
	{
		return INVALID_INPUT;
	}
	strcpy(path_buf,devname);
	strcat(path_buf,"-");
	strcat(path_buf,filename);
	int ret = pthread_create(&camera_pthread,NULL,start_camera,(void *)path_buf);
	if(ret != 0)
	{
		return -1;
	}
	if(pthread_detach(camera_pthread))
	{
		return -1;
	}
	return 0;

}
int stop(void)
{
//	if(pthread_kill(camera_pthread,SIGCHLD))
//	{
//		return -1;
//	}
	condition = 0;
	return 0;
}
