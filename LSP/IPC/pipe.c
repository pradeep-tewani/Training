#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void writer(const char *message, int count, int fd)
{
    int len = strlen(message);
    for(; count > 0; --count)
    {
        if (write(fd, message, len) < 0)
        {
            printf("Unable to write\n");
            return;
        }
        sleep(2);
    }
}

void reader(int fd)
{
    char buffer[1024];
	int i = 0;
    while (read(fd, buffer, sizeof(buffer)) > 0)
        printf("%s %d\n", buffer, i++);
}

int main()
{
    int fds[2];
    pid_t pid;
    
    // TODO 1: Create the pipe

    // TODO 2: Create the new process

    // TODO 3: Make a child read from the pipe
	if (pid == (pid_t)0)
	{
		printf("I am in child\n");
		reader(fds[0]);
	}
    else // TODO 4: Make a parent to write to pipe
	{
		printf("I am in parent\n");
		sleep(5);
		writer("Hello, World", 5, fds[1]);
	}
		
    return 0;
}
