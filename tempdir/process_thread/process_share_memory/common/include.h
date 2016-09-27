#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#define SM_SIZE 2048
#define OPEN_MODE 0777
#define IPCKEY 0x01
#define SHM_SIZE 256
#define FTOK_FILE "../keyfile"

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

typedef struct _tag_shm
{
    char buf[SHM_SIZE];
    unsigned short num;
}shm_t;

int creat_sem(void);
int set_semvalue(int semid);
int sem_p(int semid);
int sem_v(int semid);
int del_sem(int semid);


#endif //_INCLUDE_H_
