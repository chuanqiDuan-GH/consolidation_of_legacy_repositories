/**********************************************************************
题目:
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
分析:
方法一:用移位运算符
方法二:直接处理二进制的1
**********************************************************************/
#include <stdio.h>

int NumberOfOne(int n)
{
    int count = 0;  
    int flag = 1;

#if 0
    if(n<0)
    {
        n = (-1)*n;
        n = (~n)+1;
        while(0 != flag)
        {
            if(0 != (n & flag))
            {
                count++;
            }
            flag <<= 1;
        }
    } 
    else
#endif
    {
        while(0 != flag)
        {
            if(0 != (n & flag))
            {
                count++;
            }
            flag <<= 1;
        }
    }
    return count;
}

int NumberOfOne2(int n)
{
    int count = 0;

    while(n != 0)
    {
        count++;
        n = (n-1) & n;  //每次相与会清除一个二进制的1
    }
    return count;
}

int main()
{
    printf("%d\n", NumberOfOne(15));
    printf("%d\n", NumberOfOne(-1));
    printf("%d\n", NumberOfOne2(15));
    printf("%d\n", NumberOfOne2(-1));
    return 0;
}