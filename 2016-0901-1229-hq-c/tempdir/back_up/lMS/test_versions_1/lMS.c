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
	fgets(book->name, NAME_LEN, stdin);

	//scanf("%s", book->name);
	scanf("%d", &(book->price));
	scanf("%d", &(book->publish));
	book++;
	curAmount++;
    }
    
    //to do
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
     
    printf("%s", (book+id)->name);
    printf("%d\n", (book+id)->price);
    printf("%d\n", (book+id)->publish);
    //to do
}

