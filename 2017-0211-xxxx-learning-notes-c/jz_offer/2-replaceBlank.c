/********************************************************
 *   Copyright (C) 2017 All rights reserved.
 *   
 *   Filename:2-replaceBlank.c
 *   Author  :Chuanqi.Duan
 *   Email   :chuanqiduan@foxmail.com
 *   Date    :2017-01-07 23:14
 *   Describe:剑指offer-Q4-替换空格
 ********************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ReplaceBlank(char *str, int len);

int main()
{
    char *str = (char *)malloc(16*sizeof(char));
    strcpy(str, "we are happy");
    int len = strlen(str);
    ReplaceBlank(str, len);
    printf("%s\n", str);
    free(str);
}

void ReplaceBlank(char *str, int len)
{
    if(NULL == str)
	return;

    int blkNum = 0;
    int i = 0;

    while(str[i] != '\0')
    {
	if(str[i++] == ' ') 
	    blkNum++;
    }

    int tmpLen = len + blkNum * 2;
    /*扩容*/
    str = realloc(str, (tmpLen+1)*sizeof(char));
    str[tmpLen] = '\0';
    /*将原有末尾移动到新的末尾,从后向前一次替换,只需遍历一趟即可完成替换*/
    while(len != tmpLen)
    {
	if((str[len]) == ' ')
	{
	    str[tmpLen--] = '0';
	    str[tmpLen--] = '2';
	    str[tmpLen--] = '%';
	    len--;
	}
	else
	    str[tmpLen--] = str[len--];
    } 
}
