#ifndef _LINK_H_
#define _LINK_H_

typedef int data_t;
typedef struct LINK
{
    data_t data;
    struct LINK *pNext;
}Link;


#define HEADER 0
#define TAIL -1
typedef enum LINK_OP
{
    LINK_ERR = -1,
    LINK_OK,
    LINK_FIND
}LINK_OP_ENUM;




Link* CreateLink();
void DestroyLink(Link *plink);
Link* CreateLinkNode(data_t data);
int InsertLinkItem(Link *plink,data_t tdata,int Offset);
int DeleteLinkItem(Link *plink,data_t *pdata,int Offset);
void ShowLink(Link *plink);
int UpdateLinkItem(Link *plink,data_t OldData,data_t NewData);
int FindLinkitem(Link *plink,data_t tdata);
#endif /* _LINK_H_ */
