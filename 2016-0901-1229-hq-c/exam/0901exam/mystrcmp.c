#include<stdio.h>


int myStrcmp(char *s1, char *s2);

int main()
{
    char *s1 = "ab";
    char *s2 = "abcd";
    int result = myStrcmp(s1, s2); 
    printf("%d\n", result);

}

int myStrcmp(char *s1, char *s2)
{
    while(*s1 != '\0')
    {
	if(*(s1++) != *(s2++))
	{
	    return 1;	
	}
	 
    }
    if(*s2 != '\0')
    {
	return -1; 
    }

    return 0;
}
