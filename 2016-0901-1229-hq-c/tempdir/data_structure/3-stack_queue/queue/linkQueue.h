#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_

enum eFeedback
{
    ERR_INFO = -1,
    OK_INFO
};

typedef struct l_queue
{
    int value;
    struct l_queue *pPrev;
    struct l_queue *pNext;
}Queue, *pQueue;

pQueue createLikQueue();
int insertLikQueue(pQueue node, int i_value);
int deleteLikQueue(pQueue node);
void showLikQueue(pQueue node);

#endif	//_LINKQUEUE_H_
