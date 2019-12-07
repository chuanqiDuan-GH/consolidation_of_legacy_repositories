//字符大小写转化
#include<stdio.h>

int main()
{
    char inputCh;
    char ExCh;
    
    
    inputCh = getchar();
    //printf("%c\n", inputCh);
    if(inputCh >= 'a' && inputCh <= 'z')
    {
	inputCh -= 32; 
    }
    else if(inputCh >= 'A' && inputCh <= 'Z')
    {
	inputCh += 32; 
    }
    printf("%c\n", inputCh);
    
    return 0;
}
