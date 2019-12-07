/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:3-priFromTail2Head.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-08 23:09
*   Describe:剑指offer-Q5-从尾到头打印链表
********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int value;
    struct ListNode *pNext;
} Node, *pNode;

void PriListFromTail2Head(pNode head)
{
    pNode tmp = head;
    if (tmp)
    {
        PriListFromTail2Head(tmp->pNext);
        printf("%d ", tmp->value);
    }
}

pNode CreateList(pNode head, int value)
{
    if (NULL == head)
    {
        head = (pNode)malloc(sizeof(Node));
        head->pNext = NULL;
        head->value = 0;
    }
    else
    {
        pNode node = (pNode)malloc(sizeof(Node));
        node->value = value;
        node->pNext = head->pNext;
        head->pNext = node;
    }
    return head;
}

int main()
{
    pNode head = NULL;
    int i = 5;

    while (i >= 1)
        head = CreateList(head, i--);

    pNode tmp = head;
    /*正序输出*/
    while (tmp)
    {
        printf("%d ", tmp->value);
        tmp = tmp->pNext;
    }
    printf("\n");

    /*逆序输出*/
    PriListFromTail2Head(head);
}
