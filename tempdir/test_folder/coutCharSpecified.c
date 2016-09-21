#include<stdio.h>
//输出字符从a开始的10个字符
void main(int argv, char* argc)
{
	int count = 10;
	char character = 'a';
	while(count > 0)
	{
		printf("%c\n", character);	
		character += 1;
		count--;	
	}
}
