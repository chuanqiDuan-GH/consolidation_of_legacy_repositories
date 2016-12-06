#include <stdio.h>

typedef void (*cbFunc)(int, int);

void call(cbFunc pcbFunc, int num1, int num2)
{
    pcbFunc(num1, num2);
}

void op_plus(int num1, int num2)
{
    printf("%d + %d = %d\n", num1, num2, num1+num2);    
}

void op_sub(int num1, int num2)
{
    printf("%d - %d = %d\n", num1, num2, num1-num2);    
}

void op_mul(int num1, int num2)
{
    printf("%d * %d = %d\n", num1, num2, num1*num2);    
}

void op_div(int num1, int num2)
{
    if(0 == num2)
    {
	printf("R U serious.\n");
	return;
    }
    printf("%d / %d = %d\n", num1, num2, num1/num2);    
}
