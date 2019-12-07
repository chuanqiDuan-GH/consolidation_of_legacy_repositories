#ifndef __SIMPEQ_H__
#define __SIMPEQ_H__

#define PLOYLEN 4
#define FILEN	8


typedef struct si_list 
{
    int factor;
    int index;
    struct si_list *pNext;
}List,  *pList;

pList creatNode(pList head, int len);
void show(pList head);


#endif	//__SIMPEQ_H__
