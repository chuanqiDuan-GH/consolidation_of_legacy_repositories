#include <stdio.h>

void func ()
{
    //有效数字为6~7位,所以打印为12345.67xxxx,float小数点后默认6位小数
    float f1 = 12345.671;
    printf("%f\n", f1);
}


void main ()
{
    func();
}