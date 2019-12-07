//结构体大小
#include <stdio.h>

struct data
{
    int a;
    char b;
    float c;
    char d[10];
}d1;

struct data1
{
    int a;
    int b;
    int c;
}arr[2] = {10, 3, 21, 7, 29, 1};

struct data2
{
    int num;
    char str[10];
}s[3] = {{1, "Beijing"}, {2, "Shanghai"}, {3, "Guangzhou"}};

void func ()
{
    printf("%u\n", sizeof(d1));
}

void func1 ()
{
    printf("%d\n", arr[0].b * arr[1].c);
}

void func2 ()
{
    struct data2 *p;
    p = s+1;
    printf("%d, %c\n", p->num, (*p).str[1]);
} 

void main ()
{
    func2();
}