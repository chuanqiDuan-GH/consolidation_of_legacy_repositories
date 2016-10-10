#include"common.h"
#include"command.h"


int main()
{	
	
	struct sockaddr_in src,dest;
	bzero(&src,sizeof(src));
	int len_dest=sizeof(dest);
	src.sin_family=AF_INET;
	src.sin_port=htons(8000);
	inet_pton(AF_INET,"127.0.0.1",&src.sin_addr);
	int s_fd,c_fd,ret;
	pthread_t pthread = -1;

	s_fd=socket(AF_INET,SOCK_STREAM,0);
	if(s_fd<0)
	{
		perror("socket");
		return -1;
	}

	ret = bind(s_fd,(struct sockaddr *)&src,sizeof(src));
	if(ret<0)
	{
		perror("socket");
		return -1;
	}

	ret = listen(s_fd,10);
	if(ret<0)
	{
		perror("socket");
		return -1;
	}
	
	while(1)
	{
		c_fd = accept(s_fd,(struct sockaddr *)&dest,&len_dest);
		if(c_fd<0)
		{
			perror("accept");
			return -1;
		}
		pthread_create(&pthread,NULL,select_option,(void *)&c_fd);
		pthread_detach(pthread);
	}
	
	
	
}
