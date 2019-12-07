#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "common.h"

/*测试消息队列send不同type参数，recv的第四个参数三种情况*/

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


    Mymsg msg1;
    msg1.m_type = 1;
    strcpy(msg1.m_text, "type=1");

    Mymsg msg2;
    msg2.m_type = 2;
    strcpy(msg2.m_text, "type=2");

    Mymsg msg3;
    msg3.m_type = 3;
    strcpy(msg3.m_text, "type=3");

    //发送消息
    msgsnd(msgid, (void *)&msg1, BUF_SIZE, 0);
    msgsnd(msgid, (void *)&msg2, BUF_SIZE, 0);
    msgsnd(msgid, (void *)&msg3, BUF_SIZE, 0);

    return 0;
}
