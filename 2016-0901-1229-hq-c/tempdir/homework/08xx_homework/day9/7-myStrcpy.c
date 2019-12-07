/*************************************************
设计一个函数实现strcpy功能
*************************************************/
#include<stdio.h>

char *myStrcpy(char *s1, const char *s2);

int main()
{
    char s1[20];
    char *s2 = "hello linux";
    myStrcpy(s1, s2); 
    printf("%s\n", s1);

}

char *myStrcpy(char *s1,const char *s2)
{
    if(s1 == NULL || s2 == NULL)
    {
	return NULL; 
    }
    char *temp = s1; 
    while(*s2 != '\0')
    {
	*(s1++) = *(s2++);
    }

    return temp;
}

