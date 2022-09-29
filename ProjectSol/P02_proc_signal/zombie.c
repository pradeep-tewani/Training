#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int cpid, status;

    if ((cpid = fork()) != 0)
    {
        printf("\nParent sleeping\n");
        sleep(30);
        if (cpid > 0)
        {
            wait(&status);
        }
        printf("\nParent over\n");
    }
    else
    {
        printf("\nChild done\n");
    }
    return 0;
}
