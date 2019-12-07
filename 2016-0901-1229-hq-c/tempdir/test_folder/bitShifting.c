#include<stdio.h>

int fun(unsigned int num ,unsigned int ji);

int main()
{
#if 0
    unsigned char c1 = 7;

    //按位移动，少的补0
    printf("%u\n",c1 >> 2);
    printf("%u\n",c1 << 2);
    //按位，1变0，0变1
    printf("%u\n",~c1);
    //在同一位上，相同为0，不同为1
    printf("%u\n",c1 ^ 6);
    printf("%u\n",c1 ^ 7);
    printf("%u\n",c1 ^ 8);
    //在同一位上，都是1才是1，否则是0
    printf("%u\n",c1 & 6);
    printf("%u\n",c1 & 7);
    printf("%u\n",c1 & 8);
    //在同一位上，都是0才是0，否则是1
    printf("%u\n",c1 | 6);
    printf("%u\n",c1 | 7);
    printf("%u\n",c1 | 8);
#endif
    printf("%d\n",fun(12345,5));
    printf("%d\n",fun(12345,3));

    return 0;
}

//345325   10
int fun(unsigned int num ,unsigned int ji)
{
    return num>>ji-1&1;
}
