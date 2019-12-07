#include "include.h"

int main(int argc, char *argv[])
{
    showInfo(); 
    return 0;
}

void showInfo()
{
    DIR *dir = opendir(".");
    if(!dir)
    {
	printf("open failure\n"); 
	return; 
    }

    Stat *file_info = (Stat*)malloc(sizeof(Stat));
    struct dirent *rf = NULL;

    memset(file_info, 0, sizeof(stat));
    while(rf = readdir(dir))
    {

	stat(rf->d_name, file_info);
	//文件类型(七种)
#if 1
	if(S_ISDIR(file_info->st_mode))
	    printf("d");	
	else if(S_ISREG(file_info->st_mode))
	    printf("-");
	else if(S_ISLNK(file_info->st_mode))
	    printf("l");
	else if(S_ISCHR(file_info->st_mode))
	    printf("c"); 
	else if(S_ISBLK(file_info->st_mode))
	    printf("b");
	else if(S_ISFIFO(file_info->st_mode))
	    printf("p");
	else if(S_ISSOCK(file_info->st_mode))
	    printf("s");
#endif
	//查看链接文件与二进制文件问题
	//printf("%o\t",file_info->st_mode & S_IFMT); 

	//文件读写执行权限
	if(S_IRUSR == (file_info->st_mode & S_IRUSR))
	    printf("r"); 
	else
	    printf("-"); 
	if(S_IWUSR == (file_info->st_mode & S_IWUSR))
	    printf("w"); 
	else
	    printf("-"); 
	if(S_IXUSR == (file_info->st_mode & S_IXUSR))
	    printf("x"); 
	else
	    printf("-"); 

	if(S_IRGRP == (file_info->st_mode & S_IRGRP))
	    printf("r"); 
	else
	    printf("-"); 
	if(S_IWGRP == (file_info->st_mode & S_IWGRP))
	    printf("w"); 
	else
	    printf("-"); 
	if(S_IXGRP == (file_info->st_mode & S_IXGRP))
	    printf("x"); 
	else
	    printf("-"); 

	if(S_IROTH == (file_info->st_mode & S_IROTH))
	    printf("r"); 
	else
	    printf("-"); 
	if(S_IWOTH == (file_info->st_mode & S_IWOTH))
	    printf("w"); 
	else
	    printf("-"); 
	if(S_IXOTH == (file_info->st_mode & S_IXOTH))
	    printf("x"); 
	else
	    printf("-"); 
	printf("\t");
	
	//文件链接数目
	printf("%d\t", file_info->st_nlink); 

	//文件所属用户
	if(0 == file_info->st_uid)
	    printf("root\t");	
	else if(1000 == file_info->st_uid)
	    printf("farsight\t");

	//文件所属用户组
	if(0 == file_info->st_gid)
	    printf("root\t");	
	else if(1000 == file_info->st_gid)
	    printf("farsight\t");
	
	//文件大小
	printf("%d\t", (int)file_info->st_size);	
	
	//文件最后修改时间
	time_t t = (time_t)file_info->st_mtime;
	struct tm *p = localtime(&t);
	char s[50];
	strftime(s,sizeof(s),"%Y-%m-%d %H:%M:%S",p);
	printf("%s\t",s);
	
	//文件名
	printf("%s\n", rf->d_name);
    }

}

