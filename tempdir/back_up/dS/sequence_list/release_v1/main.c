#include "sequenceList.h"


int main()
{
    pList list = creatList(); 
   
    int i = 0;
    for( ; i<9; i++)
    {
	insertList(list, i, i);
    }
    showList(list);
    return 0;
}
