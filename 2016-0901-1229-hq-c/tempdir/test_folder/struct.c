#include<stdio.h>
#include<stdlib.h>
//结构体嵌套枚举
enum SEX{MAN, WOMEN};

typedef struct student
{
    int num;
    char name[5];
    enum SEX sex;
    double score;
    int class;	
}Student, *pStudent;

int main()
{

    int manNum = 0;	
    //结构体的初始化！
    Student s[3] = {{1, "AAA", MAN, 100, 1}, {2, "BBB", WOMEN, 99.5, 1}, {3, "SEI", WOMEN, 90, 2}};


    for(int i=0 ; i<3; i++)
    {	
	if(s[i].sex == 0)
	{
	    manNum++;	
	}		
    }

    printf("mans num is %d\n", manNum);	
}
