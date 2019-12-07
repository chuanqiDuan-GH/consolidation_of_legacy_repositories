#include <stdio.h>

void BubbleSort(int *arr, int len);

int main()
{
    int i;
    int arr[] = {9, 10, 20, 0, 3};

    BubbleSort(arr, sizeof(arr)/sizeof(int));
    for(i=0; i<sizeof(arr)/sizeof(int); i++)
	printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

void BubbleSort(int *arr, int len)
{
    int swapFlag = 1;
    int tmp;
    int i;
    int j;

    if(NULL == arr || len <= 1)
	return;

    for(i=len; i>0; i--)
    {
	for(j=0; j<len; j++)
	{
	    if(arr[j] > arr[j+1])
	    {
		tmp = arr[j];				 
		arr[j] = arr[j+1];
		arr[j+1] = tmp;
		swapFlag = 0;
	    }
	}

	if(swapFlag)
	    break;
    }
}

