#include<stdio.h>

float getAS(float score[]);

int main()
{
    float score[10] = {0}; 
    float finall_score = 0; 

    for(int i=0; i<10; i++)
    {
	scanf("%f", &score[i]); 
    }

    finall_score = getAS(score); 
    printf("%f\n", finall_score);
    return 0;
}

float getAS(float score[])
{
    //当max和min为int型时，返回值没有小数部分
    float max = 0;
    //一个定义好的最大值作为min的初始值？
    float min = 32767;
    float sum = 0;
    for(int i=0; i<10; i++)
    {
	if(score[i] > max)
	{
	    max = score[i];	
	}

	if(score[i] < min)
	{
	    min = score[i];	
	}
	sum += score[i]; 
    }
    printf("%f %f\n", max, min);

    return (sum-max-min)/8;
}
