#include<stdio.h>
#include<string.h>
#define FUNC

void findSubstr(char *a, char *b);

int main()
{
    char a[100] = {'0'};
    char b[100] = {'0'};

    char *str = a;
    char *substr = b; 
    char *temp = substr;
    int i = 0;

    scanf("%s%s", str, substr);
#ifdef MAIN
    while(*substr != '\0')
    {
	if(*str == '\0')
	    break; 

	if(*substr != *str)
	{
	    substr = temp;	
	    i++;	
	}
	    substr++;
	    str++;
    }
    if(*substr == '\0')
	printf("%d\n", i+1); 
    else
	printf("find nothing\n"); 
#endif
    findSubstr(str, substr);
    return 0;
}

#ifdef FUNC
void findSubstr(char *str, char *substr)
{
    char *temp = substr;
    int i = 0;
    while(*substr != '\0')
    {
	if(*str == '\0')
	    break; 

	if(*substr != *str)
	{
	    substr = temp;	
	    i++;	
	}
	substr++;
	str++;
    }
    if(*substr == '\0')
	printf("%d\n", i+1); 
    else
	printf("find nothing\n"); 
}
#endif
