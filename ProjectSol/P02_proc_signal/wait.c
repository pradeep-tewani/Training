#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status, i;
#if 0
    if (fork() == 0)
    {
        for (i = 0; i < 20; i++)
        {
            sleep(1);
        }
    }
    else
#endif
    {
        //fork();
        //fork();
        // TODO 1: Wait for the child process termination
        wait(&status);
        // TODO 2: Print the exit code, if process exited normally
        // TODO 3: Print the signal number, if process terminated by signals
        if (WIFEXITED(status))
        {
            printf("\nThe Child Process exited normally, with the exit code %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("The child process killed with the signal %d\n", WTERMSIG(status));
        }
        else
        {
        }
        printf("\nDone with main program.\n");
    }
    return 0;
}
