#ifndef _BOOK_M_S_H_
#define	_BOOK_M_S_H_ 
//_BOOK_M_S_H_避免同一工程多次调用头文件，导致头文件内函数声明，变量声明等重复定义

#define NAME_LEN 30
#define BOOK_AMOUNT 5

extern int curAmount;

typedef struct bookInfo
{
    char name[NAME_LEN];
    int price;
    int publish;
}Book[BOOK_AMOUNT], *pBook;

void showMenu();
void addBook(Book book);
void deleteBook(pBook book, int id);	//链表比较方便，这个功能先不做
void modifyBookInfo(pBook book, int id);
void inquireBookInfo(pBook book, char *item); 
void showBookInfo(Book book, int id);


#endif 

