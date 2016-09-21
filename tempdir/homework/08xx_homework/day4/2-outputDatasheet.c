#include<stdio.h>
#include<math.h>

int main()
{
    int ceiling;
    int floor;
    
    printf("please input two data and make the first data greater than the second data\n");
    scanf("%d%d", &ceiling, &floor);
    
    if(ceiling < floor)
    {
	printf("input data failure\n"); 
    }
    
    //pow(i,2)i的平方 pow(i,3)i的立方 pow函数返回值数据类型为double
    for(int i=floor; i<=ceiling; i++)
    {
	printf("%d\t %lf\t %lf\t\n", i, pow(i,2), pow(i,3)); 
    }

}
