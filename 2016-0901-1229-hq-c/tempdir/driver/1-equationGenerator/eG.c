#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "func.h"
#include "common.h"

//eg caller
int main(int argc, char *argv[])
{
    if(argc != 2){
	printf("ARGC ERROR\n");
	return 0; 
    }

    srand((unsigned)time(NULL));
    eqCount = (int)(argv[1][0] - '0');  

    fd = open("./eG_file",O_CREAT | O_WRONLY | O_TRUNC, 0777);
    while(eqCount--){
	numGene(nA);	
	symGene(nA, sA);	

	//printf("eqCount%d\n", eqCount);
	//printf("%d %d %d\n", nA[0], nA[1], nA[2]);
	//printf("%c %c\n", sA[0], sA[1]);

	result = verify(&nA[0], &nA[1], sA[0]);
	finall = verify(&result, &nA[2], sA[1]);

	printer(nA, sA, finall);	
	writeInFile(fd, nA, sA, finall);
    }
    close(fd);
    return 0; 
}
