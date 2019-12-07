/*************************************************************
 题目:
 一只青蛙一次可以跳上1级台阶,也可以跳上2级.
 求该青蛙跳上一个n级的台阶总共有多少种跳法. 
 分析:
 这个题类似fabonacci数列的思路.
*************************************************************/
#include <stdio.h>

int jumpFloor(int num)
{
#ifdef C1
//自底向上,迭代法
    printf("C1\n");

    int firStep = 1;
    int secStep = 0;
    int idx = 1;
    int count = 0;

    for(; idx<=num; idx++)
    {
        count = firStep + secStep;
        secStep = firStep;
        firStep = count;
    }
    return count;
#else
//自顶向下,递归法
    if(num <= 0)
        return -1;
    if(num == 1)
        return 1;
    if(num == 2)
        return 2;

    return jumpFloor(num-1)+jumpFloor(num-2);
#endif
}


int main()
{
    printf("%d\n", jumpFloor(6));
    return 0;
}