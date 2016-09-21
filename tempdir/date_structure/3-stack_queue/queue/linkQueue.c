#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkQueue.h"

//FIFO
pQueue createLikQueue()
{
    pQueue node = (pQueue)malloc(sizeof(Queue));
    if(NULL == node)
    {
	return NULL; 
    } 
    memset(node, 0, sizeof(Queue));
    return node;
}

//head insert
int insertLikQueue(pQueue node, int i_value)
{
    if(NULL == node)
    {
	return ERR_INFO;
    } 
    pQueue insNode = (pQueue)malloc(sizeof(Queue));
    if(NULL == insNode)
    {
	return ERR_INFO; 
    } 

    if(NULL == node->pNext)
    {
	node->pNext = insNode; 
	node->pPrev = insNode;
	insNode->pPrev = node;
	insNode->pNext = node;
	insNode->value = i_value;
    } 
    else
    {
	node->pNext->pPrev = insNode;
	insNode->pNext = node->pNext;
	node->pNext = insNode;
	insNode->pPrev = node;
	insNode->value = i_value;
    }

    return OK_INFO;
}

//tail delete
int deleteLikQueue(pQueue node)
{
    if(NULL == node->pNext)
    {
	return ERR_INFO; 
    }

    pQueue del = node->pPrev;
    if(NULL == del->pNext)
    {
	node->pNext = NULL;
	node->pPrev = NULL;
	del->pPrev = NULL;
    } 
    else
    {
	del->pPrev->pNext = node;
	node->pPrev = del->pPrev;
    }
    free(del);
    del = NULL;
    return OK_INFO;
}

void showLikQueue(pQueue node)
{
    if(NULL == node)
    {
	return; 
    }
    pQueue tmp = node->pNext;
    while(tmp != node)
    {
	printf("%d ", tmp->value); 
	tmp = tmp->pNext;
    }
    printf("\n");
}

