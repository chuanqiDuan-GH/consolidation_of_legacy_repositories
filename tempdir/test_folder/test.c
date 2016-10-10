#include<stdio.h>

void bubbleSort(int *arr, int len);
int IsBig_Endian();

int main()
{

    //int arr[10] = {0};
    //int *a = arr;
    //bubbleSort(a, 10); 
    //puts(a); 

    int ret = IsBig_Endian();
    printf("%d\n", ret);

   
}

int IsBig_Endian()
{
    unsigned short test = 0x1234;
    if(*( (unsigned char*) &test ) == 0x12)
	return 1;
    else
	return 0;
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
