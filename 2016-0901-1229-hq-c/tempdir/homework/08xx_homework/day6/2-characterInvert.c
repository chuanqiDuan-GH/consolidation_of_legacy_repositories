#include<stdio.h>
#include<string.h>
char *invert(char *str);

int main()
{
    //什么情况下用*str比较好，什么情况下用str[]比较好
    //
    //char* p是一个指针，根本没分配内存，他指向的"abc123ABC" 是只读的，不能改变，你在下面给他赋值肯定是错的.
    //而char p[]是一个数组，已经分配内存，是将"abc123ABC" 复制到该内存里面，这个内存是可读写的
    //
    //指针是不分配内存的，它指向的是系统的只读的内存，
    //而数组是分配内存的，就是将系统的只读的内存里面的值复制到它的内存里面，因此可读写
    //
    //char* p是定义的一个指针。他指向的字符窜"abc123ABC" 是存在不可修改的区域(代码区)的。
    //而char p[]是一个数组。他的内容存在栈区可以修改
    char str[] = "0";  
    gets(str);
    char *invertStr = "0"; 
    invertStr = invert(str);
    puts(invertStr);
    //printf("%s\n", str);
}


char *invert(char *str)
{
    char temp = '0';
    int i = 0;
    int j = strlen(str);
    while(i < (j-1))
    {
	temp = str[i];
	str[i] = str[j-1];
	str[j-1] = temp;
	i++;
	j--;
    }

    return str;

}
