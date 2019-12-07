/***********************************************
字符串倒序存储并输出 
***********************************************/
#include<stdio.h>
#include<string.h>

char *stringReversal(char *str, int len);

int main()
{
    char str[] = {'\0'};
    scanf("%s", str);
    int len = strlen(str);

    char *Reversal;
    Reversal = stringReversal(str, len);
    #if 0
    while(*Reversal)
    {
	printf("%c", *Reversal++); 
    }
    #endif
    puts(Reversal);
	//printf("%s", str); 
    return 0;
}

char *stringReversal(char *str, int len)
{
    char *mark = str;
    #if 1
   for(int i=0; i<len/2; i++)
   {
	char temp = '0'; 
	temp = str[i];
	str[i] = str[len-1-i];
	str[len-1-i] = temp;
   }
   #endif 
    puts(mark);
    puts(str);
    return mark;
    
}
