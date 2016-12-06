#include <stdio.h>
#include "simpEq.h"

int main()
{
    pList head; 
    char c_len[PLOYLEN];
    int i_len;


    printf("please input the lenght of Polynomial: ");
    gets(c_len);
    i_len = atoi(c_len);

    head = creatNode(head, i_len);
    printf("back\n");
    show(head);


    return 0;
}
