#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include "../common/include.h"

int main()
{
    //创建信号量
    int semid = creat_sem();
    if(semid == -1)
    {    printf("%s : semid = %d!\n", __func__, semid);
	return -1;
    }

    //创建信号量之后的，初始化操作
    if(set_semvalue(semid))
    {
	printf("%s : set_semvalue failed!\n",__func__);
	return -1;
    }

    //服务器端创建
    //创建共享内存
    //shmget
    int shmid;
    key_t key = ftok(FTOK_FILE, IPCKEY);
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
	sem_v(semid);
	gets(shmaddr); 
	//sem_v(semid);
	//sem_post(&sem2);
    }

    //删除信号量键值
    if(del_sem(semid))
    {
	printf("%s : del_sem failed!\n", __func__);
	return -1;
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
