#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sig.h"

#define FIFO_FILE "fifo"

void broken_pipe(int sno)
{
    printf("Broken Pipe %d. Let's continue ...\n", sno);
}

int main(int argc, char *argv[])
{
    int cnt = 1, i;
    FILE *fp;

    if ((argc != 2) && (argc != 3))
    {
        printf("Usage: fifoclient <string> [ <cnt> ]\n");
        return 1;
    }
    if (argc == 3)
    {
        cnt = atoi(argv[2]);
    }
    //TODO 1: Register the handler for SIGPIPE
    signal_register(SIGPIPE, broken_pipe, NULL, NULL);

    //TODO 2: Create the FIFO using library function
    mkfifo(FIFO_FILE, S_IFIFO | S_IRUSR | S_IWUSR);

    printf("\nSending %d \"%s\" to %s ", cnt, argv[1], FIFO_FILE);
    fflush(stdout);
    //TODO 3: Open the FIFO file
    if ((fp = fopen(FIFO_FILE, "w")) == NULL)
    {
        perror("fopen");
        return 2;
    }
    for (i = 0; i < cnt; i++)
    {
        // TODO 4: Write to the FIFO using fputs
        fputs(argv[1], fp);
        fputs("\n", fp);
        fflush(fp);
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf(" done\n");
    fclose(fp);

    return 0;
}
