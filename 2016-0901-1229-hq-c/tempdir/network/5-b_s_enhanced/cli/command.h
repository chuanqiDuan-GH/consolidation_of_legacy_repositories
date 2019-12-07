#ifndef _COMMAND_H_
#define _COMMAND_H_

int do_connect(char *ip, int *sock_fd);    //与服务器进行连接
int do_get(const char *src, const char *dst, int sock_fd);  //下载
int do_put(const char *src, const char *dst, int sock_fd);  //上传
int do_cd(char *path);	//进入当前主机指定目录
int do_ls(char *path);	//列出当前主机指定目录下的内容
int do_serv_cd(char *path, int sock_fd);    //进入服务器指定目录
int do_serv_ls(char *path, int sock_fd);    //列出服务器指定目录
int do_bye(int sock_fd);	//say goodbye

#endif	//_COMMAND_H_ 
