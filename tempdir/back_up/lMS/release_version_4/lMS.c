#include <stdio.h>
#include <string.h>
#include "lMS.h"

int curAmount = 0;

void welcomeScreen()
{
    printf(" -------------------------------\n");
    printf("|welcome to use cqd's product :p|\n");
    printf(" -------------------------------\n");

    printf(" _     _______  _____ \n");
    printf("| |   |  _ _  ||  ___|\n");
    printf("| |   | | | | ||_|___ \n");
    printf("| |__ | | | | | ___|_|\n");
    printf("|____||_| | |_||_____|\n\n");

}

void showMenu()
{
    printf("FUNCTION->\t SUMMARY->\t\t OPERATION GUIDE->\t\n");
    printf("\n");
    printf("showMenu\t show menu info\t\t input 'menu'\t\n");
    printf("addBook\t\t add book\t\t input 'add'\t\n");
    printf("deleteBook\t delete book\t\t input 'delete'\t\n");
    printf("modifyBookInfo\t modify book info\t input 'modify'\t\n");
    printf("inquireBookInfo\t inquire book info\t input 'inquire'\t\n");
    printf("showBookInfo\t display all book info\t input 'show'\t\n");
    printf("exit\t\t exit the system\t input 'exit'\t\n");
    printf("\n");
}


void addBook(Book book)
{
    //scanf()遇到空格会返回，所以不能输入有空格的的字符串
    //scanf("%s", book->name);
    //get()函数会有潜在越界问题，不推荐使用
    //fgets()函数自带换行
    if(curAmount < BOOK_AMOUNT)
    {
	//printf("%s\n", __FUNCTION__);
	//fgets(book->name, NAME_LEN, stdin);
	scanf("%s", book[curAmount].name);
	scanf("%d", &(book[curAmount].price));
	scanf("%d", &(book[curAmount].pdate));
	curAmount++;
	/*因为上面的语句调用了scanf函数，会在缓存中留下数据，所以add函数调用结束后，会
	  影响main函数gets的使用*/
	FLUSH;
    }
    else
    {
	printf("can't get more data\n");
    }
}

void deleteBook(Book book)
{
    unsigned int id = 0; 
    printf("please input the number of book which you wanna delete\n");
    scanf("%d", &id); 
    //printf("%d\n", curAmount);
    //printf("%d\n", id);
    if(id-1 < (curAmount) && id != 0)
    {
	strcpy(book[id-1].name, "\0");
	book[id-1].price = 0;
	book[id-1].pdate = 0;
    }
    else
    {
	printf("no data to delete\n"); 
    }
    //gets函数之前有scanf函数使用，需要flush
    FLUSH;

}

void modifyBookInfo(Book book)
{
    unsigned int id = 0; 
    printf("please input the number of book which you wanna modify\n");
    scanf("%d", &id); 
    //printf("%d\n", curAmount);
    //printf("%d\n", id);
    if(id-1 < (curAmount) && id != 0)
    {
	scanf("%s", book[id-1].name);
	scanf("%d", &(book[id-1].price));
	scanf("%d", &(book[id-1].pdate));
	FLUSH;
    }
    else
    {
	printf("no data to modify\n"); 
    }
    //gets函数之前有scanf函数使用，需要flush
    FLUSH;
}

void inquireBookInfo(Book book)
{
    char item[10] = {'\0'};
    if(item == NULL)
    {
	return; 
    }
    printf("please input options, such as the 'name','price' or 'pdate', you can query relevant info.\n");
    gets(item);
    if(curAmount != 0)
    {
	if(!strcmp(item, "name"))
	{
	    for(int i=0; i<curAmount; i++)
	    {
		printf(">>>%s<<<\n", (book[i]).name);
	    }
	}
	else if(!strcmp(item, "price"))
	{
	    for(int i=0; i<curAmount; i++)
	    {
		printf(">>>%d<<<\n", (book[i]).price);
	    }
	    //printf("price\n");
	}
	else if(!strcmp(item, "pdate"))
	{
	    for(int i=0; i<curAmount; i++)
	    {
		printf(">>>%d<<<\n", (book[i]).pdate);
	    }
	    //printf("pdate\n");
	}
	else
	{
	    printf("option does't exist\n"); 
	}

    }
    else
    {
	printf("no data\n"); 
    }
    //调用gets函数不用清缓存?
    //FLUSH;

}

void showBookInfo(Book book)
{
    if(curAmount != 0)
    {
	printf("NAME->\t PRICE->\t PDATE->\t\n");
	for(int i=0; i<curAmount; i++)
	{
	    printf("%s\t %d\t %d\t\n", (book[i]).name, (book[i]).price, (book[i]).pdate);
	}
    }
    else
    {
	printf("no data\n"); 
    }
}

