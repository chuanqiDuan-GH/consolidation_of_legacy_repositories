#include <stdio.h>

void bubbleSort(int *arr, int size)
{
    printf("%s\n", __func__);
    int i;
    int j;
    int tmp;

    for(i=0; i<size; i++)
    {
	for(j=size-1; j>i; j--)
	{
	    if(*(arr+j) < *(arr+j-1) )
	    {
		tmp = *(arr+j); 
		*(arr+j) = *(arr+j-1);
		*(arr+j-1) = tmp;
	    }
	}
    }
}

/*插入排序:将数组无序部分的第一个数插入数组有序部分*/
void insertSort(int *arr, int size)
{
    printf("%s\n", __func__);
    int i, j;
    int tmp;
    for(i=1; i<size; i++)
    {
	for(j=i-1; j>=0&&arr[j]>arr[j+1]; j--)
	{
	    tmp = arr[j];
	    arr[j] = arr[j+1];
	    arr[j+1] = tmp;
	}

    }
}

/*选择排序:将数组无序部分最大(小)插入数组有序部分的最后一个*/
void selectSort(int *arr, int size)
{
    printf("%s\n", __func__);
    int i, j;
    int tmp;
    int min;

    for(i=0; i<size; i++)
    {
	min = i;
	for(j=i+1; j<size; j++)
	{
	    if(arr[j] < arr[min])
		min = j; 
	}
	tmp = arr[i];
	arr[i] = arr[min];
	arr[min] = tmp;
    }
}
