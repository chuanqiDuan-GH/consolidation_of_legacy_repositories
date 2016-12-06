#include <stdio.h>
#include "s_i.h"

#define SIZE 5

int main()
{
    int i = 0;
    int arr[SIZE] = {4, 2, 23, 0, 3};
#ifdef	BS 
    bubbleSort(arr, SIZE);
#endif
#ifdef	IS
    insertSort(arr, SIZE);
#endif
#ifdef	SS
    selectSort(arr, SIZE);
#endif

    for(; i<SIZE; i++)
    {
	printf("%d ", arr[i]); 
    }
    printf("\n");
    return 0;
}
