#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include "sig.h"
#include "em_registers.h"

#define FIFO_NAME "myfifo"


void sig(int signum)
{
    printf("Received signal %d\n", signum);
}

int get_lib_count()
{
    int libcount;
    // TODO 7: Open the pipe with ls lib*.so
    FILE *stream = popen("ls lib*.c | wc -l", "r");

    if (stream == NULL)
    {
        perror("popen");
        return -1;
    }

    if (fscanf(stream, "%d", &libcount) > 0)
        return libcount;

    return -1;
}

int main()
{
    int fd, num, libcount;
    struct em_registers reg;

    memset(&reg, 0, sizeof(struct em_registers));
    reg.va = 440;
    reg.vb = 438;
    reg.vc = 430;
    
    // TODO 1: Register handler sig for SIGINT and SIGPIPE
    signal_register(SIGINT, sig, NULL, NULL);
    signal_register(SIGPIPE, sig, NULL, NULL);

    // TODO 2: Get the count of lib*.so files using pipe
    libcount = get_lib_count();
    if (libcount > 0)
    {
        printf("Library count = %d\n", libcount);
    }
    
    // TODO 3: Create the FIFO
    if (mknod(FIFO_NAME, S_IFIFO | S_IRUSR | S_IWUSR, 0) == -1)
    {
        perror("mknod");
    }

    printf("Waiting for readers ...\n");
    // TODO 4: Open the FIFO
    if ((fd = open(FIFO_NAME, O_WRONLY)) == -1)
    {
        perror("open");
        return 1;
    }
    printf("Got a reader - Sending registers\n");
    // TODO 5: Write EM Registers to the FIFO
    if ((num = write(fd, &reg, sizeof(struct em_registers))) == -1)
    {
        perror("write");
    }
    else
        printf("Wrote %d bytes\n", num);
    close(fd);

    return 0;
}
