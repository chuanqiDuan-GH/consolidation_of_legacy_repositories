#include<stdio.h>

int main()
{
    
    int num1, num2, num3;
    int temp, max;

    scanf("%d%d%d", &num1, &num2, &num3);

    temp = num1 > num2 ? num1 : num2;
    max = temp > num3 ? temp : num3;
    
    printf("max num = %d\n", max); 
    return 0; 
}
