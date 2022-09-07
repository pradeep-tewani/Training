#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

//TODO 1:  Obtain a binary semaphore id, allocating if necessary
int binary_semaphore_allocate(key_t key, int sem_flags)
{
	return 0;
}

//TODO 2: Deallocate a binary semaphore. 
//All users must have finished their use. Returns -1 on failure
int binary_semaphore_deallocate(int semid)
{
	return 0;
}

//TODO 3: Obtain a pre-existing binary semaphore id without allocating
int binary_semaphore_get(key_t key, int sem_flags)
{
	return 0;
}

//TODO 4: Initialize a binary semaphore with a value of 1
int binary_semaphore_set(int semid)
{
	return 0;
}

/* 
 * Wait on a binary semaphore. 
 * Block until the semaphore value is positive, then decrement it by 1
 */
int binary_semaphore_wait(int semid)
{
	struct sembuf operations[1];

	//TODO 5: Use the first (and only) semaphore
	//TODO 6: Decrement by 1
	//TODO 7: Permit undoing
	//TODO 8: Finally perform the operation using semop
}

/* Post to a binary semaphore: Increment its value by 1. This returns immediately. */
int binary_semaphore_post(int semid)
{
	struct sembuf operations[1];

	//TODO 9: Use the first (and only) semaphore
	//TODO 10: Increment by 1
	//TODO 11: Permit undoing
	//TODO 12: Finally perform the operation using semop
}
