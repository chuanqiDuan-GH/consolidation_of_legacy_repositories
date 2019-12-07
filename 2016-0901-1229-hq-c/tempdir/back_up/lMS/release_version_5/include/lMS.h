#ifndef _BOOK_M_S_H_
#define	_BOOK_M_S_H_ 
//_BOOK_M_S_H_避免同一工程多次调用头文件，导致头文件内函数声明，变量声明等重复定义

#define NAME_LEN 30 //书籍名字长度
#define BOOK_AMOUNT 5	//书籍数量上限
#define MENU_LEN 10 //菜单选项名字长度
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
    int pdate;
}Book[BOOK_AMOUNT], *pBook;

void addBook(Book book);
void deleteBook(Book book);	//链表比较方便，这个功能先不做
void modifyBookInfo(Book book);
void inquireBookInfo(Book book); 
void showBookInfo(Book book);


#endif 

