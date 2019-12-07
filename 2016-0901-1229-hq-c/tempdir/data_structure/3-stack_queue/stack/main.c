#include "sequenceStack.h"


int main()
{
#ifdef _SEQUENCESTACK_H_
    pStack node = createSeqStack();
    insertSeqStack(node, 1);
    insertSeqStack(node, 2);
    insertSeqStack(node, 3);
    insertSeqStack(node, 4);
    showSeqStack(node);

    deleteSeqStack(node);
    showSeqStack(node);
#endif

    return 0;
}
