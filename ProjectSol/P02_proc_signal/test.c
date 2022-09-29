#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "sig.h"


void sig(int signum)
{
    printf("Received signal\n");
}

void sig1(int signum)
{
    printf("Received SIGUSR1\n");
}

int main()
{
    int status, i;
    pid_t pid = fork();

    if (pid == 0) 
    {
        printf("Parent process id is %d\n", getppid());
        //execl("./exec_overlay", "exec_overlay", (char *)0);
        //printf("This shouldn't print\n");
        signal_register(SIGUSR1, sig1, NULL, NULL);
        for (i = 0; i < 5; i++)
        {
            printf("Waiting\n");
            sleep(1);
        }

        return 0;
    }
    else 
    {
        printf("Pid for child process is %d\n", pid);
        sleep(2);
        signal_send(pid, SIGUSR1);
        pid = wait(&status);
        printf("Process %d terminated\n", pid);
        signal_register(SIGINT, sig, NULL, NULL);
        for (i = 0; i < 20; i++)
        {
            sleep(1);
        }
        return 0;
    }
    return 0;
}
