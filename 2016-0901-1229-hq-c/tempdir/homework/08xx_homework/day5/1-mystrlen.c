#include<stdio.h>

int myStrlen(char *str);

int main()
{
    int L = 0;
    char *str = "abcdef";
    L = myStrlen(str);
    printf("%d\n", L);
}


int myStrlen(char *str)
{
    char *temp = str;
    int length = 0;

    while(*temp != '\0')
    {
	temp++;
	length++;
    }

    return length;
}
