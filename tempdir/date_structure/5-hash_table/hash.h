#ifndef _HASH_H_
#define _HASH_H_

#define TABLE_SIZE 10

typedef struct _Node
{
    int data;
    struct _Node *pNext;

}Node, *pNode;

typedef struct _Hash
{
    pNode pHead[TABLE_SIZE]; 
}Hash, *pHash;

pHash createHash();
int insertNode(pHash table, int i_data);
int deleteNode(pHash table, int d_data);
int destoryTable(pHash table);
void showTableNode(pHash table);

#endif	//_HASH_H_
