#include <string.h>
#include "lMS.h"

int main()
{

    Book b;
    //pBook pb = b;

    memset(b, 0, sizeof(b));
    addBook(b);
    showBookInfo(b, 0);

}

