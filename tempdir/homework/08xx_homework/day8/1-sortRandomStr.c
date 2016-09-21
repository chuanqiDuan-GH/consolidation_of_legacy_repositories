#include<stdio.h>
#include<string.h>
#define STR_AMOUNT 5	//字符串个数
#define STR_LEN    20	//字符串长度

void sort(char *str[STR_LEN], int amount);
void output(char *str[STR_LEN], int amount);
//第一种方法char a[][]; char temp[]; temp作为中间交换变量 
//第二种方法char a[][]; char (*p)[]; a[]接收键盘输入,p = a,p做传参 
//第三种方法char a[][]; char *p[]; p[] = a[]; p[]接收键盘输入，p做传参 
//第四种方法char a[][]; char *p[]; char **pp; p[] = a[]; p[]接收键盘输入,pp = p,pp做传参

int main ()
{
    char str[STR_AMOUNT][STR_LEN]; 
    char *pstr[STR_LEN];
    int i;

    //指针数组指向字符串数组
    for(i=0; i<STR_AMOUNT; i++)
    {	
	pstr[i] = str[i];
    }

    for(i=0; i<STR_AMOUNT; i++)
    {	
	gets(str[i]);
    }

    printf("\n");
    //函数调用
    sort(pstr, STR_AMOUNT);
    output(pstr, STR_AMOUNT);
#if 0
    for(i=0; i<STR_AMOUNT-1; i++)
    {
	k = i;
	for(j=i+1; j<STR_AMOUNT; j++)
	{
	    if(strcmp(str[j], str[k])<0)
		k=j;
	}
	strcpy(t, str[i]); 
	strcpy(str[i], str[k]); 
	strcpy(str[k], t);
    }

    printf("\n");

    for(i=0; i<STR_AMOUNT; i++)
    {

	puts(str[i]);
    }
#endif
    return 0;
}

//排序
void sort(char *str[STR_LEN], int amount)
{
    int i,j,k;
    char temp[STR_LEN];

    for(i=0; i<amount-1; i++)
    {
	k = i;
	for(j=i+1; j<amount; j++)
	{
	    if(strcmp(str[j], str[k]) < 0)
		k = j;
	}
	strcpy(temp, str[i]); 
	strcpy(str[i], str[k]); 
	strcpy(str[k], temp);
    }
}

//输出
void output(char *str[STR_LEN], int amount)
{
    int i;

    for(i=0; i<amount; i++)
    {
	puts(str[i]);
    }

}
