#include<stdio.h>



char *deleteBlank(char *str)
{
    char *s = str;
    //把一个字符串常量赋值给一个数据存储类型为char的数组是不对的
    //main函数中有接收值，是否可以去掉static的修饰?
    static char ss[20] = "0"; 
    //static char ss[20] = {'\0'};
    int i = 0;

    while(*s != '\0')
    {
	if(*s != ' ')
	{
	    //ss是用下标进行元素的调用，并没有移动指针的位置
	    ss[i++] = *s;	
	}
	s++;
    }

    ss[i] = '\0';
    //printf("%s\n", ss);

    return ss;
}

void main()
{
#if 1
    char *str = "asd af aa z67";
    char *temp = deleteBlank(str);

    printf("%s\n", temp);
#endif

#if 0	
    char *str = "asd af aa z67";
    char temp[20] = "";
    int i = 0;
    char ch = ' ';

    while(*str != '\0')
    {
	if(*str != ' ')
	{
	    ch = *str;
	    temp[i++] = ch;	
	    //	printf("%c\n", temp[i]);
	}
	str++;
    }
    //temp[i] = '\0';
    //	nothing display when output
    //	printf("%s\n", str); 
    printf("%s\n", temp);
#endif

#if 0 
    char str[20] = "asd af aa z67 ";
    char finall[] = "";
    int i = 0;
    int j = 0;

    while(str[j] != '\0')
    {
	printf("%c\n", str[j]);	
	if(str[j] != ' ')
	{

	    finall[i] = str[j];
	    i++;
	    j++;	
	}
	else
	    j++;	
    }
    finall[i] = '\0';

    printf("%s\n", finall);
#endif 
}
