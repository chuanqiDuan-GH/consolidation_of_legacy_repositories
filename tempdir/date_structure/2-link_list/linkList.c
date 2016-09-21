#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"

int linkLength = 0;

pNode creatLink()
{
    pNode node = (pNode)malloc(sizeof(Node));
    if(NULL == node)
    {
	return NULL;
    }
    memset(node, 0, sizeof(Node));
    linkLength++;
    return node;
}

int insertLinkNode(pNode node, int value, int i_index)
{
    if(NULL == node)
    {
	return ERR_INFO; 
    }

    pNode istNode = NULL; 
    pNode tmpNode = node;

#if 0
    if( NULL == node->pNext)
    {
	istNode = (pNode)malloc(sizeof(Node)); 
	node->pNext = istNode;
	istNode->value = i_value;
	istNode->pNext = NULL;
	linkLength++;

	return OK_INFO;
    }
#endif

    if(i_index > linkLength)
    {
	return ERR_INFO;	 
    }
    while(--i_index)
    {
	tmpNode = tmpNode->pNext; 
    }

    istNode = (pNode)malloc(sizeof(Node)); 
    memset(istNode, 0, sizeof(Node));
    istNode->pNext = tmpNode->pNext;
    tmpNode->pNext = istNode;	
    istNode->value = value;
    linkLength++;

    return OK_INFO;
}

int deleteLinkNode(pNode node, int d_index)
{
    if(NULL == node->pNext)
    {
	return ERR_INFO; 
    }
   
    pNode preDel = node;
    pNode Del = node->pNext;
    while(--d_index)
    {
	preDel = preDel->pNext;
	Del = Del->pNext; 
    }
    
    preDel->pNext = Del->pNext;  
    linkLength--;
    free(Del);
    Del = NULL;

    return OK_INFO;
    
}

int modifyLinkNode(pNode node, int m_index)
{
    //to do
}

void showLink(pNode node)
{
    if(NULL == node->pNext)
    {
	return; 
    }
    
    pNode tmp = node->pNext;
    while(NULL != tmp)
    {
	printf("%d ", tmp->value); 
	tmp = tmp->pNext;
    }
    printf("\n");

}

void bubbleSort(pNode node)
{
    if(NULL == node->pNext)
    {
	return; 
    }

    pNode tmp;	//tmp用来更新循环尾点
    pNode pre = node;	//pre指向需要交换的第一个node的previous node
    pNode compFir = node->pNext;    //指向第一个node
    pNode compSec = node->pNext->pNext;	//指向第二个node
    pNode tail = NULL;	//记录冒泡的结尾

    //每次进行排序要从链表的头开始，经过冒泡将最大的node放到最后
    //每一轮选出一个最大的，tail要提前一个node
    for( ;tail != node; tail = tmp)
    {
	//每进行一轮最大node选择要从头开始，将三个指针都置回初始位置
	tmp = pre = node;
	compFir = pre->pNext;
	compSec = compFir->pNext;
		
	//用来比较的第二个node指针指向tail说明到末尾了，第一次tail为NULL，之后tail 每轮提前一个node
	while(compSec != tail)
	{
	    //比较&交换
	    if(compFir->value > compSec->value)
	    {
		compFir->pNext = compSec->pNext;
		compSec->pNext = compFir;
		pre->pNext = compSec; 
		tmp = compFir;
	    }
	    //动起来
	    pre = pre->pNext;
	    compFir = pre->pNext;
	    compSec = compFir->pNext;
	}
    }
}

void bubbleSort2 (pNode node)  
{  
    pNode tail; 
    pNode tmp; 
    pNode pre;
    pNode sec;  

    pre = node;
    for (tail = NULL; tail != node; tail = tmp) 
    {  
	for (tmp = pre = node; pre->pNext->pNext != tail; pre = pre->pNext)  
	{  
	    if (pre->pNext->value > pre->pNext->pNext->value)  
	    {  
		sec = pre->pNext->pNext; 
		pre->pNext->pNext = sec->pNext;
		sec->pNext = pre->pNext; 
		pre->pNext = sec; 
		tmp = pre->pNext->pNext; 
	    }  
	}  
    }  
}  

void selectSort(pNode node)
{
    if(NULL == node)
    {
	return; 
    }

    pNode newLink = NULL;   //新链表第一个node（有效元素）
    pNode newLinkTail = NULL;	//指向新链表的尾，最后加NULL
    pNode min;	//指向当前最小node
    pNode preMin;   //最小node的前驱
    pNode comp;	//指向遍历比较的node
    
    //旧链表会不断的被移除，所以只要判断头的下一个是否为空即可
    while(node->pNext != NULL)
    {
	//循环遍历	
	for(comp = node->pNext, min = node->pNext; comp->pNext != NULL; comp = comp->pNext)
	{
	    //比较&记录
	    if(comp->pNext->value < min->value)
	    {
		preMin = comp;
		min = comp->pNext;
	    }
	}

	//最小node放到新链
	if(NULL == newLink)
	{
	    newLink = min;
	    newLinkTail = min;
	}
	else
	{
	    newLinkTail->pNext = min;
	    newLinkTail = min;
	}

	//从旧链表移除
	if(min == node->pNext)
	{
	    node->pNext = min->pNext;
	}
	else
	{
	    preMin->pNext = min->pNext;	
	}
    }    
    //循环结束，末尾赋值NULL
    if(newLink != NULL)
    {
	newLinkTail->pNext = NULL; 
    }
    //头指向新链表
    node->pNext = newLink;
    //return node;
}


void selectSort2(pNode node)
{
    if(NULL == node)
    {
	return; 
    }
    
    pNode comp;
    pNode insPos;
    pNode min;
    pNode preMin;
    
    
    
}

