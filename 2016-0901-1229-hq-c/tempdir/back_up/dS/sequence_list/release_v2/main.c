#include <stdio.h>
#include <stdlib.h>
#include "sequenceList.h"

//定义成全局变量以便多次调用insert函数，length用于长期记录arr空间大小
int length = 10;
int main()
{
    pList list = creatList(); 
   
    int i = 0;
    int j = 20;
    
    for( ; i<20; i++)
    {
	insertList(list, i, i);
    }
    showList(list);
    for( ; j<40; j++)
    {
	insertList(list, j, j);
    }
    showList(list);
    free(list->arr);
    list->arr = NULL;
    free(list);
    list = NULL;
    return 0;
}
