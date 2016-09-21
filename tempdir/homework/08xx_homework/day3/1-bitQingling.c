//实现对应bit位清零
#include<stdio.h>

int main()
{
    int num;
    int position;
    int binaryNum[] = {0}; 
    int count = 0; 
    int temp = 0; 

    scanf("%d%d", &num, &position);
    while((num /2) != 0)
    {
	binaryNum[count++] = num % 2;
	num /= 2;
    }
    binaryNum[count] = 1;
    temp = count; 
    //置零前的二进制数 
    do
    {
	printf("%d ", binaryNum[count]); 
    }while(count--);

    printf("\n"); 
    //清零对应bit位
    if(position <= (temp+1))
    {
	binaryNum[position-1] = 0; 
    }
#if 1 
    //对应位置零后的二进制数 
    do
    {
	printf("%d ", binaryNum[temp]); 
    }while(temp--);
#endif
    return 0;
}
