#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

pQueue pHead = NULL;
pQueue pEnd = NULL;

pTree createTree(int *arr, int len)
{
    if ( NULL == arr )
    {
	return NULL;
    }

    Tree *proot = (Tree*)malloc(sizeof(Tree));
    if ( NULL == proot)
    {
	return proot;
    }
    memset(proot,0,sizeof(Tree));
    proot->value = arr[0];
#if 0
    Tree *proot = CreateTreeNode(arr[0]);


    if ( NULL == proot )
    {
	return proot;
    }
#endif

    int i = 1;
    Tree *prootTmp = NULL;
    // Tree *pNode = NULL;
    for ( i = 1 ; i <len ; i++ )
    {
	prootTmp = proot;
	Tree *pNode = (Tree*)malloc(sizeof(Tree));
	if ( NULL == pNode)
	{
	    break;
	}
	memset(pNode, 0, sizeof(Tree));
	pNode->value = arr[i];
#if 0
	pNode = CreateTreeNode(arr[i]);
	if ( NULL == pNode)
	{
	    break;
	}
#endif
	while ( 1 )
	{
	    if ( pNode->value > prootTmp->value)
	    {
		if ( NULL == prootTmp->pR)
		{
		    prootTmp->pR = pNode;
		    break;
		}
		else
		{
		    prootTmp = prootTmp->pR;
		}
	    }
	    else
	    {
		if ( NULL == prootTmp->pL)
		{
		    prootTmp->pL = pNode;
		    break;
		}
		else
		{
		    prootTmp = prootTmp->pL;
		}
	    }
	}
    }

    return proot;
}

//尾部插入
void enQueue(pTree root)
{
    if(NULL == root)
    {
	return; 
    }

    pQueue tmp = (pQueue)malloc(sizeof(Queue));
    tmp->node = root;
    tmp->pNext = NULL;
    
    if(NULL == pHead)
    {
	pHead = tmp;
	pEnd = tmp;
    }
    else
    {
	//尾插
	pEnd->pNext = tmp;
	pEnd = tmp;
    }
}

//头部删除
pTree deQueue()
{
    if(NULL == pHead)
    {
	return NULL; 
    }
    else
    {
	pQueue del = pHead;
	pTree tree = del->node;

	if(pHead == pEnd)
	{
	    pEnd = NULL;	
	}	

	pHead = pHead->pNext;
	free(del);
	del = NULL;

	return tree;
    }
}

void levelOrder(pTree root)
{
    while(root)
    {
	printf("%d ", root->value); 
    
	if(root->pL)
	{
	    enQueue(root->pL);	
	}
	if(root->pR)
	{
	    enQueue(root->pR);	
	}
	root = deQueue();
    }
    printf("\n");
}

void inOrder(pTree root)
{
    if(root)
    {
	if(root->pL) 
	    inOrder(root->pL);
	printf("%d ", root->value);
	if(root->pR)
	    inOrder(root->pR);
    }
}
