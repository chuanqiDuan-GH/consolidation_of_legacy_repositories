#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void GetMemory(char **p, int num)
{
    *p = (char *)malloc(num);
}

int main()
{
    char *str = NULL; 
    GetMemory(&str, 100);
    strcpy(str, "hello");
    printf("%s\n", str);
    return 0;
}
