#ifndef __COMMAND_H__
#define __COMMAND_H__

int fd;
#define BUF_SIZE 256
#define TEMP_SIZE 256
#define SIZE 12

//sql数据库
static sqlite3 *account;
static char *errmsg;
static char **resultp;
static int nrow, ncolumn;

#if MYSQL
//mysql数据库相关声明
MYSQL conn;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;
//MYSQL_FIELD *myfd;	//储存列信息? 没用到?
#endif

int success=0;	//用户数据表操作标识符
char name[SIZE]="";
char buf[BUF_SIZE]="";

typedef struct ACCOUNT	//注册表数据结构体
{
    char name[SIZE];    //用户名
    char passwd[SIZE];  //密码
}Account;
Account accbuf;


/*可交互接口*/
//客户端
void open_cam();    //打开摄像头
void close_cam();   //关闭摄像头
void get_env_data();	//获取环境数
void get_run_time(); //获取运行时间
void get_cam_data();	//获取视频信息
//数据库
int signup();	//帐号注册
int signin();	//帐号登录
int function();

/*无交互接口*/
//LCD
void init_lcd();    //初始化lcd
void send_pic_lcd();    //发送数据到显示屏
//m0
void recv_env_m0();   //接收m0的环境数据
//摄像头
void init_cam();    //初始化摄像头(默认打开)
void recv_pic_cam();	//获取摄像头图片

#endif	//__COMMAND_H__
