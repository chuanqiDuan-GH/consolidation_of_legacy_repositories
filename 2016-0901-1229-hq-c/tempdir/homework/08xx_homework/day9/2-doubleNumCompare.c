/*******************************************************
  设计函数min(x,y)，返回两个double数值中较小的数值
 *******************************************************/
#include<stdio.h>
#include<math.h>
#define EPSILON 0.000000
//#define COMPARE
#define SIZE

double min(double x, double y);

int main()
{

    double num1 = 1.000001;
    double num2 = 1.000002;

    double result = min(num1, num2);
    printf("%lf\n", result);
    return 0;
}

double min(double num1, double num2)
{
#ifdef COMPARE 
    if(fabs(num1 - num2) == EPSILON)
	return 0; 
    else
	return (num1 - num2);	
#endif

#ifdef SIZE 
    if((num1 -num2) > EPSILON)
	return num2;	
    else
	return num1;
#endif
}
