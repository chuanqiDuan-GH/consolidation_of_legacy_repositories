#include<stdio.h>
#include<string.h>

char *myStrcpy(char *str1, char *str2);
char *myStrcat(char *str1, const char *str2);
int myStrcmp(char *str1, char *str2);

int main()
{

    char str1[] = "0"; 
    char str2[] = "0";

    gets(str1);
    gets(str2);

    //str1只有8个字符的大小，输出都会出问题
    //char *str = myStrcat(str1, str2);
    //char *str = myStrcpy(str1, str2);
    int result = myStrcmp(str1, str2);

#if 0
    printf("%d\n", sizeof(str1));
    printf("%d\n", strlen(str1));
    printf("%d\n", sizeof(str2));
    printf("%d\n", strlen(str2));
    #endif
    //printf("%s\n", str);
    printf("%d\n", result);

    return 0;
}

char *myStrcat(char *str1, const char *str2)
{

    //不要再犯这种低级错误，要记住str1的首地址，如果直接返回str1，那么经过下面的操作
    //str1已经指向了字符串的末尾。
    char *str = str1;
    if(str1 == NULL && str2 == NULL)
    {
	return NULL; 
    }

    while(*str1 != '\0')
    {
	str1++; 
    }

    while(*str2 != '\0')
    {
	*str1++ = *str2++;
    }
    *str1 = '\0';
    return str;
}

char *myStrcpy(char *str1, char *str2)
{
    if(str1 == NULL && str2 == NULL)
    {
	return NULL; 
    }
    char *str = str1; 
    while(*str2 != '\0')
    {
	//if(*str2 != '\0')
	*str1++ = *str2++; 
    }
    *str1 = '\0';

    return str;
}

int myStrcmp(char *str1, char *str2)
{
    while(*str1 != '\0')
    {
	if(*str1++ != *str2++)
	{
	    return 1;	
	}
    }
    
    if(*str2 != '\0')
    {
	return -1; 
    }

    return 0;
}
