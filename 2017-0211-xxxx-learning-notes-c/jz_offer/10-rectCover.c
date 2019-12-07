/***********************************************************************
题目:
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
分析:
还是fabonacci,思路稍有不同
https://www.nowcoder.com/profile/562667/codeBookDetail?submissionId=1519959
***********************************************************************/
#include <stdio.h>

int rectCover(int number)
{
    if(number <= 0)
        return -1;
    if(number == 1)
        return 1;
    if(number == 2)
        return 2;

    return rectCover(number-1)+rectCover(number-2);
}

int main()
{
    printf("%d\n", rectCover(6));
    return 0;
}