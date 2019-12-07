#include<stdio.h>

void transform(char *str);
void findCharNum(char *str);

int main()
{
    char str[100] = "0"; 
    char *p = str;  
    int i = 0;

    gets(p);
    transform(p);
    //puts(p);
    int *pp = findCharNum(p);
}

//转换大小写，大写全部转换成小写
void transform(char *str)
{
    while(*str != '\0')
    {
	if(*str >= 'A' && *str <= 'Z')
	{
	    *str += 32;
	}
	str++;
    }
}

//找到对应字符的个数
void findCharNum(char *str)
{
    char cmp[38] = "0";
    int num[37] = {0};
    int *p = num;
    int i = 0;
    int j = 0;
    int k =0;

//建立一个对比字符数组，里面包含所有要进行个数筛选的字符
    for(i=0; i<26; i++)
    {
	cmp[i] = 'a' + i; 
    }
    cmp[i++] = ' ';
    for(; i<37; i++)
    {
	cmp[i] = '0' + j; 
	j++;
    }
    cmp[++i] = '\0';
    //puts(cmp);
   
//对比查找，找出字符串中字符个数
    while(*str != '\0')
    {
	for(k=0; k<38; k++)
	{
	    if(cmp[k] == *str)
	    {
		num[k] += 1;	
		//printf("%c=%d\n", cmp[k], num[k]);	
	    }
	}
	str++;
	//printf("%c=%d\n", cmp[k], num[k]);
    }

//打印
    int m = 0;
    while(m < 36)
    {
	printf("%c=%d\n", cmp[m], num[m]); 
	m++;
    }
}
