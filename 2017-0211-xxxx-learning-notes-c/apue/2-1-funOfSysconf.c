/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:2-1-funOfSysconf.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-04-20 23:18
 *   Describe:linux系统调用sysconf
 ********************************************************/
#include <stdio.h>
#include <unistd.h>

#define ONE_MB (1024 * 1024)

void main(int argc, char *argv[])
{
    /*
     *sysconf返回值为long型
     */
    printf("the number of processors configured is: %ld\n", sysconf(_SC_NPROCESSORS_CONF));
    printf("the number of processors currently online(available) is: %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
    printf("the pagesize: %ld\n", sysconf(_SC_PAGESIZE));
    printf ("The number of available pages: %ld\n", sysconf(_SC_AVPHYS_PAGES)); 
    printf ("The memory size: %lld MB\n", 
	    (long long)sysconf(_SC_PAGESIZE) * (long long)sysconf(_SC_PHYS_PAGES) / ONE_MB );  
    printf ("The number of files max opened:: %ld\n", sysconf(_SC_OPEN_MAX));  
    printf("The number of ticks per second: %ld\n", sysconf(_SC_CLK_TCK));  
    printf ("The max length of host name: %ld\n", sysconf(_SC_HOST_NAME_MAX));  
    printf ("The max length of login name: %ld\n", sysconf(_SC_LOGIN_NAME_MAX)); 

}
