/*************************************************************************
 设计一个函数，满足两个数的和差积商 
*************************************************************************/
#include<stdio.h>

int caculator(int num1, int num2, char symbol);

int main()
{
    int num1;
    int num2;
    char symbol;

    scanf("%d%c%d", &num1, &symbol, &num2);
    
    int result = caculator(num1, num2, symbol);
    printf("%d\n", result);

    return 0;
}

int caculator(int num1, int num2, char symbol)
{
    int result = 0;

    switch(symbol)
    {
	case '+':
	    result = num1 + num2;
	    break;
	case '-':
	    result = num1 - num2;
	    break;
	case '*':
	    result = num1 * num2;
	    break;
	case '/':
	    result = num1 / num2;
	    break;
    }

    return result;
    
}
