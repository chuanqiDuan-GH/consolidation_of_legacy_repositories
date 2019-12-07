#include <stdio.h>

int plusFun(int n1, int n2)
{
    return n1 + n2;
}

int minsFun(int n1, int n2)
{
    return n1 - n2;
}

int run(int a, int b, int (*pFun)(int, int))
{
    return (*pFun)(a, b);
}

int main()
{
    int (*pFun)(int, int);
    //pFun = plusFun;
    pFun = minsFun;
    
    printf("%d\n", run(2, 1, pFun));
    return 0;
}