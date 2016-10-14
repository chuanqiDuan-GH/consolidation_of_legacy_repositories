#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include "include.h"
//#include <semaphore.h>

#define SM_SIZE 2048
#define OPEN_MODE 0777
#define IPCKEY 0x01


int main()
{
    //服务器端创建
    //创建共享内存
    //shmget
    int shmid;
    key_t key = ftok("./keyfile", IPCKEY);
    printf("%d\n", key);
    if(-1 == (shmid = shmget(key, SM_SIZE, OPEN_MODE|IPC_CREAT)))
    //if(-1 == (shmid = shmget(MYSHMKEY, SM_SIZE, 0777)))
    {
	printf("%s shmget failre!!!\n", __FILE__); 
	return -1;
    }

    //建立进程与共享内存的联系(映射)
    //shmat
    char *shmaddr = NULL;
    if((char *)-1 == (shmaddr = (char *)shmat(shmid, NULL, 0)))
    {
	printf("%s shmmat failure!!!\n", __FILE__); 
	return -1;
    }

    //控制共享内存进行所需操作
    //向共享内存写数据，对shaddr进行操作
    while(1)
    {
	//sem_wait(&sem1);
	gets(shmaddr); 
	//sem_post(&sem2);
    }


    //将共享内存从当前进程中分离
    //shmdt
    if(-1 == shmdt(shmaddr))
    {
	printf("%s shmdt failure!!!\n", __FILE__); 
	return -1;
    }
    
    //将共享内存和进程分离后，就可以操作删除
    //shmctl
    if(-1 == shmctl(shmid, IPC_RMID, NULL))
    {
	printf("%s shmctl failure!!!\n", __FILE__); 
	return -1;
    }

    return 0;
}
