#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequenceList.h" 
#define	REALLOC_FUNC 


pList creatList()
{
    pList p_list = NULL; 
    p_list = (pList)malloc(sizeof(List));
    if(NULL == p_list)
    {
	return NULL;
    }
    memset(p_list, 0, sizeof(List));
    p_list->arr = (int*)malloc(sizeof(int)*10);	 
    memset(p_list->arr, 0, sizeof(int)*10);
    return p_list;
}

int insertList(pList p_list, int i_position, int value)
{
    if(NULL == p_list || i_position > p_list->listLen)
    {
	return ERR_INFO; 
    }

    #ifdef MALLOC_FUNC
    int oldLen = length;
    int temp[length];
    int i;
    int j;
    if(p_list->listLen >= length)
    {
	for(i=0; i<oldLen; i++)
	{
	    temp[i] = *(p_list->arr++);
	}
	length += 10;
	p_list->arr = (int *)malloc(sizeof(int)*length);
	for(j=0; j<oldLen; j++)
	{
	    *(p_list->arr++) = temp[j];
	}
    }
    #endif
    
    //通过realloc实现动态扩容
    #ifdef REALLOC_FUNC
    //printf("%d\n", length);
    //printf("%d\n", p_list->listLen);
    if(p_list->listLen >= length)
    {
	length += 10;
	p_list->arr = (int*)realloc(p_list->arr, sizeof(int)*length);	 
    }
    //printf("%d\n", length);
    //printf("\n");
    #endif

    int k = i_position;
    for(; k<p_list->listLen; k++)
    {
	int temp = p_list->arr[k+1];
	p_list->arr[k+1] = p_list->arr[k]; 
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
