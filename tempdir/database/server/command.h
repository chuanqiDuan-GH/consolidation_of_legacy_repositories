#ifndef _command_h_
#define _command_h_

int fd;
#define BUF_SIZE 256
#define TEMP_SIZE 256
#define SIZE 12

MYSQL conn;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
MYSQL_FIELD *myfd;

int success=0;
char name[SIZE]="";
char buf[BUF_SIZE]="";

typedef struct ACCOUNT
{
	char name[SIZE];
	char passwd[SIZE];
}Account;
Account accbuf;

int signup();
int  signin();
int function();

#endif
