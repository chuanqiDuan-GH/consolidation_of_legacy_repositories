#include<stdio.h>


int main()
{
    int a;
    int b;
    int c;

    scanf("%d%d%d", &a, &b, &c);
    
    int *p1 = &a;
    int *p2 = &b;
    int *p3 = &c;

    int min = *p1 < *p2 ? *p1 : *p2;
    int max = *p1 > *p2 ? *p1 : *p2;

    if(*p3 > max)
	max = *p3; 
    if(*p3 < min)
	min = *p3; 

    printf("%d %d %d\n", min, (*p1 + *p2 + *p3 - max - min), max);
    return 0;
}
