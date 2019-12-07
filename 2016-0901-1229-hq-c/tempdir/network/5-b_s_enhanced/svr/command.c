#include"common.h"
#include"command.h"
int do_put(const char *src, const char *dst, int sock_fd)
{
	struct stat file_info;
	int ret=-1;
	char buf[BUF_SIZE]="";
	int file;

	ret = stat(src,&file_info);//�ж��ļ��Ƿ����
	if(ret < 0)
	{	
		send(sock_fd, "no",2,0); // �ļ�������
		perror("stat");
		return -1;
	}
	else
	{
		file=open(src,O_RDONLY);
		if(file<0)
		{
			perror("open file");
			return -1;
		}
	}
	ret = send(sock_fd, "ok",2,0);//������ڷ���ok��Ϣȷ��
	if(ret<0)
	{
		perror("send file size");
		return -1;
	}
	bzero(buf,BUF_SIZE);
	ret=recv(sock_fd,buf,BUF_SIZE,0);//����client׼����״̬
	if(ret<0)
	{
		perror("recv file ready");
		return -1;
	}
	if(strcmp(buf,"red")==0)
	{	
		
		printf("%s\n",buf);
		
		while(1)    //�����ļ�
		{
			bzero(buf,BUF_SIZE);
			ret=read(file,buf,BUF_SIZE);
			if(ret == 0)
			{
				break;
			}
			send(sock_fd,buf,ret,0);
			printf("file=%s\n",buf);
		}
		send(sock_fd,"fin",6,0);// �ļ�����
		bzero(buf,BUF_SIZE);
		printf("finish\n");
	}
	
	
}

int do_get(const char *src, const char *dst, int sock_fd)
{
	
	int ret=-1;
	long  size=0;
	char buf[BUF_SIZE]="";
	int file;
//	ret=recv(sock_fd,&size,sizeof(size),0);//�����ļ���С
/*	if(size<=0)
	{
		return -1;
	}   */
	file = open(dst,O_CREAT| O_WRONLY, 0777);
	if(file<0)
	{
		perror("open dst file");
		send(sock_fd,"no",2,0);
		return -1;
	}
	strcpy(buf,"red");
	send(sock_fd,buf,BUF_SIZE,0);//׼���ý���
	printf("ready\n");

	while(1)
	{
		bzero(buf,BUF_SIZE);
		ret=recv(sock_fd,buf,BUF_SIZE,0);
		if(strcmp(buf,"fin")==0) // ���������ݱ��
		{
			printf("FINISH \n");
			break;
		}
		write(file,buf,ret);
	}
	
	close(file);	
	return 0;
}
/*
int do_ls(char *path)
{
	struct dirent *file_name;
	DIR *dir=opendir(path);
	char buf[BUF_SIZE]="";
	if(dir==NULL)
	{
		perror("opendir");
		return -1;
	}
	while(file_name=readdir(dir))
	{
		strcpy(buf,file_name->d_name);
		send(fd,buf,BUF_SIZE,0);
		bzero(buf,BUF_SIZE);
	}
	return 0;
}

*/

int do_cd(char *path)
{
	int ret = chdir(path);
	if(ret==0)
	{
	//	send(fd,"OK",2,0);
	printf("chdir ok \n");
	}
	else
	{
		send(fd,"no",2,0);
		printf("chdir no \n");
	}
	
	return 0;
}

int do_ls(char *path)
{
	char buf[BUF_SIZE]="";
	char command[MAX_LENGTH]="";
	int file=open("/home/farsight/tempfile",O_CREAT|O_RDWR|O_TRUNC,0777); //������ʱ�ļ�����ls������ʾ����
	if(file<0)
	{
		perror("open tempfile");
		return -1;
	}
	strcpy(command,"ls ");
	strcat(command,path);
	strcat(command," > /home/farsight/tempfile");
	system(command);
	int ret = read(file,buf,BUF_SIZE);
	if(ret==0)
	{
		send(fd,"ERROR",5,0);
	}
	else
	{	
		int i;
		for(i=0;i<BUF_SIZE;i++)
		{
			if(buf[i]=='\n')
			{
				buf[i]='\t';
			}
		}         //���ļ������\n ��Ϊ\t

		
		send(fd,buf,ret,0);
	}
	remove("/home/farsight/tempfile");//ɾ����ʱ�ļ�
	return 0;
}









void * select_option(void * c_fd)  //�����������ͬ�Ĺ���ȥ����
{
	printf("into select_option\n");



	
	fd=*(int *)c_fd;
	command_line data;
//	bzero(&data,sizeof(data));
	int ret=-1;

	while(1)
	{	
		bzero(&data,sizeof(data));
		ret=recv(fd,&data,sizeof(data),0);
		
		if(ret <= 0)
		{
			perror("recv ");
		
		}
	
	
	printf("name=%s\t,argv1=%s\t,argv2=%s\n",data.name,data.argv1,data.argv2);

		
		if(strcmp(data.name,"get") == 0 )
		{
			do_put(data.argv1, data.argv2, fd);
		}
		else if(strcmp(data.name,"put") == 0 )
		{
			do_get(data.argv1, data.argv2, fd);
		}

		else if(strcmp(data.name,"!cd") == 0 )
		{
			do_cd(data.argv1);
		}
		else if(strcmp(data.name,"!ls") == 0 )
		{
			do_ls(data.argv1);
		}
		else if(strcmp(data.name,"bye") == 0 )
		{
				close(fd);
				printf("over pthread\n");
				
			pthread_exit(0);

		}
		
	}
}

