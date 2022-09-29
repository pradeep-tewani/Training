#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "sig.h"

sig_atomic_t sigintcnt = 0;

void handler(int signum)
{
    ++sigintcnt;
    if (signum == SIGUSR1)
    {
        printf("Sleeping ...\n");
        sleep(10);
        printf("Done\n");
    }
}

int main()
{
    sigset_t sa_mask;
    // TODO 1: Register handler for SIGINT
    signal_register(SIGINT, handler, NULL, NULL);
    //memset(&sa, 0, sizeof(sa));
    //sa.sa_handler = &handler;

    //if (sigaction(SIGINT, &sa, NULL) == -1)
    //    perror("Failed to install SIGINT signal handler");
    // TODO 2: Add SIGINT to sa_mask;
    sigaddset(&sa_mask, SIGINT);

    // TODO 3: Register same handler for SIGUSR1 as well and provide sa_mask as arg
    signal_register(SIGUSR1, handler, NULL, &sa_mask);
    
    //if (sigaction(SIGUSR1, &sa, NULL) == -1)
     //   perror("Failed to install SIGUSR1 signal handler");

    for(;;)
    {
        printf("Signal Count: %d\n", (int)sigintcnt);	
        sleep(5); // Would return when signalled
    }
    return 0;
}
