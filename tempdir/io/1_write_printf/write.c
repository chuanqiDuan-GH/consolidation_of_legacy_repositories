#include <stdio.h>
#include <unistd.h>

int main()
{
	write(1, "hello linux\n", 128);
	return 0;
}
