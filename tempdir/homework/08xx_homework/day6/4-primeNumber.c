#include<stdio.h>
#include<math.h>

int main()
{

    int num = 101;
    int ceiling = sqrt(num);
    int flag;
    //质数的判断是思路：一个数若是能被整除，整除该数字的两个数一定分布在该数字的平方根两侧
    //例如100，开平方为10，整除100的数：2*50 4*25 5*25 ，这些组合都分布在10的两侧
    //通过以上方法可以降低预算，简化步骤

    while(num < 200)
    {
    //这个for循环就只用让当前数字取余从2至(开根得出的那个数)为止的所有数字，
    //如果等于0，说明可以被某数字整除，跳过这个数，定义一个flag，被改变说明被break了，
    //在循环外面判断flag来确定是否要打印这个数字，即得出质数
	for(int i=2; i<ceiling; i++)	
	{
	    flag = 0;
	    if(num%i == 0)
	    {
		flag = 1;
		break; 
	    }
	}
	if(flag == 0)
	{
	    printf("%d ", num);

	}
	num++;
    }
}


