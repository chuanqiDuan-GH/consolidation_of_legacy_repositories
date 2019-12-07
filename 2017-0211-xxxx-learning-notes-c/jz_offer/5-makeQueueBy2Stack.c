/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:5-makeQueueBy2Stack.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-12 21:03
*   Describe:剑指offer-Q7-两个栈实现队列
********************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACKLEN 10

typedef struct SeqStack
{
    int seqStack[STACKLEN];
    int topPos;
}Stack, *pStack;

pStack stack1 = NULL;
pStack stack2 = NULL;

pStack CreateStack()
{
    pStack root = (pStack)malloc(sizeof(Stack));      

    if(NULL == root)
    {
	printf("malloc failure.\n"); 
	return NULL;
    }
    memset(root, 0, sizeof(Stack));

    return root;
}

void PushStack(pStack root, int value)
{
    if(NULL == root || root->topPos == STACKLEN)
    {
	printf("stack full\n");    
	return;
    }

    root->seqStack[(root->topPos)++] = value;
}

void PopStack(pStack root)
{
    if(NULL == root || root->topPos == 0)
	return;	

    root->seqStack[--(root->topPos)] == 0;
}

void AppendTail(int value)
{
    if(NULL == stack1)
    {
	printf("stack error\n"); 
	return;
    }
	
    PushStack(stack1, value);
}

void DeleteHead()
{
    if(NULL == stack2) 
    {
	printf("stack error\n"); 
	return;
    }

    if(stack2->topPos == 0)
    {
	if(stack1->topPos == 0)
	{
	   printf("stack empty\n"); 
	   return;
	}

	while(stack1->topPos-1 > 0)
	{
	    PushStack(stack2, stack1->seqStack[(stack1->topPos)-1]);	
	    PopStack(stack1);
	}
	printf("%d %d\n", __LINE__, stack1->seqStack[(stack1->topPos)-1]);
	PopStack(stack1);
	return;
    }
    printf("%d %d\n", __LINE__, stack2->seqStack[(stack2->topPos)-1]);
    PopStack(stack2);
}

int main()
{
    stack1 = CreateStack();    
    stack2 = CreateStack(); 

    AppendTail(100);
    AppendTail(200);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);
    AppendTail(300);	//stack1满了
    DeleteHead();
    DeleteHead();
    AppendTail(400);
    DeleteHead();
    DeleteHead();
    DeleteHead();
    DeleteHead();
    DeleteHead();
    DeleteHead();
    DeleteHead();   //stack1和stack2都空了
    DeleteHead();
    DeleteHead();
    DeleteHead();

    return 0;
}
