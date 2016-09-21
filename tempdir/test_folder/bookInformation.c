#include<stdio.h>
#define NAME_LEN 30

typedef struct bookInfo
{
    char name[NAME_LEN];
    int publish;
}Book, *pBook;

void showBookInfo(pBook book);
void inputBookInfo(pBook book);

int main()
{

    Book b1;
    pBook pb = &b1;
    inputBookInfo(pb);
    showBookInfo(pb);

}

void inputBookInfo(pBook book)
{
    //scanf()遇到空格会返回，所以不能输入有空格的的字符串
    //scanf("%s", book->name);
    //get()函数会有潜在越界问题，不推荐使用
    //fgets()函数自带换行
    fgets(book->name, NAME_LEN, stdin);
    scanf("%d", &book->publish);

}

void showBookInfo(pBook book)
{
    printf("%s", book->name);
    printf("%d\n", book->publish);
}
