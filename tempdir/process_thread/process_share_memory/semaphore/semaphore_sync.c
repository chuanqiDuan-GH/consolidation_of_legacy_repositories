#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "../common/include.h"

//创建信号量
int creat_sem(void)
{
    int semid = 0;
    key_t key;

    key = ftok(FTOK_FILE, IPCKEY);
    if(key == -1)
    {
	printf("%s : key = -1!\n",__func__);
	return -1;
    }

    semid = semget(key, 1, IPC_CREAT|OPEN_MODE);
    if(semid == -1)
    {
	printf("%s : semid = -1!\n",__func__);
	return -1;
    }

    return semid;

}

//初始化信号量。在使用之前必须先初始化
int set_semvalue(int semid)
{
    union semun sem_arg;
    sem_arg.val = 0;

    if(semctl(semid, 0, SETVAL, sem_arg) == -1)
    {
	printf("%s : can't set value for sem!\n",__func__);
	return -1;
    }
    return 0;
}

//占用资源，p操作
int sem_p(int semid)
{
    struct sembuf sem_arg;
    sem_arg.sem_num = 0;
    sem_arg.sem_op = -1;
    sem_arg.sem_flg = SEM_UNDO;

    if(semop(semid, & sem_arg, 1) == -1)
    {
	printf("%s : can't do the sem_p!\n",__func__);
	return -1;
    }
    return 0;
}

//释放资源，v操作
int sem_v(int semid)
{
    struct sembuf sem_arg;
    sem_arg.sem_num = 0;
    sem_arg.sem_op = 1;
    sem_arg.sem_flg = SEM_UNDO;

    if(semop(semid, & sem_arg, 1) == -1)
    {
	printf("%s : can't do the sem_v!\n",__func__);
	return -1;
    }
    return 0;
}

//删除信号量。
int del_sem(int semid)
{
    if(semctl(semid, 0, IPC_RMID) == -1)
    {
	printf("%s : can't rm the sem!\n",__func__);
	return -1;
    }
    return 0;
}
