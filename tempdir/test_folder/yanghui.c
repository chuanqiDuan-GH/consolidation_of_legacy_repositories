#include <stdio.h>  

void printTri(int* a, int n)  
{  
    int i;  
    for (i = 0; i <= n; i++)  
    {  
	printf("%d ",a[i]);  
    }  
    printf("\n");  
}  

int main()  
{  
    int i, j, N;  
    int a[100] = {1, 0};  

    int len = sizeof(a)/sizeof(a[0]);
    printf("%d\n", len);
    for(int k=0; k<100; k++)
    {
	printf("%d ", a[k]); 
    }
    int old, s;  
    printf("Input the number of line:");  
    scanf("%d",&N);  
    for (i = 0; i < N; i++)  
    {  
	old = a[0];  
	for (j = 0; j < i; j++)  
	{  
	    s = old;  
	    old = a[j + 1];  
	    a [j + 1] = s + old;  
	}  
	//	printTri(a,i);  
    }  
    return 0;  
}  
