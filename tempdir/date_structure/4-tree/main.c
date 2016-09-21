#include "tree.h"

int main()
{

    int arr[8] = {66,77,99,55,22,56,11,100};
    pTree root = createTree(arr, 8);
    levelOrder(root);
    inOrder(root);
    printf("\n");

    return 0;
}
