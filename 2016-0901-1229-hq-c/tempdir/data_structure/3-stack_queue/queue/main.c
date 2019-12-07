#include "linkQueue.h"


int main()
{
#ifdef _LINKQUEUE_H_
    pQueue node = createLikQueue();
    insertLikQueue(node, 1);
    insertLikQueue(node, 2);
    insertLikQueue(node, 3);
    insertLikQueue(node, 4);
    showLikQueue(node);

    deleteLikQueue(node);
    showLikQueue(node);
#endif

    return 0;
}
