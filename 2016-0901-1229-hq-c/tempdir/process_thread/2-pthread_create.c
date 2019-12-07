#include <stdio.h>
#include <pthread.h>

void *ThreadFunc(void *arg);

int main()
{
    pthread_t tID = 0;
#ifndef ARG
    //pthread_create的第四个参数可以用来给线程函数传参
    int a = 10;
    if(0 != pthread_create(&tID, NULL, ThreadFunc, (void *)&a))
    {
	return -1; 
    }
#else
    //当前代码段可通过gcc -D ARG选项编译
    if(0 != pthread_create(&tID, NULL, ThreadFunc, NULL))
    {
	return -1; 
    }
#endif
    //这里不加上1秒延时，线程还没调用，主进程就结束了
    //sleep(1);

    //pthread_join用来等待一个线程结束，pthread_exit用来强制退出一个线程
    pthread_join(tID,NULL);

    return 0;
}

void *ThreadFunc(void *arg)
{
#ifndef ARG
    int a = *(int *)arg;
    printf("%d %s\n", a,  __func__);
#else
    printf("%s\n", __func__);
#endif
}
