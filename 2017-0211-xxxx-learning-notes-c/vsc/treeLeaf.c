#include <stdio.h>
#include <stdlib.h>

typedef struct _TreeNode
{
    char chr;
    struct _TreeNode *pLchild, *pRchild;
}TreeNode, *pTreeNode;

pTreeNode CreateNode (char chr)
{
    if(!(chr >= 'a' && chr <= 'z'))
        return NULL;
    
    pTreeNode newNode = (pTreeNode)malloc(sizeof(TreeNode));
    newNode->chr = chr;
    newNode->pLchild = newNode->pRchild = NULL;

    return newNode;
}

void CountTreeLeaf(pTreeNode root, unsigned int *count)
{
    if(NULL != root)
    {
        if(NULL == root->pLchild && NULL == root->pRchild)
            (*count)++;
        else
        {
            CountTreeLeaf(root->pLchild, count);
            CountTreeLeaf(root->pRchild, count);
        }
    }
}

void ConstructTree (char chr, pTreeNode *node)
{
    if(!(*node))
    {
        *node = (pTreeNode)malloc(sizeof(TreeNode));
        (*node)->chr = chr;
        (*node)->pLchild = (*node)->pRchild = NULL;
        printf("create root\n");
        return;
    }

    pTreeNode tmpNode = *node;
    while(chr && (NULL != tmpNode))
    {
        printf("%c\n", chr);
        if((chr <= (tmpNode)->chr))
        {
            if(!(tmpNode)->pLchild) 
            {
                (tmpNode)->pLchild = CreateNode(chr);
                return;
            }
            else
            {
                tmpNode = tmpNode->pLchild;
                continue;
            }
        }
        else
        {
            if(!(tmpNode)->pRchild)
            {
                (tmpNode)->pRchild = CreateNode(chr);
                return;
            }
            else
            {
                tmpNode = tmpNode->pRchild;
                continue;
            }
        }
    }
}

int main()
{

    char data[8] = {'e', 'f', 'h', 'g', 'a', 'c', 'b', 'd'};
    pTreeNode root = NULL;
    unsigned int count = 0;
    int i = 0;
    for(; i<8; i++)
    {
        ConstructTree(data[i], &root);
    }
    
    CountTreeLeaf(root, &count);
    printf("count:%d\n", count);
    return 0;
}