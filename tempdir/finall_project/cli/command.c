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
    //这里的ip是本地回环测试地址,在实际测试中需要明确服务器地址
    inet_pton(AF_INET, "127.0.0.1", &sd_addr.sin_addr);

    *s_fd = socket(AF_INET, SOCK_STREAM, 0);
    int ret = connect(*s_fd, (struct sockaddr *)&sd_addr, sd_len); 
    printf("connect ret:%d\n", ret);
    return ret;
}

/*
   在注册和登录的过程中都采用了协定的四次交互原则,
   1->
   发送操作命令,这里是signup
   2->
   接收服务器是否接受命令的确认消息并作对应处理,成功ok,失败no
   3->
   发送账户(account)密码(passwd)
   4->
   接收服务器注册操作的确认信息,成功ok,失败no
 */
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

	printf("being regist......\n");
    }

    //printf("user data:%s %s\n ", ud.account, ud.passwd);
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

//处理过程同signup
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

/*
   增加,删除处理逻辑类似,过程分三步如下
   1->
   发送操作命令之后,以服务区所需数据格式发送要插入的数据,四个数据分别以逗号隔开
   发送time为1,step为2,km为3,sleep为4的数据
   数据格式:1,2,3,4
   2->
   接收确认消息
   3->
   打印提示信息,成功提示success,失败提示failue
 */
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

//删除数据时以time作为区分,所以用表中time做为对比项,也就是说time数据无重复
/*
   删除时秩序发送time值,根据time值删除对应整条数据
   删除time为1的整条数据
   数据格式:1
 */
//处理过程同增加
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

/*
   接收服务端发送过来的数据进行显示时,
   由于服务端的数据是循环一个一个的发过来的,
   所以客户端相应的也会循环去接,以服务端发送fin标识作为发送结束标志

   一条信息对应登陆用户的time,step,km,sleep四个数据,
   所以每打印完四个数据说明已经接受一条完整数据,需要做换行处理
 */
int do_show(int s_fd)
{
    printf("ready to show\n");
    char data_buf[DT_LEN];
    int ret;
    int line_feed = 0; 

    bzero(data_buf, DT_LEN);

    while(1)
    {	
	ret = recv(s_fd, data_buf, DT_LEN, 0);
	if(-1 == ret)
	{
	    printf("recv err\n");	
	}
	//结束标识判断
	if(!strncmp(data_buf, "fin", 3))
	{
	    printf("data recv finish\n");
	    break;	
	}
	//打印数据
	printf("%s ", data_buf); 

	//换行处理
	line_feed++;
	if(line_feed == 4)
	{
	    printf("\n");
	    line_feed = 0;
	}
	bzero(data_buf, DT_LEN);
    }
    return 1;
}

void do_signout()
{
    //注销登陆后,需要将cmd_flag置0,禁止用户的数据表操作(增,删,显示) 
    cmd_flag = 0;
    start_menu(); 
}
