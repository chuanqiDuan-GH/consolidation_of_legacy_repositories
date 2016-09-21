#include <stdio.h>
#include "lMS.h"

int curAmount = 0;

void showMenu()
{
    //to do
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
	//book++;
	curAmount++;
    FLUSH;
    }
    else
	printf("can't get more data\n");

    /*因为上面的语句调用了scanf函数，会在缓存中留下数据，所以add函数调用结束后，会
      影响main函数gets的使用*/
    //FLUSH清空缓存，以防止main函数的gets函数从缓存中获取上一次的输入缓存
    //to finsh
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
    //printf("%d\n", (book)->price);
    //printf("%d\n", (book)->publish);
    }
    }
    else
    {
	printf("no data\n"); 
    }
    //to finsh
}

