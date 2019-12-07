/***************************************************
  给出年、月、日，计算该日是该年的第几天。（考虑闰年）
 ***************************************************/
#include<stdio.h>


int main()
{

    printf("please enter the current date in the form of (year) (month) and (day)\n");
    int year = 0;
    int month = 0;
    int day = 0;
    int sum = 0; 
    scanf("%d%d%d", &year, &month, &day);
    printf("%d %d %d\n", year, month, day);

    switch(month)
    {
	case 1:
	    sum = 0;
	    break;
	case 2:
	    sum = 31;
	    break;
	case 3:
	    sum = 59;
	    break;
	case 4:
	    sum = 90;
	    break;
	case 5:
	    sum = 120;
	    break;
	case 6:
	    sum = 151;
	    break;
	case 7:
	    sum = 181;
	    break;
	    case 8:
	    sum = 212;
	    break;
	case 9:
	    sum = 243;
	    break;
	case 10:
	    sum = 273;
	    break;
	case 11:
	    sum = 303;
	    break;
	case 12:
	    sum = 333;
	    break;
    }
    if(year % 4 == 0 && month > 2)
	sum += day + 1;
    else
	sum += day;

    printf("%d\n", sum);


    return 0;
}
