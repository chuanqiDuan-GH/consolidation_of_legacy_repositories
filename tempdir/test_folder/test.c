#include<stdio.h>

void bubbleSort(int *arr, int len);

int main()
{

    int arr[10] = {0};
    int *a = arr;
    bubbleSort(a, 10); 
   //puts(a); 
   
}


void bubbleSort(int *arr, int len)
{
    int firRound = len;
    int secRound = 0;

    for(int i=firRound; i>0; i--)
    {
	for(int j=secRound; j<firRound; j++)
	{
	    if(arr[j] < arr[j+1])
	    {
		int temp = arr[j];
		arr[j] = arr[j+1];
		arr[j+1] = temp;
	    }
	}
    }

}
