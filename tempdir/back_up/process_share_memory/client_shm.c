#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
//#include <semaphore.h>
#include "include.h"

#define SM_SIZE 2048
#define OPEN_MODE 0777
#define IPCKEY 0x01


int main()
{
    
    //客户端创建
    //创建共享内存
    //shmget
    int shmid;
    int key = ftok("./keyfile", IPCKEY);
    if(-1 == (shmid = shmget(key, SM_SIZE, OPEN_MODE|IPC_EXCL)))
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

    while(1)
    {
	//sem_wait(&sem2);
	printf("%s\n", shmaddr);
	//sleep(2);
	//sem_post(&sem1);
	
    }
#if 0
    //客户端与服务器端建立的共享内存建立联系  
    //建立进程与共享内存的联系

    //控制共享内存进行所需操作
    //读取共享内存中的数据
    //shmctl
    if(-1 == shmctl(shmid))
    {
    
    }
#endif

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
