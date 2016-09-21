#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Link.h"


Link* CreateLink()
{
    Link *plink = (Link*)malloc(sizeof(Link));
    if ( NULL == plink )
    {
        return plink;
    }
    memset(plink,0,sizeof(Link));
    return plink;
}
void DestroyLink(Link *plink)
{
    if ( NULL == plink )
    {
        return;
    }
    Link *pTmp = NULL;
    Link *pDel = NULL;
    pDel = plink->pNext;
    while ( NULL != pDel )
    {
        pTmp = pDel->pNext;
        free(pDel);
        pDel = pTmp;
    }
    free(plink);
    plink = NULL;
    pTmp = NULL;
    pDel = NULL;
    return;
}

Link* CreateLinkNode(data_t data)
{
    Link *pNode = (Link*)malloc(sizeof(Link));
    if ( NULL == pNode )
    {
        return pNode;
    }
    memset(pNode,0,sizeof(Link));
    pNode->data = data;
    return pNode;
}


int InsertLinkItem(Link *plink,data_t tdata,int Offset)
{
    if ( NULL == plink )
    {
        return;
    }
    Link *pNode = CreateLinkNode(tdata);
    Link *pTmp = plink;
    if ( NULL == pNode )
    {
        return LINK_ERR;
    }
    switch ( Offset )
    {
        case HEADER:
            pNode->pNext = plink->pNext;
            plink->pNext = pNode;
            break;
        case TAIL:
            while ( NULL != pTmp->pNext)
            {
                pTmp = pTmp->pNext;
            }
            pTmp->pNext = pNode;
            pNode->pNext = NULL;
            break;
        default:
            while ( Offset--)
            {
                if ( NULL != pTmp->pNext)
                {
                    pTmp = pTmp->pNext;
                }

            }
            pNode->pNext = pTmp->pNext;
            pTmp->pNext = pNode;
    }

    return LINK_OK;
}
int DeleteLinkItem(Link *plink,data_t *pdata,int Offset)
{
    if ( (NULL == plink) || (NULL == pdata) || (NULL == plink->pNext) )
    {
        return LINK_ERR;
    }
    Link *pDel = NULL;
    Link *pTmp = plink;
    switch ( Offset )
    {
        case HEADER:
            pDel = plink->pNext;
            plink->pNext = pDel->pNext;
            *pdata = pDel->data;
            free(pDel);
            pDel = NULL;
            break;
        case TAIL:
            while ( NULL != pTmp->pNext->pNext)
            {
                pTmp = pTmp->pNext;
            }
            pDel = pTmp->pNext;
            pTmp->pNext = NULL;
            *pdata = pDel->data;
            free(pDel);
            pDel = NULL;
            break;
        default:
            while ( Offset--)
            {
                if ( NULL != pTmp->pNext)
                {
                    pTmp = pTmp->pNext;
                }
            }
            pDel = pTmp->pNext;
            if ( NULL != pDel)
            {
                pTmp->pNext = pDel->pNext;
                *pdata = pDel->data;
                free(pDel);
                pDel = NULL;
            }

    }
    return LINK_OK;
}





void ShowLink(Link *plink)
{
    if ( NULL == plink )
    {
        return;
    }
    Link *pNode = plink->pNext;
    while ( NULL != pNode)
    {
        printf("%4d",pNode->data);
        pNode = pNode->pNext;
    }
    printf("\n");
}


int UpdateLinkItem(Link *plink,data_t OldData,data_t NewData)
{
    if ( NULL == plink )
    {
        return LINK_ERR;
    }
    Link *pTmp = plink->pNext;
    while ( NULL != pTmp)
    {
        if ( OldData == pTmp->data)
        {
            pTmp->data = NewData;
        }
        pTmp = pTmp->pNext;
    }
    return LINK_OK;
}

int FindLinkitem(Link *plink,data_t tdata)
{
    if(NULL == plink )
    {
        return LINK_ERR;
    }
    Link *pTmp = plink->pNext;
    while (NULL != pTmp)
    {
       if(pTmp->data == tdata)
       {
            printf("%3d",pTmp->data);
            return LINK_FIND;
       }
       pTmp =pTmp->pNext;
    }
    return LINK_OK;
}








