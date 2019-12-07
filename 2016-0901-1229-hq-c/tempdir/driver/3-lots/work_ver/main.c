#include "common.h"
#include "func.h"

int main()
{ 
    char opts[OPT_LEN] = {'0'};
    srand((unsigned)time(NULL));
    pthread_t tID = 0;

    while(1)
    {	 
	gets(opts);
	if(!strcmp(opts, "g"))
	{
	    if(0 != pthread_create(&tID, NULL, Lots, NULL))
		return -1; 
	    //pthread_join(tID, NULL);
	}
	else if(!strcmp(opts, "q"))
	    break;	
	else
	{
	    printf("wrong input T_T\n");
	    printf("input 'g' for pick if you wanna get some luck guys\n");	
	    printf("input 'q' for quit if you done\n");
	}
	fflush(stdin);
    }
    return 0;
}


