#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "sem.h"

#define SEGMENT_SIZE 0x400

int main()
{
    key_t key = 0x12345; // Using same for both shm & sem
    int segment_id;
    char *shared_memory;
    int sem_id;

    // TODO 1: Allocate shared memory segment using shmget
    segment_id = shmget(key, SEGMENT_SIZE, IPC_CREAT | S_IRUSR | S_IWUSR);
    printf("2: Allocated a shared segment\n");

    // TODO 2: Attach shared memory segment
    shared_memory = (char*)shmat(segment_id, NULL, 0);
    printf("2: Mapped shared memory at address %p\n", shared_memory);

    // TODO 3: Allocate the binary semaphore
    if ((sem_id = binary_semaphore_get(key, S_IRUSR | S_IWUSR)) < 0)
    {
        perror("sem_get");
        printf("2: Semaphore connect failed\n");
        /* Cleanup */
        shmdt(shared_memory);
        shmctl(segment_id, IPC_RMID, 0);
        return 1;
    }
    else
    {
        printf("2: Semaphore connected\n");
    }

    // TODO 4: Invoke wait
    binary_semaphore_wait(sem_id);
    printf("2: Wait call returned\n");

    /* Print out the string from shared memory */
    printf("2: Shared memory has \"%s\"\n", shared_memory);

    /* Write a string to the shared memory segment */
    sprintf(shared_memory, "I am fine. How r u?");
    printf("2: Message posted and timepass for a 6 secs\n");
    sleep(6);

    // TODO 5: Invoke post
    binary_semaphore_post(sem_id);
    printf("2: Post call returned\n");

    // TODO 6: De-allocate the semaphore
    binary_semaphore_deallocate(sem_id);
    printf("2: Semaphore freed\n");

    // TODO 7: Detach the shared memory
    shmdt(shared_memory);
    printf("2: Unmapped shared memory\n");
    sleep(2);

    // TODO 8: Deallocate the shared memory segment
    shmctl(segment_id, IPC_RMID, 0);
    printf("2: Finally deallocated the shared memory\n");

    return 0;
}
