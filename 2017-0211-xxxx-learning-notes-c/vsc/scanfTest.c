#include <stdio.h>

typedef struct staff
{
    int a;
    char b[16];
    float c;
}STAFF, *pSTAFF;

void func()
{
    char ss;
   STAFF s1;
   scanf("%d", &s1.a);
   scanf("%s", s1.b);
   //printf("%s\n", s1.b);
   getchar();
   scanf("%c", &ss);
   scanf("%f", &s1.c);

   printf("%d, %s, %.2f", s1.a, s1.b, s1.c);
}

int main()
{
    func();
    return 0;
}