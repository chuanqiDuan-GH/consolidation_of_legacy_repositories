#include<stdio.h>

int main(int argc, char* argv[])
{
    int num[10] = {0};
    int row;
    int column;	
    int i=0;

    for(i; i<10; i++)
    {
	scanf("%d", &num[i]);
    }

    for(int j=0; j<10; j++)
    {
	printf("num[%d]=%d\n", j, num[j]);
    }	

    printf("\n");
    for(row=10; row>0; row--)
    {
	for(column=0; column<row; column++)
	{
	    if(num[column] < num[column+1])
	    {
		int temp = num[column+1];
		num[column+1] = num[column];
		num[column] = temp;	
	    }	
	}
    }
    for(int j=0; j<10; j++)
    {
	printf("num[%d]=%d\n", j, num[j]);
    }
}
