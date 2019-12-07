#ifndef _COMMAND_H_
#define _COMMAND_H_

int fd;
#define BUF_SIZE 256
#define TEMP_SIZE 256
#define SIZE 12

//数据库相关声明
MYSQL conn;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
//MYSQL_FIELD *myfd;	//储存列信息? 没用到?

int success=0;	//用户数据表操作标识符
char name[SIZE]="";
char buf[BUF_SIZE]="";

typedef struct ACCOUNT	//注册表数据结构体
{
	char name[SIZE];    //用户名
	char passwd[SIZE];  //密码
}Account;
Account accbuf;

int signup();	//注册
int  signin();	//登录
int function();	//用户数据表操作函数

#endif	//_COMMAND_H_
