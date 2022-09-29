#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "sig.h"

sig_atomic_t sigint_count = 0;
struct sigaction sa_org;

void handler(int signum)
{
    sigint_count++;
}

void handler1(int sig, siginfo_t *info, void *ucontext)
{
    printf("sid = %d\n", info->si_pid);
}
int main()
{
    int i;

    // TODO 6: Register the handler SIGINT
    //signal_register(SIGINT, handler, NULL, NULL);
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_handler = handler1;
    sigaction(SIGINT, &sa, NULL);

    for(i = 0; i < 20; i++)
    {
        printf("Hmmmmm\n");
        sleep(5);
    }

    printf("\nSIGINT was raised %d times\n", sigint_count);
    return 0;
}
