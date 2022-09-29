#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"

int main()
{
    char s[300];
    int fd, ret, num;

    // TODO 1: Create FIFO using the system call
    if (mknod(FIFO_NAME, S_IFIFO | S_IRUSR | S_IWUSR, 0) == -1)
    {
        perror("mknod");
    }

    printf("Waiting for readers ...\n");
    // TODO 2: Open the FIFO for write only 
    if ((fd = open(FIFO_NAME, O_WRONLY)) == -1)
    {
        perror("open");
        return 1;
    }
    printf("Got a reader - Type some stuff\n");

    while ((ret = scanf("%[^\n]%*c", s)), !feof(stdin)) 
    {
        if (ret == 0) // No input read - remove the newline
        {
            getchar();
            continue;
        }
        // TODO 3: Write to FIFO
        if ((num = write(fd, s, strlen(s))) == -1)
        {
            perror("write");
        }
        else
        {
            printf("speak: wrote %d bytes\n", num);
        }
    }

    close(fd);

    return 0;
}
