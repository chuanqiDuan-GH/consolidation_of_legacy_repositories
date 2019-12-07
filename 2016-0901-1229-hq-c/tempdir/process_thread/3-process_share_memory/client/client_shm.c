#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include "../common/include.h"

int main()
{
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

    //客户端创建
    //创建共享内存
    //shmget
    int shmid;
    int key = ftok(FTOK_FILE, IPCKEY);
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

sleep(5);
    while(1)
    {
	//sem_wait(&sem2);
	sem_p(semid);
	sleep(2);
	printf("%s\n", shmaddr);
	//sem_p(semid);
	//sleep(2);
	//sem_post(&sem1);

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
