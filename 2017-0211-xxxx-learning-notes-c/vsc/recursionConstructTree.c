#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TreeNode
{
    char chr;
    struct _TreeNode *pLchild, *pRchild;
} TreeNode, *pTreeNode;


pTreeNode RecursionTree(char *data, pTreeNode root, int len)
{
    if (NULL == data)
        return NULL;

    static int idx = 0;

    if (0 == idx)
    {
        root = (pTreeNode)malloc(sizeof(TreeNode));
        root->chr = data[idx++];
        root->pLchild = NULL;
        root->pRchild = NULL;
        printf("create root\n");
        //这里要特别注意,如果28行的递归判断放到这个递归上面,那么将会导致漏判断这里,会造成栈溢出
        RecursionTree(data, root, len);
    }

    if (len == idx)
        return root;

    pTreeNode tmpNode = root;
    int oldIdx = idx;
    while (1)
    {
        if (data[idx] <= tmpNode->chr)
        {
            if (NULL == tmpNode->pLchild)
            {
                pTreeNode node = (pTreeNode)malloc(sizeof(TreeNode));
                node->chr = data[idx++];
                node->pLchild = NULL;
                node->pRchild = NULL;
                tmpNode->pLchild = node;
                break;
            }
            else
            {
                tmpNode = tmpNode->pLchild;
                continue;
            }
        }
        else
        {
            if (NULL == tmpNode->pRchild)
            {
                pTreeNode node = (pTreeNode)malloc(sizeof(TreeNode));
                node->chr = data[idx++];
                node->pLchild = NULL;
                node->pRchild = NULL;
                tmpNode->pRchild = node;
                break;
            }
            else
            {
                tmpNode = tmpNode->pRchild;
                continue;
            }
        }
    }
    RecursionTree(data, root, len);
}

void PreOrder(pTreeNode root)
{
    if (root)
    {
        printf("%c ", root->chr);
        PreOrder(root->pLchild);
        PreOrder(root->pRchild);
    }
}

int main()
{
    char data[8] = {'e', 'f', 'h', 'g', 'a', 'c', 'b', 'd'};
    int len = strlen(data);
    pTreeNode root = NULL;
    root = RecursionTree(data, root, len);
    PreOrder(root);
    return 0;
}
