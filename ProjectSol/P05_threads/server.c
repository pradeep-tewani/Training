#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include <sys/shm.h>

#include "sig.h"
#include "em_registers.h"
#include "sem.h"

#define FIFO_NAME "myfifo"
#define KEY 0x12345 // Would retrieve the same if not detached

void sig(int signum)
{
    printf("Received signal %d\n", signum);
}

int get_lib_count()
{
    int libcount;
    // TODO 6: Open the pipe with ls lib*.so
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

void *shm_allocate(key_t key, size_t shm_size,
        int flags, int *shm_id, void *addr)
{
    // TODO 7: Allocate the shared memory
    *shm_id  = shmget(key, shm_size, flags);
    printf("The segment id: %d (0x%X)\n", *shm_id, *shm_id);

    // TODO 8: Attach the shared memory
    return shmat(*shm_id, addr, 0);
}

int main()
{
    int fd, libcount;
    struct em_registers reg;
    int shm_id;
    char *shm_addr = NULL;
    const int shm_size = sizeof(struct em_registers);
    int sem_id;

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

    //TODO 9: Allocate the shared memory
    shm_addr = shm_allocate(KEY, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR, &shm_id, shm_addr);
    if (shm_addr == NULL)
    {
        printf("Unable to allocate the shared memory\n");
        return -1;
    }
    printf("Shared memory attached at address %p\n", shm_addr);

    // TODO 10: Allocate the binary semaphore
    sem_id = binary_semaphore_allocate(KEY, S_IRUSR | S_IWUSR);
    printf("Semaphore created with id: %d\n", sem_id);

    // TODO 11: Initialize the binary semaphore
    binary_semaphore_set(sem_id);
    printf("1: Semaphore set to 1\n");

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
    // TODO 12: Get the semaphore
    if ((sem_id = binary_semaphore_get(KEY, S_IRUSR | S_IWUSR)) < 0)
    {
        perror("sem_get");
        printf("2: Semaphore connect failed\n");
        /* Cleanup */
        shmdt(shm_addr);
        shmctl(shm_id, IPC_RMID, 0);
        return -1;
    }
    else
    {
        printf("2: Semaphore connected\n");
    }
    while (1) 
    {
        /* Wait call */
        // TODO 14: Synchronize the access to shared memory using semaphore
        binary_semaphore_wait(sem_id);
        memcpy(&reg, shm_addr, sizeof(struct em_registers)); 

        /* Post call */
        binary_semaphore_post(sem_id);
        // TODO 5: Write EM Registers to the FIFO
        if ((write(fd, &reg, sizeof(struct em_registers))) < 0)
        {
            perror("write");
            return -1;
        }
        sleep(5);
        printf("Sent shared registers\n");
    }
    close(fd);

    return 0;
}
