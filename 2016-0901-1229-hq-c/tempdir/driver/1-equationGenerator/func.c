#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

//we need three numbers
void numGene(int *nA)
{    
    int i;
    for(i=0; i<3; i++)
	*(nA+i) = rand()%100;
}

//we need tow symbols
void symGene(int *nA, char *sA)
{
    int i;
    for(i=0; i<2; i++){    
	if(*(nA+i)%10 > 5)
	    *(sA+i) = '+';
	else
	    *(sA+i) = '-';
    }
}

//verify the result tow times
int verify(int *nA1, int *nA2, char sA)
{
    int re = 0;
    do{
	//用随机出的数字做产生符号的种子
	if(sA == '+')
	    re = *nA1 + *nA2;
	else
	    re = *nA1 - *nA2; 

	//数字不合适就做除以2的处理
	if(re < 0 || re >= 100)
	    *nA2 /= 2;
    }while(re < 0 || re >= 100);

    return re; 
}

//printer
void printer(int *nA, char *sA, int finall)
{
    printf("%d %c %d %c %d = %d\n", *nA, *sA, *(nA+1), *(sA+1), *(nA+2), finall);
}

//write data
void writeInFile(int fd, int *nA, char*sA, int finall)
{
    char tmpBuf[128] = {'0'};
    sprintf(tmpBuf, "%d %c %d %c %d = %d\n", *nA, *sA, *(nA+1), *(sA+1), *(nA+2), finall);

    //printf("%s\n", tmpBuf);
    write(fd, tmpBuf, sizeof(tmpBuf));
}
