#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkList.h"


int main(int argc, char *argv[])
{
    pNode node = creatLink();

    char op[OP_SIZE] = {'0'};
    while(1)
    {
	gets(op); 

	if(strstr(op, "insert"))
	{
	    strtok(op, " ");
	    int value = atoi(strtok(NULL, " "));
	    int i_index = atoi(strtok(NULL, " "));
	    printf("%d %d\n", value, i_index);
	    if(ERR_INFO == insertLinkNode(node, value, i_index))
	    {
		printf("over range\n"); 
	    }

	}
	else if(strstr(op, "delete"))
	{	
	    strtok(op, " ");
	    int d_index = atoi(strtok(NULL, " "));
	    printf("%d\n", d_index);
	    deleteLinkNode(node, d_index);	
	}
	else if(!strcmp(op, "modify"))
	{
	    //to do	
	}

	else if(!strcmp(op, "show"))
	{
	    showLink(node);
	}
	else if(!strcmp(op, "sort"))
	{
	    selectSort(node);
	    //bubbleSort(node);
	    //bubbleSort2(node);
	}
	else if(!strcmp(op, "quit"))
	{
	    free(node);
	    node = NULL;
	    break;
	}
	else
	{
	    printf("T.T\n");	
	}
    }

    return 0;
}
