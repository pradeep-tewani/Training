#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main()
{
	int semid, pid;
	struct sembuf sop;
	
	//TODO 1: Allocate the semaphore with semget
	//TODO 2: Set the semaphore value to 1 with semctl

	pid = fork();
	if (pid == 0)
	{
		printf("Child before semop\n");
		//TODO 3: Populate the sembuf to decrement the first semaphore
		//Set sem_flg to 0
		//TODO 4: Finally invoke the semop
		printf("Child in critical section for 10 seconds\n");
		printf("Parent may have to wait\n");
		sleep(10);
		printf("Child coming out of critical section\n");
		//TODO 5: Populate the sembuf to increment the first semaphore
		//Set sem_flg to 0
		//TODO 6: Finally invoke the semop
	}
	else
	{
		int child_status;

		printf("Parent before semop\n");
		//TODO 7: Populate the sembuf to decrement the first semaphore
		//Set sem_flg to 0
		//TODO 8: Finally invoke the semop
		printf("Parent in critical section\n");
		printf("Child may have to wait\n");
		sleep(10);
		printf("Parent coming out of critical section\n");
		//TODO 9: Populate the sembuf to increment the first semaphore
		//Set sem_flg to 0
		//TODO 10: Finally invoke the semop
	}

	return 0;
}
