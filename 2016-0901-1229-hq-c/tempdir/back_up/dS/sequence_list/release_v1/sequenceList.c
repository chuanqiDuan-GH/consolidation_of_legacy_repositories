#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequenceList.h" 


pList creatList()
{
    pList p_list = NULL; 
    p_list = (pList)malloc(sizeof(List));
    if(NULL == p_list)
    {
	return NULL;
    }
    memset(p_list, 0, sizeof(List));
    return p_list;
}

int insertList(pList p_list, int i_position, int value)
{
    if(NULL == p_list || i_position > p_list->listLen || p_list->listLen == LIST_AMOUNT)
    {
	return ERR_INFO; 
    }

    int i = i_position;
    for(; i<p_list->listLen; i++)
    {
	int temp = p_list->arr[i+1];
	p_list->arr[i+1] = p_list->arr[i]; 
    }
    p_list->arr[i_position] = value;
    p_list->listLen++;
    return OK_INFO;
}

int deleteList(pList p_list, int d_position)
{
    if(NULL == p_list || d_position > p_list->listLen-1 || 0 == p_list->listLen)
    {
	return ERR_INFO; 
    }

    int remind = p_list->arr[d_position];
    int i = d_position;
    for( ; i<p_list->listLen; i++)
    {
	p_list->arr[i] = p_list->arr[i+1];
    }
    p_list->listLen--;
    return OK_INFO; 
}

int modifyList(pList p_list, int m_position, int value)
{
   if(NULL == p_list || m_position > p_list->listLen-1)
   {
	return ERR_INFO; 
   }
    int i = m_position;
    p_list->arr[m_position] = value;
    return OK_INFO; 
}

void showList(pList p_list)
{
    if(NULL == p_list)
    {
	return; 
    }
    
    int i = 0;
    for( ; i<p_list->listLen; i++)
    {
	printf("%d ", p_list->arr[i]);
    } 
    printf("\n");
}
