#include<stdio.h>
#define ONEHOUR 60

int main()
{
    int min;
    int hour = 0;
    scanf("%d", &min);

    hour = (min/ONEHOUR);
    min %= ONEHOUR;
    
    if(hour < 1)
    {
	printf("%dmins\n", min);
    
    }
    else if(hour == 1)
    {
 	printf("%dhour %dmins\n", hour, min);   
    }
    else
    {
 	printf("%dhours %dmins\n", hour, min);   
    }

}
