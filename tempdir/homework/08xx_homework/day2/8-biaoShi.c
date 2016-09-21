//宏定义?
#include<stdio.h>
#define MAX(NUM1, NUM2) (NUM1 > NUM2 ? NUM1 : NUM2) 


int fun(int n1, int n2)
{

}
int main()
{
    int max = MAX(10,20);
    printf("%d\n", max);
    return 0;
}
