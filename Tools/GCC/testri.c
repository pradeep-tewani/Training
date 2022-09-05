#include <stdio.h>
#include "ri.h"

int main()
{
	int i;

	read_int(&i);
	printf("Read %d\n", i);
	return 0;
}
