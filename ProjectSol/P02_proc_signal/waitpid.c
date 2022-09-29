#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status, w, pid;

    if ((pid = fork()) == 0)
    {
        pause();
    }
    else
    {
        do {
            // TODO 1: Wait for the child with waitpid
            // Make sure to include WUNTRACED and WCONTINUE options
            w = waitpid(pid, &status, 0);
            if (w == -1) 
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            // TODO 2: Check if exited normally or abnormally and print status accordingly
            // TODO 3: Check for the stop and continue signals

            if (WIFEXITED(status)) 
            {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } 
            else if (WIFSIGNALED(status)) 
            {
                printf("killed by signal %d\n", WTERMSIG(status));
            } 
            else if (WIFSTOPPED(status)) 
            {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } 
            else if (WIFCONTINUED(status)) 
            {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        printf("\nDone with main program.\n");
    }
    return 0;
}
