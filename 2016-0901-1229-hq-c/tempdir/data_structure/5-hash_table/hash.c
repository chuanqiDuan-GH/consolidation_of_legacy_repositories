#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"



pHash createHash()
{
    pHash table = (pHash)malloc(sizeof(Hash));
    if(NULL == table)
    {
	return NULL;
    }
    memset(table, 0, sizeof(Hash));
    return table;
}

int insertNode(pHash table, int i_data)
{
    if(NULL == table)
    {
	return -1; 
    }
    int tableIndex = i_data % 10;
    printf("%d\n", tableIndex);
    pNode insNode = (pNode)malloc(sizeof(Node));
    if(NULL == insNode)
    {
	return -1; 
    }
    insNode->data = i_data;
    /*这里的头插不是在头结点的下一个插入，而是在头指针的下一个插入
    所以先用新来的node的pNext指向头指针指向的结点（最开始是NULL）
    所以不用区分是否为第一次添加结点，然后在让头指针指向新来的*/
    insNode->pNext = table->pHead[tableIndex];
    table->pHead[tableIndex] = insNode;
    
    return 0;
}

int deleteNode(pHash table, int d_data)
{
    if(NULL == table)
    {
	return -1; 
    }
    int tableIndex = d_data % 10;
    pNode head = table->pHead[tableIndex];
    //pNode del = head->pNext; 

    //在删除时有一种特殊情况，该结点是第一各个结点
    if(table->pHead[tableIndex]->data == d_data)
    {
	table->pHead[tableIndex] = head->pNext; 
	free(head);
	head = NULL;
	return 0;
    }
    else
    {
	while(NULL != head)
	{
	    pNode del = head->pNext;
	    if(del->data == d_data)
	    {
		head = head->pNext;
		free(del);
		del = NULL;
		return 0;
	    }
	    head = head->pNext;
	}
    }
    return -1;
}

int destoryTable(pHash table)
{
    if(NULL == table)
    {
	return -1; 
    }
	pNode tmp = NULL;
	pNode del = NULL;
    for(int i=0; i<TABLE_SIZE; i++)
    {
	if(NULL == table->pHead[i])
	{
	    continue;	
	}

	del = table->pHead[i];
	//删除的时候思路要清晰，头删除前记住下一个结点，再把记住的结点当作新头
	while(del = NULL)
	{
	    tmp = del->pNext;
	    free(del);
	    del = tmp;
	}
    }
    free(table);
    table = NULL;
    tmp = NULL;
    del = NULL;
    return 0;
}

void showTableNode(pHash table)
{
    if(NULL == table)
    {
	return; 
    }
    for(int i=0; i<TABLE_SIZE; i++)
    {
	if(NULL == table->pHead[i])
	{
	    continue;	
	}

	pNode tmp = table->pHead[i];

	while(NULL != tmp)
	{
	    printf("%d ", tmp->data);	
	    tmp = tmp->pNext;
	}
    }
}

