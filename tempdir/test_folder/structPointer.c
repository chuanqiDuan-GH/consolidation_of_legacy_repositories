#include<stdio.h>
#if 0
//结构体嵌套枚举
enum SEX { MAN, WOMEN};
struct student
{
    int ID;
    char *name;
    enum SEX sexual;
    int age;
};
#endif
//结构体嵌套枚举另一种方式
struct student
{
    int ID;
    char *name;
    enum SEX{ MAN, WOMEN} sexual;
    int age;
};
//结构体嵌套枚举另一种方式



int main()
{
    struct student s1;
    //结构体指针
    struct student *p;
    p = &s1;
    s1.ID = 1;
    s1.name = "aaa";
    s1.sexual = MAN;
    s1.age = 20;
    printf("%d %s %d %d\n", s1.ID, s1.name, s1.sexual, s1.age); 
    
    //结构体指针引用结构体成员变量
    //下面这两种方式都可以
    p->sexual = WOMEN;
    (*p).age = 25;
    
    printf("%d %s %d %d\n", p->ID, p->name, p->sexual, p->age); 
}
