#include<stdio.h>

union dt
{
   int a;
   char b;
   float c;
};

//此处的*data即作为一个传入参数 同时又作为一个传出参数
void fun(union dt *data)
{
    data->a = 10;
    printf("%d\n", data->a);
}

int main()
{
    union dt DT;
    //定义一个指向union数据类型的指针 
    union dt *p;
    
    //将一个union类型的数据的地址赋值给p，即一个指向union的指针
    p = &DT;

    DT.a = 5;

    fun(p);

    return 0;
}
