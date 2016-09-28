#ifndef _COMMON_H_
#define _COMMON_H_

#define MSG_MODE 0777
#define FTOK_PATH "."
#define IPCKEY 0x01
#define BUF_SIZE 20

typedef struct _Mymsg
{
   long m_type;
   char m_text[BUF_SIZE];
}Mymsg;

#endif //_COMMON_H_
