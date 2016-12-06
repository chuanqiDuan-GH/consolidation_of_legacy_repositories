#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simpEq.h"


pList creatNode(pList head, int len)
{
    int i = 0;
    int factor;
    int index;
    pList new;
    pList tmp;
    char f_i[FILEN];

    head = (pList)malloc(sizeof(List)); 
    memset(head, 0, sizeof(List));
    if(NULL == head)
    {
	printf("create failed T.T\n"); 
	return;
    }
    tmp = head;

    for(i=0; i<len; i++)
    {
	new = (pList)malloc(sizeof(List));
	printf("please input factor and index: ");
	gets(f_i);
	factor = atoi(strtok(f_i, " "));
	index = atoi(strtok(NULL, " "));
	//printf("%d %d\n", factor , index);
	new->factor = factor;
	new->index = index;
	//printf("%d %d\n", new->factor , new->index);
	new->pNext = NULL;
	tmp->pNext = new;
	tmp = new;
    }

    return head;
}

void show(pList head)
{
    int i;
    pList tmp = head->pNext;

    while(NULL != tmp)
    {
	//printf("%d %d\n", tmp->factor , tmp->index);
	if(0 == tmp->factor)
	{
	    continue;
	}
	else if(0 == tmp->index)
	{
	    printf("%d", tmp->factor); 
	}
	else
	{
	    printf("%dX^%d", tmp->factor, tmp->index);	
	}
	tmp = tmp->pNext;
	if(NULL != tmp)
	{
	    printf(" + ");
	}
    }
    printf("\n");
}
