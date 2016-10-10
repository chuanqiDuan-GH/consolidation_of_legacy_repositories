#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

enum eFeedback
{
    ERR_INFO,
    OK_INFO
};

typedef struct l_stack
{
    int value;
    struct l_stack *pPrev;
    struct l-stack *pnext;
}Stack, *pStack;


#endif	//_LINKSTACK_H_
