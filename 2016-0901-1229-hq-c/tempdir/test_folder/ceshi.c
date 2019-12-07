#include <stdio.h>
#include <string.h>
#if 0
int func(char *s,char a,int n)
{  int j;
    *s=a; j=n ;
    while (*s<s[j]) j-- ;
    return j;
}
void main ( )
{  char c[6] ;
    int i ;
    for (i=1; i<=5 ; i++) *(c+i)='A'+i+1;
    printf("%d\n",func(c,'E',5));
}

void sub(char *a,char b)
{  while (*(a++)!='\0') ;
    while (*(a-1)<b)
	*(a--)=*(a-1);
    *(a--)=b;
}
void main ( )
{  char s[]="97531",c;
    c = getchar ( ) ;
    sub(s,c); puts(s) ;
}
#endif
void main ( )
{  
#if 0
    char *a[]={"Pascal","C Language","dBase","Java"};
    char (**p)[ ] ; int j ;
    p = a + 3 ;
    for (j=3; j>=0; j--)
	printf("%s\n",*(p--)) ;
#endif
#if 0
    char str[10] = {'0'};
    gets(str);
    printf("%d", strcmp(str, "add"));
#endif
#if 0
    char str[1] = {'0'};
    int i = 1000;
    fflush(stdout);
    while(i--)
    {
	fprintf(stdout, str);
	//printf("%s" ,str);

    }
    system("free -m");    
    while(1);
#endif
#if 0
    int num[][2] = {{1,2}, {3,4,5}};
#endif
}


