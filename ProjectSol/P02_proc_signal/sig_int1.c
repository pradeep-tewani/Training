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

int main()
{
    int i;

    signal_register(SIGINT, handler, &sa_org, NULL);

    for(i = 0; i < 20; i++)
    {
        if (i == 10)
        {
            signal_restore(SIGINT, &sa_org);
            printf("Signal restored\n");
        }
        printf("Hmmmmm\n");
        sleep(1);
    }

    printf("\nSIGINT was raised %d times\n", sigint_count);
    return 0;
}
