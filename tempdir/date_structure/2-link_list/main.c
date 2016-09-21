#include <stdio.h>
#include <stdlib.h>
#include "linkList.h"


int main()
{
    
    pNode node = creatLink();

    insertLinkNode(node, 1, 1);
    insertLinkNode(node, 9, 2);
    insertLinkNode(node, 4, 3);
    insertLinkNode(node, 3, 4);
    insertLinkNode(node, 5, 5);
    insertLinkNode(node, 8, 6);
    showLink(node);

    printf("%d\n", linkLength);
    //deleteLinkNode(node, 1);

    //bubbleSort(node);
    //bubbleSort2(node);
    selectSort(node);
    showLink(node);

    free(node);
    node = NULL;
    return 0;
}
