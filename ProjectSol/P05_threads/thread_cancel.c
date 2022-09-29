#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg)
{
	int i, res = 0, old_type;

        // TODO 2: Enable the cancellation
	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        // TODO 3: Set the cancellation type to DEFERRED
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &old_type);
        while (1);
	if (old_type == PTHREAD_CANCEL_DEFERRED)
		printf("Cancellation type is deferred\n");

	if (res != 0)
	{
		printf("Thread pthread_setcancelstate failed");
		pthread_exit(NULL);
	}
	printf("Thread_fuction is running\n");
	for(i = 0; i < 10; i++)
	{
		printf("Thread function is still running (%d) ...\n", i);
		sleep(1);
	}
	pthread_exit(NULL);
}

int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_create(&a_thread, NULL, &thread_function, NULL);
	if (res != 0)
	{
		printf("Thread creation failed");
		exit(EXIT_FAILURE);
	}

	sleep(1);
	printf("Cancelling thread ...\n");
        // TODO 1: Cancel the thread
	res = pthread_cancel(a_thread);
	if (res != 0)
	{
		printf("Thread Cancellation failed");
		exit(EXIT_FAILURE);
	}
	pthread_join(a_thread, NULL);
	exit(EXIT_SUCCESS);
}
