/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:6-bracketMatching.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-02-21 17:37
 *   Describe:验证一个括号字符串中的所有括号是否成対匹配
 ********************************************************/
#include <stdio.h>

/*******************************************************
  括号字符串需要成対匹配,举例如下:
  "{([)]}" RULE1:匹配 RULE2:匹配 
  "{()[]}" RULE1:匹配 RULE2:匹配
  "{()[(}" RULE1:不配陪 RULE2:匹配
 ********************************************************/
//gcc 6-bracketMatching.c -D RULE1 括号可以错位匹配
//gcc 6-bracketMatching.c -D RULE2 括号不可一错位匹配

#define STACKSIZE 128

char stack[STACKSIZE] = {'0'};
int top = STACKSIZE;

//入栈
void Push(char symbol)
{
    top--;
    stack[top] = symbol; 
}

//出栈
char Pop()
{
    char tmp = stack[top]; 
    top++;

    return tmp;
}

//匹配检验
int IsMatching(char *str)
{
    if(NULL == str)
	return 0;

    int i = 0;
    char tmp = '0';

    while(str[i])
    {
	if(str[i] == '(' || str[i] == '{' || str[i] == '[')
	    Push(str[i++]); 
	else if(str[i] == ')' || str[i] == '}' || str[i] == ']')
	{
#ifdef RULE1
	    tmp = Pop();	    
	    //printf("%c\n", tmp);
	    i++;
	    if(tmp == '(' || tmp == '{' || tmp == '[')
		continue;
#endif

#ifdef RULE2
	    tmp = Pop();
	    if(str[i] == ')' && tmp == '(')
		continue;
	    else if(str[i] == '}' && tmp == '{')
		continue;
	    else if(str[i] == ']' && tmp == '[')
		continue;
#endif
	    return 0;
	}
    }
    return 1;
}

int main()
{
    char str[10] = "{([)]}";

    if(IsMatching(str))
    {
	printf("match\n");
	goto exit;
    }

    printf("not match\n");

exit:
    return 0;
}
