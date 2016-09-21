#ifndef _BOOK_M_S_H_
#define	_BOOK_M_S_H_ 
//_BOOK_M_S_H_避免同一工程多次调用头文件，导致头文件内函数声明，变量声明等重复定义

#define NAME_LEN 30
#define BOOK_AMOUNT 5
#define MENU_LEN 10
/*因为上面的语句调用了scanf函数，会在缓存中留下数据，所以add函数调用结束后，会
  影响main函数gets的使用*/
//FLUSH清空缓存，以防止main函数的gets函数从缓存中获取上一次的输入缓存
#define FLUSH                                         \
    do{                                               \
	int c;                                          \
	while( ( c = getchar() ) != '\n' && c != EOF )  \
	;                                             \
    } while( 0 )


extern int curAmount;

typedef struct bookInfo
{
    char name[NAME_LEN];
    int price;
    int publish;
}Book[BOOK_AMOUNT], *pBook;

void welcomeScreen();
void showMenu();
void addBook(Book book);
void deleteBook(pBook book, int id);	//链表比较方便，这个功能先不做
void modifyBookInfo(pBook book, int id);
void inquireBookInfo(pBook book, char *item); 
void showBookInfo(Book book, int id);


#endif 

