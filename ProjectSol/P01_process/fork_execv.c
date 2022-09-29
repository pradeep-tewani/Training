#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	char *agr[] = {"ls", "-l", "/", NULL};

	if (fork() == 0)
	{
		execv("/bin/ls", agr);
		printf("\nThis will not print, if all ok\n");
	}
	else
	{
		sleep(1);
		printf("\nDone with main program.\n");
	}
	return 0;
}
