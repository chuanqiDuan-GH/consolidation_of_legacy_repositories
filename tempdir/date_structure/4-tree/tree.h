#ifndef _TREE_H_
#define _TREE_H_
#include <stdio.h>

//typedef int t_data

typedef struct _Tree
{
    int value;
    struct _Tree *pL;
    struct _Tree *pR;
}Tree, *pTree;

typedef struct _Queue
{
    pTree node;
    struct _Queue *pNext;
}Queue, *pQueue;

pTree createTree(int *arr, int len);
void enQueue(pTree root);
pTree deQueue();
void levelOrder(pTree root);
void inOrder(pTree root);


#endif	//_TREE_H_
