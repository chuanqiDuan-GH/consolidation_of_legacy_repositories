//取整数从右侧开始的4~7位
#include<stdio.h>

int main()
{
    int num;
    //若不在定义时全部赋予初值0，后面在程序运行中程序输出或许会出问题 
    int binaryNum[10] = {0};
    int count = 0; 
    int temp = 0; 

    scanf("%d", &num);
    while((num /2) != 0)
    {
	binaryNum[count++] = num % 2;
	num /= 2;
    }
    binaryNum[count] = 1;
    temp = count; 
    //取值前的二进制数 
    do
    {
	printf("%d ", binaryNum[count]); 
    }while(count--);
    printf("\n");
#if 1
if(temp >= 6)
    {
	for(int i=6; i>=3; i--)
	{
	    printf("%d ", binaryNum[i]);	
	}
    }
    else if(temp<6 && temp>=3)
    {
	for(int j=6; j>temp; j--)
	{
	    printf("0 ");	
	}
	for(int i=temp; i>=3; i--)
	{
	    printf("%d ", binaryNum[i]);	
	}
	
    }
    else
    {
	for(int i=6; i>=3; i--)
	{
	    printf("0 ");	
	}
	 
    }
   #endif 
    return 0;
}
