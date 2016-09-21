#include<stdio.h>

char *myStrncat(char *str1, const char *str2, size_t n);
char *myStrncpy(char *str1, char *str2, size_t n);
int myStrncmp(char *str1, char *str2, size_t n);

int main()
{
    
    char str1[] = "0";
    char str2[] = "0";
    size_t n;

    gets(str1);
    gets(str2);
    scanf("%d", &n);
    //char *str = myStrncat(str1, str2, n);
    //char *str = myStrncpy(str1, str2, n);
    
   int result = myStrncmp(str1, str2, n); 
   printf("%d\n", result); 
    //printf("%s\n", str);
   return 0; 
}


char *myStrncat(char *str1, const char *str2, size_t n)
{
    if(str1 == NULL || str2 == NULL)
    {
	return NULL; 
    }
    
    char *str = str1; 
    
    while(*str1 != '\0')
    {
	str1++; 
    }
    while(n > 0)
    {
	if(*str2 != '\0')
	{
	    *str1++ = *str2++;
	}
	n--;
    }
    *str1 = '\0'; 

    return str;
}

char *myStrncpy(char *str1, char *str2, size_t n)
{
    if(str1 == NULL || str2 == NULL)
    {
	return NULL;
    }
    
    char *str = str1;
    while(n > 0)
    {
	if(*str2 != '\0')
	{
	    *str1++ = *str2++;	
	}
	n--;
    }
    *str1 = '\0';

    return str;
}

int myStrncmp(char *str1, char *str2, size_t n)
{
    while(--n && *str1 && *str1 == *str2)
    {
	str1++;
	str2++;
    }

    return (*str1 -*str2);

}

#ifdef MY_NCMP 
int myStrncmp(char *str1, char *str2, size_t n)
{
    while(n-- && *str1)
    {
	if(*str1++ == *str2++)
	{
	    return 1;	
	}
	if(*str2 != '\0' n >= 0)
	{
	    return -1; 
	}
    }

    return 0;
}
#endif
