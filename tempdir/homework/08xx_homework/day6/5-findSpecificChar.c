#include<stdio.h>
#include<string.h>

int main()
{
    //键盘输入的字符串达到一定长度就会segment fault
    char inputstr[] = "0";
    int letter = 0;
    int number = 0;
    int blank = 0;
    int otherstuff = 0;
    int i = 0;

    gets(inputstr);
    //puts(inputstr);
    int length = strlen(inputstr);
    printf("%d\n", length);
#if 1 
    while(inputstr[i] != '\0')
    {
	if((inputstr[i] >= 'a' && inputstr[i] <= 'z') || (inputstr[i] >= 'A' && inputstr[i] <= 'Z'))
	{
	    letter++;	
	}
	else if(inputstr[i] >= '0' && inputstr[i] <= '9')
	{
	    number++; 	
	}
	else if(inputstr[i] == ' ')
	{
	    blank++;	
	}
	else
	{
	    otherstuff++;	
	}
	i++;
    }
#endif

    printf("l=%d n=%d b=%d o=%d", letter, number, blank, otherstuff);
    return 0;
}
