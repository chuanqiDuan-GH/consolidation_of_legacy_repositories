#ifndef _COMMAND_H_
#define _COMMAND_H_

#define VRF_LEN 32
#define OPT_LEN 256
#define DT_LEN 16

int cmd_flag;

//table 1 opt
int do_connect(int *s_fd);
int do_signup(int s_fd);
int do_signin(int s_fd);
int do_bye();

//table 2 opt
int do_insert(int s_fd);
int do_delete(int s_fd);
int do_show(int s_fd);
int do_signout();

#endif	//_COMMAND_H_	
