#include <stdio.h>
#include "lMS.h"

int curAmount = 0;

void showMenu()
{
    printf("FUNCTION\t SUMMARY\t\t OPERATION GUIDE\t\n");
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
	scanf("%d", &(book[curAmount].publish));
	curAmount++;
	/*因为上面的语句调用了scanf函数，会在缓存中留下数据，所以add函数调用结束后，会
	  影响main函数gets的使用*/
	//FLUSH清空缓存，以防止main函数的gets函数从缓存中获取上一次的输入缓存
	FLUSH;
    }
    else
    {
	printf("can't get more data\n");
    }
}

void deleteBook(pBook book, int id)
{
    //to do
}

void modfiyBookInfo(pBook book, int id)
{
    //to do
}

void inquireBookInfo(pBook book, char *item)
{
    //to do
}

void showBookInfo(Book book, int id)
{
    if(curAmount != 0)
    {
	for(int i=0; i<id; i++)
	{
	    printf("%s\t %d\t %d\t\n", (book[i]).name, (book[i]).price, (book[i]).publish);
	}
    }
    else
    {
	printf("no data\n"); 
    }
}

