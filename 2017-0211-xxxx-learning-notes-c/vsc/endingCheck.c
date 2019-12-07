/**
大小端检查
*/

#include <stdio.h> 

union data 
{
    char a;
    int b;
}d1;

void func ()
{
    d1.b = 0x12345678;
    printf("%#x\n", d1.a);
}

void main ()
{
    func();
}