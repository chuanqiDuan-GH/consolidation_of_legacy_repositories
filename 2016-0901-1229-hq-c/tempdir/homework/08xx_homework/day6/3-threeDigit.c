#include<stdio.h>

int main()
{
    int num[4] = {1, 2, 3, 4};
    int bai = 0;
    int shi = 0;
    int ge = 0;
    int count = 0;
#if 0
    int count = 0; 
    int i = 0;
    while(count < 4)
    {
	//向没定义长度的数组内输入数据时，从下标为0处开始，尽量正序输入
	scanf("%d", &num[count]);
	printf("%d ", num[count]);
	count++;  
    }
    while(i < 4)
    {
	printf("%d ", i);
	printf("%d ", num[i]);
	i++; 
    }
#endif
#ifdef RANDOM_INPUT
    for(int i=0; i<4; i++)
    {
	bai = num[i];
	for(int j=0; j<4; j++)
	{
	    shi = num[j];
	    for(int k=0; k<4; k++)
	    {
		ge = num[k];

		if(bai != shi && bai != ge && shi != ge
			&& (shi == 0 && bai != 0)
			&& (ge == 0 && shi != 0 && bai != 0))
		{
		    printf("%d%d%d\n", bai, shi, ge);	
		}
	    }
	}
    }
#endif
    for(int bai=1; bai<=4; bai++)
    {
	for(int shi=1; shi<=4; shi++)
	{
	    for(int ge=1; ge<=4; ge++)
	    {
		if(bai != shi && shi != ge && ge != bai)
		{
		    count++;
		    printf("%d%d%d\n", bai, shi, ge);
		}
	    }
	}
    }
    printf("total number is %d\n", count);
    return 0;
}
