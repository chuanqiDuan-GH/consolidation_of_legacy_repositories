//字符串大小写转化
//char *a和char a[]的区别主要在于前者是存放在常量区的，无法修改；后者是存放在栈区，可以修改
#include<stdio.h>

int main()
{
#if 0 
    char str[] = "adAfZXef A"; 
    int i = 0;  

    while(str[i] != '\0')
    {
	printf("%c\n", str[i]);  
	
	if((str[i]) >= 'a' && (str[i]) <= 'z')
	{
	    (str[i]) -= 32; 
	}
	else if((str[i]) >= 'A' && (str[i]) <= 'Z')
	{
	    (str[i]) += 32; 
	}
	i++;  
    }
#endif 
    char *str = "adAfZXef A";
    char strEx[10] = {'0'};
    int i = 0;  
    printf("%s\n", str);  

    while(*str != '\0')
    {
	
	if((*str) >= 'a' && (*str) <= 'z')
	{
	    //printf("a~z\n"); 
	    //此时申请的字符串放在常量区，无法需改，若修改，会出现段错误 
	    //(*str) -= 32; 
	    strEx[i++] = (*str) - 32;	
	    printf("%c\n", strEx[i]);  
	}
	else if((*str) >= 'A' && (*str) <= 'Z')
	{
	    //printf("A~Z\n"); 
	    //(*str) += 32; 
	    strEx[i++] = (*str) + 32;	
	    printf("%c\n", strEx[i]);  
	}
	str++;  
    }
    printf("%s\n", strEx);  
    return 0;
}
