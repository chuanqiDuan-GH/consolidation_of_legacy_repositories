#ifndef _SEQUENCELIST_H_
#define _SEQUENCELIST_H_

#define LIST_AMOUNT 10

enum eFeedback
{
    ERR_INFO = -1,
    OK_INFO
};

typedef struct sList
{
    int arr[LIST_AMOUNT];
    int listLen; 
}List, *pList;

pList creatList();
int insertList(pList p_list, int i_position, int value);
int deleteList(pList p_list, int d_position);
int modifyList(pList p_list, int m_position, int value);
void showList(pList p_list);

#endif
