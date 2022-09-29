#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
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
    segment_id = shmget(key, SEGMENT_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    printf("1: Allocated a shared segment\n");

    // TODO 2: Attach shared memory segment
    shared_memory = (char*)shmat(segment_id, NULL, 0);
    printf("1: Mapped shared memory at address %p\n", shared_memory);

    // TODO 3: Allocate the binary semaphore
    sem_id = binary_semaphore_allocate(key, S_IRUSR | S_IWUSR);
    printf("1: Semaphore created with id: %d\n", sem_id);

    // TODO 4: Initialize the semaphore
    binary_semaphore_set(sem_id);
    printf("1: Semaphore set to 1\n");

    // TODO 5: Invoke wait
    binary_semaphore_wait(sem_id);
    printf("1: Wait call returned\n");

    /* Write a string to the shared memory segment */
    sprintf(shared_memory, "Hi how r you?");
    printf("1: Message posted and timepass for half a minute. Now run ./sem_two\n");
    sleep(30);

    // TODO 6: Invoke post
    binary_semaphore_post(sem_id);
    printf("1: Post call returned\n");

    // TODO 7: Invoke wait
    binary_semaphore_wait(sem_id);
    printf("1: Wait call returned\n");	

    /* Print out the string from shared memory */
    printf("1: Shared memory has \"%s\"\n", shared_memory);

    // TODO 8: Invoke post
    binary_semaphore_post(sem_id);
    printf("1: Post call returned\n");

    // TODO 9: Detach the shared memory
    shmdt(shared_memory);
    printf("1: Unmapped shared memory\n");

    return 0;
}
