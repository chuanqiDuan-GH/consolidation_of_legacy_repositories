#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "common.h"

int main()
{
    //ftok获取key 	
    int msgid;
    key_t key = ftok(FTOK_PATH, IPCKEY);
    if(-1 == key)
    {
	printf("%s ftok failed\n", __func__); 
	return -1;
    }

    //创建msg
    msgid = msgget(key, IPC_CREAT | MSG_MODE);    
    if(-1 == msgid)
    {
	printf("%s msgget failed\n", __func__); 
	return -1;
		
    }

    Mymsg msg_rcv;
    memset(&msg_rcv, 0, sizeof(Mymsg));

    if(-1 == (msgrcv(msgid, (void *)&msg_rcv, BUF_SIZE, -2, 0)))
    {
	printf("%s msgrcv failed\n", __func__); 
	return -1;
    }
    printf("%s\n", msg_rcv.m_text);
    return 0;
}
