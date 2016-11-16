#ifndef _FUNC_H_
#define _FUNC_H_

int fd = 0;

void numGene(int *nA);	//number generator, generate one number at one times
char symGene(int *nA, char *sA);	//symbol generator, generate one symbol at one times
int verify(int *num1, int *num2, char sym);   //verify the equation(0< result >100)
void printer(int *nA, char *sA, int finall);	//print the finall equation
void writeInFile(int fd, int *nA, char *sA, int finall);    //write data in the file

#endif
