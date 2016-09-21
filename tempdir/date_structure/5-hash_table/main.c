#include "hash.h"

int main()
{
   pHash table = createHash(); 
   insertNode(table, 10);
   insertNode(table, 20);
   insertNode(table, 1);
   insertNode(table, 21);
   insertNode(table, 32);

   showTableNode(table);


    return 0;
}
