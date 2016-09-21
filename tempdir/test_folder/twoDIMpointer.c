#include<stdio.h>
//数组指针和二维数组
int main()
{
    int a[2][3]={1,2,3,4,5,6};
    int b[3] = {1,2,3};
    int (*p)[3] =&b;
    int i,j;
    for(i=0;i<3;i++)
    {
	printf("%d  ",*(p[0]+i));
    }
    printf("\n");
    int (*q)[3]= a;
    for(i=0;i<2;i++)
	for(j=0;j<3;j++)
	{
	    printf("%d\n",*(q[i]+j));
	}
    int *x[2];
    x[0]= a[0];
    x[1]= a[1];
    printf("a[1][2]=%d   ",*(x[1]+2));
    printf("\n");
    printf("%d\n%d\n%d\n",a[1][2],*(a[1]+2),*(*(a+1)+2));
    return 0;
}
