/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:8-singleListReverse.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-21 22:44
 *   Describe:单链表逆序
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define LISTTYPE int

typedef struct ListNode
{
    LISTTYPE value; 
    struct ListNode *pNext;
}Node, *pNode;

pNode AddList(LISTTYPE value, pNode head)
{
    pNode new = (pNode)malloc(sizeof(Node));
    if(NULL == new)
	return NULL;
    new->value = value;
    new->pNext = NULL;

    if(NULL == head)
	head = new;
    else
    {
	new->pNext = head->pNext;
	head->pNext = new;
    }
    return head;
}


pNode Reverse(pNode head)
{
    if(NULL == head)
	return head;

    pNode tmp = head->pNext;
    pNode rear = head;
    pNode front = NULL;
    head->pNext = NULL;

    while(tmp)
    {
	front = tmp; 
	tmp = tmp->pNext;
	front->pNext = rear;
	rear = front;
    }
    head = rear;
    return head;
}

int main()
{
    pNode head = NULL;
    head = AddList(1, head);
    head = AddList(2, head);
    head = AddList(3, head);
    head = AddList(4, head);

    pNode tmp = Reverse(head);
    while(tmp)
    {
	printf("%d\n", tmp->value);
	tmp = tmp->pNext;
    }
    return 0;
}
