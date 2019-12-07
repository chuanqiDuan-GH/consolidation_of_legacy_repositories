#include <stdio.h>
#include <string.h>
//#include <unistd.h> //sleep函数头文件
#include "lMS.h"
#include "menu.h"

int main()
{

    Book b;
    //之前想适用指针指向这个数组，然后在操作，遇到问题，弃用?
    pBook pb = b;
    char button[MENU_LEN] = {'\0'};
    memset(pb, 0, sizeof(b));

    welcomeScreen();
    showMenu();

    while(1)
    {
	//这里使用fgets函数会导致strcmp判断出问题，未找到原因?
	//fgets(button, MENU_LEN, stdin);
	gets(button);
	if(!strcmp(button, "add"))
	{
	    addBook(b);
	    printf("\n");    
	    //printf("add\n");
	}
	else if(!strcmp(button, "delete"))
	{
	    deleteBook(b);
	    printf("\n");
	    //printf("delete\n");
	}
	else if(!strcmp(button, "inquire"))
	{
	    inquireBookInfo(b);
	    printf("\n");
	    //printf("inquire\n");
	}
	else if(!strcmp(button, "modify"))
	{
	    modifyBookInfo(b);
	    printf("\n");
	    //printf("modify\n");
	}
	else if(!strcmp(button, "show"))
	{
	    showBookInfo(b);
	    printf("\n");
	    //printf("show\n");
	}
	else if(!strcmp(button, "menu"))
	{
	    showMenu();
	    //printf("showmenu\n");
	}
	else if(!strcmp(button, "exit"))
	{
	    printf("CARPE DIME\n");
	    //printf("carpe dime\n");
	    break;	
	}
#if 1
	else
	{
	    printf("worng input\n");	
	    printf("\n");
	}
#endif
#if 0
	//使用switch语句会有问题，且无法使用字符串当作判断条件，故放弃
	switch(button)
	{
	    case '1':
		printf("add\n");
		addBook(pb);
		break;
	    case '2':
		printf("delete\n");
		//delete()
		break;
	    case '3':
		printf("inquire\n");
		break;
	    case '4':
		printf("modify\n");
		break;
	    case '5':
		showBookInfo(pb, curAmount-1);
		printf("show\n");
		break;
	    case '0':
		printf("showmenu\n");
		break;
	}

#endif
    }

    //sleep(3);
}

