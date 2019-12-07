#include <stdio.h>

void func()
{
    double dn = 12.34;
    double dnn = 12.345;

    if(dn > dnn)
        printf("dn > dnn\n");
    else
        printf("dn < dnn\n");
}

int main()
{
    func();
    return 0;
}