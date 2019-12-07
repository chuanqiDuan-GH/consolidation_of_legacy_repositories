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
        //printf("%c\n", chr);
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

pTreeNode ConstructTree2 (char chr, pTreeNode node)
{
    if(!(node))
    {
        node = (pTreeNode)malloc(sizeof(TreeNode));
        node->chr = chr;
        node->pLchild = node->pRchild = NULL;
        printf("create root\n");
        return node;
    }

    pTreeNode tmpNode = node;
    while(chr && (NULL != tmpNode))
    {
        //printf("%c\n", chr);
        if((chr <= (tmpNode)->chr))
        {
            if(!(tmpNode)->pLchild) 
            {
                (tmpNode)->pLchild = CreateNode(chr);
                return node;
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
                return node;
            }
            else
            {
                tmpNode = tmpNode->pRchild;
                continue;
            }
        }
    }
}

//计算二叉树高度
int TreeHign (pTreeNode root)
{
    if(NULL == root)
        return -1;

    //printf("chr:%c\n", root->chr);

    /*
    //方法1    
    int h1 = 0;
    int h2 = 0;

    h1 = TreeHign(root->pLchild);
    h2 = TreeHign(root->pRchild);
    return h1 > h2 ? (h1+1) : (h2+1);
    */    

    //方法2
    return TreeHign(root->pLchild) > TreeHign(root->pRchild) ? ((TreeHign(root->pLchild))+1) : ((TreeHign(root->pRchild))+1);
}

void PreOrder (pTreeNode root)
{
    if(root)
    {
        printf("%c ", root->chr);
        PreOrder(root->pLchild);
        PreOrder(root->pRchild);
    }
}

int main ()
{
    char data[8] = {'e', 'f', 'h', 'g', 'a', 'c', 'b', 'd'};
    int i = 0;
    pTreeNode root = NULL;

    for(i; i<8; i++)
    {
        ConstructTree(data[i], &root);
        //root = ConstructTree2(data[i], root);
    }

    printf("tree hign:%d\n", TreeHign(root));

    PreOrder(root);
    return 0;
}