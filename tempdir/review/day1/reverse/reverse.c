/*实现将任意字符按单词逆置*/
#include <stdio.h>
#include <string.h>

void reverse(char *str, int len)
{
    char *tmp = str;
    int	fore = 0; 
    int after = 0;
    int count = 0;
    int i;
    char swap;

     
    if(NULL == str)
	return; 
     
   while(count < len)
   {
	tmp = str+count;	
	if(*(tmp) == ' ')
	{
	    after = count;	
	    for(i=0; i<(after-fore)/2; i++)
	    {
		swap = *(str+fore+i);
		*(str+fore+i) = *(str+after-1-i);
		*(str+after-1-i) = swap;
	    }
	    fore = after+1;
	}
	count++;
   }
}

void main()
{
    char str[64] = "hello linux i am gonna find some goddamn word in you";
    int len = strlen(str);
    reverse(str, len);
    printf("%s\n", str);
}
