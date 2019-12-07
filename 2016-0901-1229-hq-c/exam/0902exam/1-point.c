#include<stdio.h>

int main()
{
   int n1 = 1;
   int n2 = 2;
   int n3 = 3;
    
    
    int *a = &n1;
    int *b = &n2;
    int *c = &n3;
    
    
    int max,min;
    
    max = *a>*b ? *a : *b;
    min = *a<*b ? *a : *b;
    
    if(*c > max) 
	max = *c;
    if(min > *c) 
	min = *c;
    
    printf("%d %d %d\n",max,*a+*b+*c-max-min,min);       
}

