/*************************************************************************
  > File Name: start_camera.c
  > Author: huang yang
  > Mail: huangyangwork@sina.com 
  > Created Time: 2016年12月09日 星期五 11时05分02秒
 ************************************************************************/
#include"camera.h"
void *start_camera(void *argv)
{
    printf("start pthread\n");
    camera_log_error = fopen("camera_log","w+");
    if(NULL == camera_log_error)
    {
	pthread_exit(0);
    }
    if(NULL == argv)
    {
	log_exit("argv");
    }
    char *devname = NULL;
    devname = strtok(argv,"-");
    filename = strtok(NULL,"-");
    if(NULL == devname || NULL == filename)
    {
	log_exit("strtok argv");
    }

    fd = 0;
    picture_count =0;
    buf_count = 1;
    condition = 1;
    //停止信号处理监听
    //	signal(SIGCHLD,stop_handler);
    //初始化函数
    init_device(devname);

    //申请缓存
    request_queue();
    //初始化缓存映射保存区
    init_buf(&buf);
    //缓冲区映射
    init_mmap();
    //加入缓冲队列
    add_queue();
    //初始化信号量
    init_sem();
    //开启视频采集
    start_capture();
    //定时信号处理
    //	signal(SIGALRM,loop_handler);
    //	ualarm(1,RATE);
    while(condition)
    {
	collect_data();
    }
    /*	while(1)
	{
	sleep(100);
	}   */
    stop_capture();
    close_device();
    return 0;
}

void log_exit(char *error)
{
    fprintf(camera_log_error,"%s error:%s\n",error,strerror(errno));
    close(fd);
    pthread_exit(NULL);
}

void ckioctl(int fd,int macro,void *st)
{
    if(ioctl(fd,macro,st))
    {
	char buf[5]="";
	sprintf(buf,"%0x",macro);
	log_exit(buf);
    }
    return ;
}

int init_device(char *devname)
{
    //打开设备
    open_device(devname);
    //检查设备能力
    query_cap();
    //设置图片大小
    set_size();

}

//打开设备文件
void open_device(char *devname)
{
    fd = open(devname,O_RDWR);
    if(fd<0)
    {
	log_exit("open device");
    }
}

//检查设备能力：查看是否具有V4L2_BUF_TYPE_VIDEO_CAPTURE能力和支持读写能力
void query_cap(void)
{
    struct v4l2_capability cap;
    bzero(&cap,sizeof(cap));
    ckioctl(fd,VIDIOC_QUERYCAP,&cap);
    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
    {
	log_exit("query_cap capture");
    }
    if(!(cap.capabilities & V4L2_CAP_STREAMING))
    {
	log_exit("query_cap streaming");
    }
}

//设置采集图片大小
void set_size(void )
{
    struct v4l2_format format;
    bzero(&format,sizeof(format));
    format.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width=IMAGE_WIDTH;
    format.fmt.pix.height=IMAGE_HEIGHT;
    format.fmt.pix.pixelformat=V4L2_PIX_FMT_YUYV;
    format.fmt.pix.field=V4L2_FIELD_NONE;
    ckioctl(fd,VIDIOC_S_FMT,&format);
}

//申请内存缓冲区
void request_queue(void)
{
    struct v4l2_requestbuffers  buffers;
    bzero(&buffers,sizeof(buffers));
    buffers.count = buf_count;
    buffers.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffers.memory = V4L2_MEMORY_MMAP; 
    ckioctl(fd,VIDIOC_REQBUFS,&buffers);
    buf_count = buffers.count;  //成功申请的buf数量
    if(buf_count<0)
    {
	log_exit("request buf");
    }
}

//初始化缓存映射保存区
void init_buf(struct BUFFER **buf)
{
    *buf = calloc(buf_count,sizeof(struct BUFFER));
    if(NULL ==  buf)
    {
	log_exit("calloc buf");
    }
    bzero(*buf,buf_count*sizeof(struct BUFFER));
}

//缓存映射
void init_mmap(void)
{
    struct v4l2_buffer getbuf;
    int i;
    for( i=0;i<buf_count;i++)
    {
	bzero(&getbuf,sizeof(getbuf));
	getbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	getbuf.memory = V4L2_MEMORY_MMAP;
	getbuf.index = i;
	ckioctl(fd,VIDIOC_QUERYBUF,&getbuf);
	buf[i].length = getbuf.length;
	buf[i].start = mmap(NULL,getbuf.length,PROT_READ | PROT_WRITE,MAP_SHARED,fd,getbuf.m.offset);
	if(NULL == buf[i].start)
	{
	    log_exit("mmap");
	}

    }
    bufdata_length = 6 * buf[0].length/4;
    bufdata = calloc(1,bufdata_length);
    if(NULL==bufdata)
    {
	log_exit("calloc bufdata");
    }
}

//添加队列
void add_queue(void)
{
    struct v4l2_buffer addbuf;
    int i;
    for( i=0;i<buf_count;i++)
    {
	bzero(&addbuf,sizeof(addbuf));
	addbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	addbuf.memory = V4L2_MEMORY_MMAP;
	addbuf.index = i;
	ckioctl(fd,VIDIOC_QBUF,&addbuf);
    }
}

//开始采集视频
void start_capture(void)
{
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ckioctl(fd,VIDIOC_STREAMON,&type);
}

//保存视频采集数据
void collect_data(void)
{
    struct v4l2_buffer getdata;
    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd,&set);
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    int ret = select(fd+1,&set,NULL,NULL,&tv);
    if(ret <= 0)
    {
	fprintf(camera_log_error,"select ret =%d,errno:%d\n",ret,errno);
	start_capture();
	stop_capture();
	return ;
    }

    //获取采集满的缓冲区
    bzero(&getdata,sizeof(getdata));
    getdata.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    getdata.memory = V4L2_MEMORY_MMAP;
    ret = ioctl(fd,VIDIOC_DQBUF,&getdata);
    if(ret <0)
    {
	fprintf(camera_log_error,"DQBUF:ret =%d,%s\n",ret,strerror(errno));
	start_capture();
	stop_capture();
	return ;
    }
    //保存文件名设置
    char filepath[256]="";
    sprintf(filepath,"%s%d.bmp",filename,picture_count%1);
    picture_count++;
    //保存数据

    int fs = open(filepath,O_RDWR | O_CREAT,0666);
    if(fs< 0)
    {
	log_exit("open Storage file");
    }
    bzero(bufdata,bufdata_length);
    gbpos =0;
    add_bmphead(fs);
    //申请访问bufdata
    sem_wait(&sem_camera);
    yuyv2rgb(getdata.index);
    ret = write(fs,bufdata,bufdata_length);
    //释放lcd访问信号量
    sem_post(&sem_lcd);
    close(fs);
    //将缓冲区才添加回等待队列
    struct 	v4l2_buffer addbuf;
    bzero(&addbuf,sizeof(addbuf));
    addbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    addbuf.memory = V4L2_MEMORY_MMAP;
    addbuf.index = getdata.index;
    ckioctl(fd,VIDIOC_QBUF,&addbuf);
}

//停止视频数据采集
void stop_capture(void)
{
    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ckioctl(fd,VIDIOC_STREAMOFF,&type);
}

//关闭视频设备
void close_device(void)
{
    int i;
    for(i= 0;i<buf_count;i++)
    {
	//		munmap(buf[i].start,buf[i].length);
    }
    close(fd);
}

void loop_handler(int signum)
{
    if(condition)
    {
	//获得图片
	collect_data();
    }	
    else
    {
	ualarm(1,0);
	stop_capture();
	close_device();
	pthread_exit(NULL);
    }
}

//停止时信号处理函数
void stop_handler(int signum)
{
    condition = 0;
}

//写入bmp文件头
void add_bmphead(int fs)
{
    //位图第一部分 文件信息
    BMPFILEHEAD filehead;
    bzero(&filehead,sizeof(filehead));
    filehead.bfType = (unsigned short)0x4d42;//bm
    filehead.bfSize = (unsigned long)(IMAGE_WIDTH * IMAGE_HEIGHT* 3 + 14 + 40); //文件字节数
    filehead.bfoffbits = 14+40;//bmp文件头的偏移量
    //位图第二部分 数据属性
    BMPINFOHEAD fileinfo;
    bzero(&fileinfo,sizeof(fileinfo));
    fileinfo.biSize = 40;
    fileinfo.biWidth = IMAGE_WIDTH;
    fileinfo.biHeight = IMAGE_HEIGHT;
    fileinfo.biPlanes = 1;//为1，不用改
    fileinfo.biBitCount = 24;//每个像素24bit
    fileinfo.biCompression = 0;//不压缩
    fileinfo.biSizeImage = IMAGE_WIDTH * IMAGE_HEIGHT *3;//像素字节数
    fileinfo.biXPelsPerMeter = 0;//2835;//像素每米
    //	fileinfo.biXPelsPerMeter = 2835;//2835;//像素每米
    //	fileinfo.biYPelsPerMeter = 2835;//2835;
    fileinfo.biYPelsPerMeter = 0;//2835;
    fileinfo.biClrUsed = 0;//已用过的颜色，24的为0；
    fileinfo.biClrImportant = 0;//每个像素都重要
    //文件第三部分 色彩表 24bit不需要
    //bmp头写入文件

    int ret =write(fs,&filehead,2);
    if(ret <= 0)
    {
	log_exit("write file head 0");
    }
    ret =write(fs,&filehead+2,12);
    if(ret <= 0 )
    {
	log_exit("write file head 1");
    }
    ret = write(fs,&fileinfo,sizeof(fileinfo));
    if(ret <= 0)
    {
	log_exit("write file head 2");
    }

}

//YUYV 2 BRG 写入文件
void yuyv2rgb(int index)
{
    unsigned char  y0,u,y1,v;
    int i;
    for(i= 0;i<buf[index].length;i=i+4)
    {
	y0 =*((char *)buf[index].start+i+0);
	u  =*((char *)buf[index].start+i+1);
	y1 =*((char *)buf[index].start+i+2);
	v  =*((char *)buf[index].start+i+3);
	input_rgb(y0,u,v);
	input_rgb(y1,u,v);
    }

}

//YUYV的y，u，v转rgb写入文件;
void input_rgb(unsigned char y,unsigned char u,unsigned char v)
{
    int r,b,g;
    char outbuf[3]="";
    b = y + (1.772 * (u-128));
    g = y - (0.71414 * (v-128)) - (0.34413 * (u-128));
    r = y + (1.402 * (v-128));
    if(r > 255) 
    {
	r = 255;
    }
    if(g > 255)
    {
	g = 255;
    }
    if(b > 255)
    {
	b = 255;
    }
    if(r < 0)
    {
	r = 0;
    }
    if(g < 0)
    {
	g =0;
    }
    if(b < 0)
    {
	b = 0;
    }
    outbuf[0] = b;
    outbuf[1] = g;
    outbuf[2] = r;
    unsigned int position =0;
    position = (IMAGE_HEIGHT -1 - gbpos/(IMAGE_WIDTH*3))*IMAGE_WIDTH*3 + gbpos%(IMAGE_WIDTH*3);
    bcopy(outbuf,bufdata+position,3);
    gbpos +=3;
}

//初始化信号量
int init_sem(void)
{
    if(sem_init(&sem_camera,0,1))
    {
	fprintf(camera_log_error,"init sem_camera\n");
	log_exit("init sem_camera\n");
    }
    if(sem_init(&sem_lcd,0,0))
    {
	fprintf(camera_log_error,"init sem_lcd\n");
	log_exit("init sem_lcd\n");
    }
    return 0;
}
