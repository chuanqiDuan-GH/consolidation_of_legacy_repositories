#include<stdio.h>

int main()
{
    int count = 3;
    int num[] = {0};
    int i = 0;
    int j = 0;

    char *str = "";
    char *temp = str;
    scanf("%s", str);
    printf("%s\n", temp);

#if 0 
    //scanf("%d", &count);
    printf("%d\n", count); 
    
    for(i; i<count; i++)
    {
	printf("%d\n", i);	
	scanf("%d", &num[i]);	
    }
    //scanf("%d", &num[i]);    
   
    for(j; j<count; j++)
    {
	printf("%d ", num[j]);	
    }
#endif
    return 0;
}
