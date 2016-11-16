#if 0
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main()
{
    int i;
    srand((unsigned)time(NULL));
    for(i=0;i<10;i++)
	printf("%lfn",rand()/(float)(RAND_MAX)*4+3); //这是关键的一步
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void main()
{
    int i;

    srand((unsigned)time(NULL));
    for(i=0; i<5; i++)
    {
	printf("%d ", rand()%10);
    }
}

#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void numGene(int *nA)
{    
    int i;
    srand((unsigned)time(NULL));
    for(i=0; i<3; i++)
    {
	*(nA+i) = rand()%100;
	printf("%d ", *(nA+i));
    }
   
}

void main()
{   
    int nA[3] = {0};
    int i;
    numGene(nA);   
    for(i=0; i<3; i++)
    {
	printf("%d ", nA[i]);
    }
}
#endif
