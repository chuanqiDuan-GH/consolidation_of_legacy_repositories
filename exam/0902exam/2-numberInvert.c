#include<stdio.h>

int *input();
struct jishu chose(int *num);

struct jishu
{
    int maxnum;
    int minnum;
};

int main()
{
    int *n = {0};
    
    n = input();    
    
    for(int i=0; i<10; i++)
    {
	printf("%d ", *n++);
    }
    printf("\n");
    struct jishu result = chose(n); 

    //printf("%d %d", result.maxnum, result.minnum);
}

int *input()
{
    static int num[] = {0}; 
    
    for(int i=0; i<10; i++)
    {
	scanf("%d", &num[i]);
    }
    return num; 
}

struct jishu chose(int *nu)
{
    int min = 32767;
    int max = 0;
    struct jishu JS;
    JS.minnum = 0;
    JS.maxnum = 0;

    for(int i=0; i<10; i++)
    {
	if(*nu < min)
	{
	    min = *nu;
	    JS.minnum++;
	}
	if(*nu > max)
	{
	    max = *nu;	
	    JS.maxnum++;
	}
	nu++; 
    } 
    printf("%d %d", max, min);
    printf("%d %d", JS.maxnum, JS.minnum);
    return JS; 
    
}
