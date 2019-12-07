#include <stdio.h>

typedef unsigned int UI;

struct data
{
    UI a : 2;
    UI b : 4;
    UI : 0;
    UI c : 6;
} d1;

void func ()
{
    d1.a = 3;
    //位域a只有2位,所以最大只能为3,当超过3时,取超过数字二进制的前两位
    //d1.a = 5; //打印出来为1,因为5的二进制为0101,取前两位:01     
    d1.b = 4;
    printf("%d %d\n", d1.a, d1.b);
}

void main ()
{
    func();
}
