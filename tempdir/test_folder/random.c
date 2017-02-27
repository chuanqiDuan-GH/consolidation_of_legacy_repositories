#include<stdio.h>
//#include<stdlib.h>
#include<time.h>

#if 0
void main()
{
    int i;
    srand((unsigned)time(NULL));
    for(i=0;i<10;i++)
	printf("%lf ",rand()/(float)(RAND_MAX)*4+3); //这是关键的一步
}
#endif

void main()
{
    int i;

    srand((unsigned)time(NULL));

    printf("%d ", rand()%5+5);
    printf("%d ", rand()%5+5);
}


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
