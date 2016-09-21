//求输入任意数的阶乘
#include<stdio.h>

int main()
{
    int input;
    int factorial = 1;

    scanf("%d", &input);
    
    while(input > 1)
    {
	factorial *=(input--);
    }

    printf("%d\n", factorial);

    return 0;
}
