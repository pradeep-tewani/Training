#include <stdio.h>
#include <stdlib.h>

/*
 * Assignment to demonstrate the usage of FIFO.
 * Sorts the file listing by using the ls and sort
 * commands
 */

int main()
{
    FILE *pipein_fp, *pipeout_fp;
    char readbuf[80];

    // TODO 1: Create one way pipe line with call to popen() and ls as arg
    if ((pipein_fp = popen("ls", "r")) == NULL)
    {
        perror("popen ls:");
        exit(1);
    }
    /* Create one way pipe line with call to popen() */
    // TODO 2: Create one way pipe line with call to popen() and "sort -r" as arg
    if ((pipeout_fp = popen("sort -r", "w")) == NULL)
    {
        perror("popen sort:");
        exit(1);
    }

    /* Processing loop */
    // TODO 3: Read from the pipe into readbuff and write to the pipeout_fp
    while (fgets(readbuf, 80, pipein_fp))
        fputs(readbuf, pipeout_fp);
    fflush(pipeout_fp);

    /* Close the pipes */
    pclose(pipein_fp);
    pclose(pipeout_fp);

    return 0;
}
