#ifndef _SEQUENCESTACK_H_
#define _SEQUENCESTACK_H_

#define A_SIZE 10

enum eFeedback
{
    ERR_INFO = -1,
    OK_INFO
};

typedef struct s_stack
{
    int arr[A_SIZE];
    int a_len;
}Stack, *pStack;

pStack createSeqStack();
int insertSeqStack(pStack node, int i_value);
int deleteSeqStack(pStack node);
void showSeqStack(pStack node);

#endif	//_SEQUENCESTACK_H_
