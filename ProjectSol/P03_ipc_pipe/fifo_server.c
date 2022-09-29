#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "fifo"

int main(void)
{
	FILE *fp;
	char readbuf[80];

        //TODO 1: Create the FIFO using library function
	mkfifo(FIFO_FILE, S_IFIFO | S_IRUSR | S_IWUSR);

	printf("\nWaiting for writer clients ...\n");
        //TODO 2: Open the FIFO file
	fp = fopen(FIFO_FILE, "r");
        //TODO 3: Read & print until EOF
	while (fgets(readbuf, 80, fp))
	{
		printf("Received string: %s\n", readbuf);
	}
	fclose(fp);

	return 0;
}
