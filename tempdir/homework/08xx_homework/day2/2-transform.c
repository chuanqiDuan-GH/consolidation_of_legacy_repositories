#include<stdio.h>

int main()
{
#if 1
    int input;
    int transform[20] = {0};
    int count = 0;
    scanf("%d", &input);

    while((input/2) != 0)
    {
	//printf("%d ", transform[count]); 
	transform[count++] = input % 2;
	input /= 2;
    }
    transform[count] = 1; 
    //printf("%d ", transform[count]); 

    do
    {
	printf("%d ", transform[count]); 
    }while(count--);
#endif

}
