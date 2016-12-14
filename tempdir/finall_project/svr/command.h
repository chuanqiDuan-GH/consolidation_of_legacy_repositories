#ifndef __COMMAND_H__
#define __COMMAND_H__

#define CLICMD_BUF 256
#define TEMP_SIZE 256
#define SIZE 12

//sql数据库
static sqlite3 *account;    //数据库
static char *errmsg;	//sql错误信息
static char **resultp;
static int nrow, ncolumn;

int fd;
int success=0;	//操作标识符
char cli_buf[CLICMD_BUF]="";

typedef struct ACCOUNT	//注册表数据结构体
{
    char name[SIZE];    //用户名
    char passwd[SIZE];  //密码
}Account;
Account accbuf;

/*可交互接口*/
//注册登录
int signup();	//帐号注册
int signin();	//帐号登录

int fun_command();	//功能控制命令

//客户端操作
//void open_cam();    //打开摄像头
//void close_cam();   //关闭摄像头
void get_env_m0();	//获取m0环境参数
void get_vdo_cam();	//获取cam视频

/*无交互接口*/

#endif	//__COMMAND_H__
