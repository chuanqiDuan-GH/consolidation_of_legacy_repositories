#include<stdio.h>

#define LEN 10

int *selectSort(int arr[], int len);

int main()
{
    int num[LEN] = {0}; 
    int i;

    for(i=0; i<10; i++)
    {
	scanf("%d", &num[i]); 
    }

    int *pNum = selectSort(num, LEN);

    while(i > 0)
    {
	printf("%d ", *pNum++); 
	i--;
    }
	return 0;
}

int *selectSort(int arr[], int len)
{
    int i = 0;
    int mark = 0;
    int swap = 0;
    int *p = arr;

   for( ; i<len; i++)
   {
	int min = arr[i];
	mark = i;
	for(int j=i+1 ; j<len; j++)
	{
	    if(arr[j] < min)
	    {
		min = arr[j]; 
		mark = j;
	    }
	}
	swap = arr[i];
	arr[i] = min;
	arr[mark] = swap;
    }
    for(int k=0; k<10; k++)
    {
	printf("%d ", arr[k]); 
    }
	printf("\n");

    return p; 
}
