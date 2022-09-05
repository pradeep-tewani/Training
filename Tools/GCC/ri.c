#include <stdio.h>

int read_int(int *ip)
{
	printf("Enter an integer: ");
	return scanf("%i", ip);
}
