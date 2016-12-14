#include "M0.h"

extern Display display;

int M0_init()
{
    int M0_fd;
    //开设备
    M0_fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY | O_NONBLOCK);
    //O_NONBLOCK设置为非阻塞模式，在read时不会阻塞住，在读的时候将read放在while循环中，下一节篇文档将详细讲解阻塞和非阻塞
    if(M0_fd == -1)
    {
	//printf("M0 open error!\r\n");
	return -1;
    }
    printf("open /dev/ttyUSB0 success!\r\n");
    //设置串口
    struct termios ser;
    if( tcgetattr( M0_fd,&ser) != 0)
    {    
	perror("SetupSerial 1");  
	printf("tcgetattr( M0_fd,&ser) -> %d\r\n",tcgetattr( M0_fd,&ser));   
	return -1;   
    }
    tcflush(M0_fd, TCIOFLUSH);
    //设置字符大小
    ser.c_cflag |= (CLOCAL | CREAD);    
    ser.c_cflag &= ~CSIZE;
    //设置停止位
    ser.c_cflag |= CS8;
    //无奇偶校验位
    ser.c_cflag &= ~PARENB; 
    ser.c_iflag &= ~INPCK;
    //设置波特率
    cfsetispeed(&ser, B115200);   
    cfsetospeed(&ser, B115200);
    //设置停止位
    ser.c_cflag &= ~CSTOPB;
    //设置等待时间和最小接收字符
    ser.c_cc[VTIME]  = 0; 
    ser.c_cc[VMIN] = 0;

    ser.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); 
    ser.c_oflag &= ~OPOST;     
    ser.c_oflag &= ~(ONLCR | OCRNL);           
    ser.c_iflag &= ~(ICRNL | INLCR);     
    ser.c_iflag &= ~(IXON | IXOFF | IXANY);   

    //处理未接收字符
    tcflush(M0_fd,TCIFLUSH);
    if((tcsetattr(M0_fd,TCSANOW,&ser))!=0)
    {   
	perror("com set error\r\n");   
	return -1;   
    } 

    printf("init success!\r\n");
    return M0_fd;
}

void M0_read(int M0_fd)
{
    unsigned char read_buf[BUF_SIZE] = {1};
    fLags flags;
    int readsize;
    int res;
    int count = 0, i;	
    while (1)
    {
	sleep(1);
	readsize = read(M0_fd, read_buf, 2);
	//printf("readsize = %d\r\n",readsize);
	if(readsize < 0)
	{
	    //printf("readsize err\n");
	    continue;
	}
	//printf("%d,%d",read_buf[0],read_buf[1]);
	if(0xbb == read_buf[0] && 0x05 == read_buf[1])
	{
	    count = BUF_SIZE - 2;
	    i = 2;
	    while(count > 0)
	    {
		readsize = read(M0_fd, read_buf + i, count);
		count -= readsize;
		i += readsize;
	    }
	    /*printf("readsize = %d\n\r",readsize);
	      int i = 0;
	      for(;i < readsize;i++)
	      {			
	      printf("%5d",read_buf[i]);
	      }
	     */

	    display.tmp = read_buf[5];
	    res = M0_flags(display.tmp, 18, 26, flags.f1);
	    //	printf("tmp = %d\n\r", display.tmp);
#if 0			
	    if(res == 0)
	    {
		M0_ctrl(M0_fd, 1);
		printf("tmp too low\r\n");						
	    }
	    if(res == 1)
	    {
		M0_ctrl(M0_fd, 2);
		printf("led closed\r\n");								
		M0_ctrl(M0_fd, 4);
		printf("fan closed\r\n");
	    }
	    if(res == 2)
	    {
		M0_ctrl(M0_fd, 3);
		printf("tmp too high\r\n");
	    }
#endif			
	    display.hum = read_buf[7];
	    M0_flags(display.hum, 13, 18, flags.f2);
	    //	printf("hmp = %d\n\r", display.hum);


	    display.lig = read_buf[20];
	    M0_flags(display.lig, 0, 0, flags.f3);
	    //	printf("lig = %d\n\r", display.lig);

	    display.led = read_buf[8];
	    M0_flags(display.led, 0, 0, flags.f4);
	    //	printf("led = %d\n\r", display.led);

	    display.fan = read_buf[9];
	    M0_flags(display.fan, 0, 0, flags.f5);
	    //	printf("fan = %d\n\r", display.fan);

	    display.buzz = read_buf[10];
	    M0_flags(display.buzz, 0, 0, flags.f6);
	    //	printf("buzz = %d\n\r", display.buzz);

	    printf("%d %d %d\n",display.tmp, display.hum, display.lig);
	    memset(read_buf, 0, sizeof(read_buf));
	}
	else
	{
	    memset(read_buf, 0, sizeof(read_buf));
	    continue;
	}
    }
}

int M0_flags(int data, int datalow, int datahig, int flags)
{	
    if(data < datahig && data >datalow )
    {
	flags = 1;
    }
    else
    {
	if( data > datahig)
	{
	    flags = 2;
	}
	else  
	{
	    flags = 0;
	}
    }
    return flags;
}

void M0_ctrl(int M0_fd, int ctrl)
{
    int res = 0;
    switch(ctrl)
    {
	case 1:	//开灯
	    //	printf("case 1\r\n");
	    write_buf[4] = 0x00;
	    res = write(M0_fd,write_buf,5);
	    break;
	case 2:	//关灯
	    //	printf("case 2\r\n");
	    write_buf[4] = 0x01;
	    res = write(M0_fd,write_buf,5);
	    break;
	case 3:	//开风扇
	    //	printf("case 3\r\n");
	    write_buf[4] = 0x04;
	    res = write(M0_fd,write_buf,5);
	    break;
	case 4:	//关风扇
	    //	printf("case 4\r\n");
	    write_buf[4] = 0x08;
	    res = write(M0_fd,write_buf,5);
	    break;
	case 5:	//开蜂鸣器
	    //	printf("case 5\r\n");
	    write_buf[4] = 0x02;
	    res = write(M0_fd,write_buf,5);
	    break;
	case 6:	//关蜂鸣器
	    //	printf("case 6\r\n");
	    write_buf[4] = 0x03;
	    res = write(M0_fd,write_buf,5);
	    break;
#if 0
	case 7: //关机
	    //	printf("case 7\r\n");
	    write_buf[4] = 0x11;
	    res = write(M0_fd,write_buf,5);
	    break;
#endif
    }
}

void M0_close(int M0_fd )
{
    close(M0_fd);
}
