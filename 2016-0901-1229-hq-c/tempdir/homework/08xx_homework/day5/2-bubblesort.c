#include<stdio.h>

int main( )
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
	printf("%d ", num[j]);
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
	
	#if 0
	for(column=1; column<row; column++)
	{
	    if(num[column-1] < num[column])
	    {
		int temp = num[column];
		num[column] = num[column-1];
		num[column-1] = temp;	
	    }	
	}
	#endif
    }

    for(int j=0; j<10; j++)
    {
	printf("%d ", num[j]);
    }
}
