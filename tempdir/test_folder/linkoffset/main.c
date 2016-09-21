#include<stdio.h>
#include"Link.h"

int main()
{
    Link *phead = CreateLink();
    if ( NULL == phead)
    {
        return -1;
    }
    int i,ret;
    for ( i = 0 ; i < 9 ; i++ )
    {
        ret = InsertLinkItem(phead, i,HEADER);
        if ( LINK_ERR == ret)
        {
            break;
        }
    }
    ShowLink(phead);
    int num = 0;
    ret = DeleteLinkItem(phead, &num,TAIL);
    printf("the deleted num is %d,ret=%d\n",num,ret);
    InsertLinkItem(phead, 88,TAIL);
    ShowLink(phead);
    DeleteLinkItem(phead, &num,HEADER);
    ShowLink(phead);
    InsertLinkItem(phead, 99,4);
    ShowLink(phead);
    DeleteLinkItem(phead, &num,3);
    ShowLink(phead);
    UpdateLinkItem(phead,5,7);
    ShowLink(phead);

    ret=FindLinkitem(phead,3);
    if(LINK_FIND == ret)
    {
        printf("FIND\n");
    }
    else
        printf("NO FIND");
    DestroyLink(phead);
    phead = NULL;
    return 0;

}
