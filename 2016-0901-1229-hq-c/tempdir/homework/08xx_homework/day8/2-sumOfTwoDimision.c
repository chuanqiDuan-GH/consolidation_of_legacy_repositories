#include<stdio.h>
#define FUNC
int sum(int *p[2]);

int main()
{

    int num[2][3] = {{1, 2, 3}, {4, 5, 6}}; 
    int result = 0;    
    int *p[2];
#if MAIN 
    for(int i=0; i<2; i++)
    {
	p[i] = num[i];
	for(int j=0; j<3; j++)
	{
	    sum += *(p[i]+j);
	}
    }

#endif
    for(int i=0; i<2; i++)
    {
	p[i] = num[i]; 
    }
    result = sum(p);
    printf("%d\n", result);
    return 0;
}

#ifdef FUNC 
int sum(int *p[2])
{
    int result = 0 ;
    for(int i=0; i<2; i++)
    {
	for(int j=0; j<3; j++)
	{
	    result += *(p[i]+j);
	}
    }

    //printf("%d\n", result);
    return result;
}
#endif
