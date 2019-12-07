#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int main(int argc, char* argv[])
{
    int ret = 0;
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[3]);

    if(argc !=4)
    {
	return -1; 
    }

    if(!strcmp((argv[2]), "+"))
    {
	//op_plus(num1, num2);
	call(op_plus, num1, num2);
    }
    else if(!strcmp((argv[2]), "-"))
    {
	//op_sub(num1, num2);
	call(op_sub, num1, num2);
    }
    else if(!strcmp((argv[2]), "*"))
    {
	//op_plus(num1, num2);
	call(op_mul, num1, num2);
    }
    else if(!strcmp((argv[2]), "/"))
    {
	//op_div(num1, num2);
	call(op_div, num1, num2);
    }

    return 0;
}
