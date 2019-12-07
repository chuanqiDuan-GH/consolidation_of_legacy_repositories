/************************************************************
 用函数实现1到n的阶乘 
************************************************************/
#include<stdio.h>

int factorial(int n);

int main()
{

    int n;
    scanf("%d", &n);

    int result = factorial(n);
    printf("%d\n", result);
    return 0;
}

int factorial(int n)
{
    int result = 1;
    
    while(n)
    {
	result *= n--; 
    }
    return result;
}
