#include "command.h"
#include "common.h"
#include "menu.h"

int do_connect(int *s_fd)
{ 
    struct sockaddr_in sd_addr; 
    int sd_len = sizeof(struct sockaddr_in);
    bzero(&sd_addr, sd_len);

    sd_addr.sin_family = AF_INET;
    sd_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &sd_addr.sin_addr);

    *s_fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = connect(*s_fd, (struct sockaddr *)&sd_addr, sd_len); 
    printf("connect ret:%d\n", ret);
    return ret;
}

int do_signup(int s_fd)
{
    int ret;
    char account[SID_LEN] = "";
    char passwd[SID_LEN] = "";
    char vrf_buf[VRF_LEN] = "";
    UD ud;

    bzero(vrf_buf, VRF_LEN);
    bzero(&ud, sizeof(UD));

    //recv ok/no
    ret = recv(s_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv signup verify message err\n"); 
	return -1;
    }

    //if ok, input account and passwd
    //if no, return to start menu
    if(!strcasecmp(vrf_buf, "no"))
    {
	printf("signup not ready\n");
	start_menu();
	return -1;
    }
    else if(!strcasecmp(vrf_buf, "ok"))
    {
	printf("please input your account:\n");		 
	gets(account);
	strcpy(ud.account, account);

	printf("please input your passwd:\n");
	gets(passwd);
	strcpy(ud.passwd, passwd);

	printf("being registered......\n");
    }

    printf("user data:%s %s\n ", ud.account, ud.passwd);
    ret = send(s_fd, &ud, sizeof(UD), 0);
    if(-1 == ret)
    {
	printf("send regist data err\n"); 
	start_menu();
	return -1;
    }

    bzero(vrf_buf, VRF_LEN);
    ret = recv(s_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv regist verify message err\n");
	return -1;
    }

    //regist succeed or failed
    if(!strcasecmp(vrf_buf, "ok"))
    {
	printf("regist succeed ^-^\n");
	void start_menu();
	return 1;
    }
    else if(!strcasecmp(vrf_buf, "no"))
    {
	printf("regist failed T.T\n");
	printf("\n");
	void start_menu();
	return -1;
    }
    return 1;
}

int do_signin(int s_fd)
{
    int ret;
    UD ud;
    char account[SID_LEN] = "";
    char passwd[SID_LEN] = "";
    char vrf_buf[VRF_LEN] = "";

    bzero(vrf_buf, VRF_LEN);
    bzero(&ud, sizeof(UD));

    //recv ok/no
    ret = recv(s_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv signin verify message err\n"); 
	return -1;
    }

    //if ok, input user data
    //if no, return to start menu
    if(!strcasecmp(vrf_buf, "no"))
    {
	printf("signin not ready\n");
	void start_menu();
	return -1;
    }
    else if(!strcasecmp(vrf_buf, "ok"))
    {
	printf("please input your account:\n");		 
	gets(account);
	strcpy(ud.account, account);

	printf("please input your passwd:\n");
	gets(passwd);
	strcpy(ud.passwd, passwd);

	printf("login......\n");
    }

    printf("user data:%s %s\n ", ud.account, ud.passwd);
    ret = send(s_fd, &ud, sizeof(UD), 0);
    if(-1 == ret)
    {
	printf("send login data err\n"); 
	void start_menu();
	return -1;
    }

    //if ok, go to opt menu
    //if sign ok, cmd_flag = 1
    //regist succeed or failed
    bzero(vrf_buf, VRF_LEN);

    ret = recv(s_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv regist verify message err\n"); 
	return -1;
    }

    if(!strcasecmp(vrf_buf, "ok"))
    {
	printf("login succeed ^-^\n");
	cmd_flag = 1;
	opt_menu();
	return 1;
    }
    else if(!strcasecmp(vrf_buf, "no"))
    {
	printf("login failed T.T\n");
	printf("\n");
	start_menu();
	return -1;
    }
    return 1;
}

int do_bye()
{
    printf("thanks for using! OTZ!\n");
}

int do_insert(int s_fd)
{
    int ret;
    char opt_buf[OPT_LEN] = "";
    char user_input[OPT_LEN] = "";
    char vrf_buf[VRF_LEN] = "";

    bzero(opt_buf, OPT_LEN); 
    bzero(user_input, OPT_LEN);

    gets(user_input);
    strcpy(opt_buf, user_input);

    ret = send(s_fd, opt_buf, OPT_LEN, 0);
    if(-1 == ret)
    {
	printf("opt insert send err\n"); 
	return -1;
    }

    //regist succeed or failed
    bzero(vrf_buf, VRF_LEN);

    ret = recv(s_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv insert verify message err\n"); 
	return -1;
    }

    if(!strcasecmp(vrf_buf, "ok"))
    {
	printf("insert succeed ^-^\n");
	return 1;
    }
    else if(!strcasecmp(vrf_buf, "no"))
    {
	printf("insert failed T.T\n");
	return -1;
    }
    return 1;
}

int do_delete(int s_fd)
{
    int ret;
    char opt_buf[OPT_LEN] = "";
    char user_input[OPT_LEN] = "";
    char vrf_buf[OPT_LEN] = "";

    bzero(opt_buf, OPT_LEN); 
    gets(user_input);
    strcpy(opt_buf, user_input);

    bzero(user_input, OPT_LEN);
    
    ret = send(s_fd, opt_buf, OPT_LEN, 0);
    printf("opt_buf:%s\n", opt_buf);

    if(-1 == ret)
    {
	printf("opt delete send err\n"); 
	return -1;
    }

    //regist succeed or failed
    bzero(vrf_buf, VRF_LEN);

    ret = recv(s_fd, vrf_buf, VRF_LEN, 0);
    if(-1 == ret)
    {
	printf("recv insert verify message err\n"); 
	return -1;
    }

    if(!strcasecmp(vrf_buf, "ok"))
    {
	printf("delete succeed ^-^\n");
	return 1;
    }
    else if(!strcasecmp(vrf_buf, "no"))
    {
	printf("delete failed T.T\n");
	return -1;
    }

    return 1;
}

int do_show(int s_fd)
{
   printf("ready to show\n");
   char data_buf[DT_LEN];
   int ret;
   int line_feed = 0; 

    bzero(data_buf, DT_LEN);

   while(1)
   {	ret = recv(s_fd, data_buf, DT_LEN, 0);
	if(-1 == ret)
	{
	    printf("recv err\n");	
	}
	if(!strncmp(data_buf, "fin", 3))
	{
	    printf("data recv finish\n");
	    break;	
	}
	printf("%s ", data_buf); 

	line_feed++;
	if(line_feed == 4)
	{
	    printf("\n");
	    line_feed = 0;
	}
	bzero(data_buf, DT_LEN);
   }
}

int do_signout()
{
    //to do
    //cmd_flag = 0
    cmd_flag = 0;
    //return to start menu
    start_menu(); 
}
