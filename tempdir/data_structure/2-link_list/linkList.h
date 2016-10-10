#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct l_Node
{
    int value;
    struct l_Node *pNext;
}Node, *pNode;

enum eFeedback
{
   ERR_INFO = -1,
   OK_INFO
};

extern int linkLength;

pNode creatLink();
int insertLinkNode(pNode node, int value, int i_index);
int deleteLinkNode(pNode node, int d_index);
int modifyLinkNode(pNode node, int m_index);
void showLink(pNode node);
void bubbleSort(pNode node);
void bubbleSort2(pNode node); 
void selectSort(pNode node);
void selectSort2(pNode node);


#endif //_LINKLIST_H_
