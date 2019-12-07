#include <stdio.h>

void InsertSort(int *arr, int len);

int main()
{
    int i;
    int arr[] = {9, 10, 20, 0, 3};

    InsertSort(arr, sizeof(arr)/sizeof(int));
    for(i=0; i<sizeof(arr)/sizeof(int); i++)
	printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void InsertSort(int *arr, int len)
{
    if(NULL == arr || len <= 1)
	return;

    int i;
    int j;
    int tmp;

    for(i=1; i<len; i++)
    {
	for(j=i-1; j>=0; j--)
	{
	    if(arr[j+1] < arr[j] )
	    {
		tmp = arr[j];	 
		arr[j] = arr[j+1];
		arr[j+1] = tmp;
	    }
	}
    }
}
