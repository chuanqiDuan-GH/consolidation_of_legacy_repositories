#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequenceStack.h"

pStack createSeqStack()
{
    pStack node = (pStack)malloc(sizeof(Stack));
    if(NULL == node)
    {
	return NULL; 
    }

    memset(node, 0, sizeof(Stack));
    return node;
}

int insertSeqStack(pStack node, int i_value)
{
    if(NULL == node || node->a_len > A_SIZE)
    {
	return ERR_INFO;	  
    }    

    node->arr[node->a_len++] = i_value; 
    //node->a_len++;
    return OK_INFO;
}

int deleteSeqStack(pStack node)
{
    if(NULL == node || node->a_len == 0)
    {
	return ERR_INFO; 
    }

    node->arr[node->a_len--] = 0;
    return OK_INFO;
}

void showSeqStack(pStack node)
{

    for(int i = 0; i < node->a_len; i++)
    {
	printf("%d ", node->arr[i]); 
    }
    printf("\n");
}

