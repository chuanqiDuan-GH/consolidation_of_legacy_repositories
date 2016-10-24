#ifndef _COMMAND_H_
#define _COMMAND_H_

#define VRF_LEN 16  //验证消息长度,ok,no等
#define OPT_LEN 16 //增加,删除操作所需命令长度(并非main函数中提及的操作命令)
#define DT_LEN 16   //用于存储show命令每次所需显示的数据长度

int cmd_flag;	//操作标识,用来分离两类表的操作过程

//登录注册表操作,对account和passwd的注册与验证操作
int do_connect(int *s_fd);  //连接
int do_signup(int s_fd);    //注册
int do_signin(int s_fd);    //登录
int do_bye();	//客户端断开连接

//用户数据表操作,对用户数据(每一条数据包含time,step,km,sleep信息)进行操作
int do_insert(int s_fd);    //插入数据
int do_delete(int s_fd);    //删除数据
int do_show(int s_fd);	//显示表中所有数据
void do_signout();  //注销登录

#endif	//_COMMAND_H_	
