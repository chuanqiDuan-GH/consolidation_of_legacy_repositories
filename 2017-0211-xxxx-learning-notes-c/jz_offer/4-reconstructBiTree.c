/********************************************************
*   Copyright (C) 2017 All rights reserved.
*   
*   Filename:4-reconstructBiTree.c
*   Author  :Chuanqi.Duan
*   Email   :chuanqiduan@foxmail.com
*   Date    :2017-01-11 21:51
*   Describe:剑指offer-Q6-重建二叉树
********************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int value;
    struct TreeNode* pLChild;
    struct TreeNode* pRChild;
}Node, *pNode;

/*已知先序中序，输出后序*/
void ReconstructPostorderTree(int *preArr, int *inArr, pNode *root, int len)
{
    if(len == 0)
    {
	root = NULL; 
	return;
    }

    int tmp = preArr[0]; 
    int index = 0;

    while(inArr[index] != tmp)
	index++;    

    /*给根节点分配空间*/
    (*root) = (pNode)malloc(sizeof(Node));
    (*root)->value = inArr[index];
    /*重建左子树*/
    ReconstructPostorderTree(preArr+1, inArr, &((*root)->pLChild), index);
    /*重建右子树*/
    ReconstructPostorderTree(preArr+index+1, inArr+index+1, &((*root)->pRChild), len-index-1);
}

/*已知后序中序，输出先序*/
void ReconstructPreorderTree(int *postArr, int *inArr, pNode *root, int len)
{
    if(len == 0)
    {
	root = NULL; 
	return;
    }

    int tmp = postArr[len-1]; 
    int index = 0;

    while(inArr[index] != tmp)
	index++;    

    /*给根节点分配空间*/
    (*root) = (pNode)malloc(sizeof(Node));
    (*root)->value = inArr[index];
    /*重建左子树*/
    ReconstructPreorderTree(postArr, inArr, &((*root)->pLChild), index);
    /*重建右子树*/
    ReconstructPreorderTree(postArr+index, inArr+index+1, &((*root)->pRChild), len-index-1);

}

/*后序遍历*/
void PostorderPrint(pNode root)
{
    if(NULL != root)
    {
	PostorderPrint(root->pLChild); 
	PostorderPrint(root->pRChild);
	printf("%d ", root->value);
    }
}

/*先序遍历*/
void PreorderPrint(pNode root)
{
    if(NULL != root)
    {
	printf("%d ", root->value);
	PreorderPrint(root->pLChild); 
	PreorderPrint(root->pRChild);
    }
}

int main()
{
    int preArr[8] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inArr[8] = {4, 7, 2, 1, 5, 3, 8, 6};
    int postArr[8] = {7, 4, 2, 5, 8, 6, 3, 1};

    pNode root = NULL;

    ReconstructPostorderTree(preArr, inArr, &root, 8);
    PostorderPrint(root);
    printf("\n");
    
    pNode root1 = NULL;
    ReconstructPreorderTree(postArr, inArr, &root1, 8);
    PreorderPrint(root1);
    printf("\n");

    return 0;
}


