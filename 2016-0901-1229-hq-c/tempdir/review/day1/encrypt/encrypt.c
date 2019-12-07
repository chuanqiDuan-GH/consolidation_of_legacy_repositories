#include <stdio.h>
#include <unistd.h>

# define NORMAL_SIZ 1024
#define CHMSK_KEY 0xcd

void encrypt(char *file)
{
    FILE *fp = fopen(file, "rb+");  
    char buf[NORMAL_SIZ];  
    int n;  

    while ((n = fread(buf, 1, NORMAL_SIZ, fp)) > 0)  
    {  
	int i;  

	for (i = 0; i < n; i++)  
	{  
	    buf[i] ^= CHMSK_KEY;  
	}  

	if (fseek(fp, -n, SEEK_CUR) == -1)  
	{  
	    perror("fseek");  
	}  

	n = fwrite(buf, 1, n, fp);  
	fflush(fp);
	buf[0] = 0;  
    }  

    fclose(fp);  
}
