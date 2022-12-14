/*
 * Example code for using pthreads condition variables. The main thread creates
 * three threads. Two of those threads increment a "count" variable, while the
 * third thread watches the value of "count". When "count" reaches a predefined
 * limit, the waiting thread is signaled by one of the incrementing threads. The
 * waiting thread "awakens" and then modifies count. The program continues until
 * the incrementing threads reach TCOUNT. The main program prints the final
 * value of count.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  3
#define TCOUNT 10
#define COUNT_LIMIT 12

static int count = 0;
static pthread_mutex_t count_mutex;
static pthread_cond_t count_threshold_cv;

void *inc_count(void *t) 
{
    int i;
    long my_id = (long)t;

    for (i = 0; i < TCOUNT; i++)
    {
        pthread_mutex_lock(&count_mutex);
        count++;

        /*
         * Check the value of count and signal waiting thread when condition is
         * reached.  Note that this occurs while mutex is locked
         */
        if (count == COUNT_LIMIT)
        {
            printf("inc_count(): thread %ld, count = %d. Threshold reached\n", my_id, count);
            pthread_cond_signal(&count_threshold_cv);
            printf("Just sent signal\n");
        }
        printf("inc_count(): thread %ld, count = %d\n", my_id, count);
        pthread_mutex_unlock(&count_mutex);

        /* Do some work so threads can alternate on mutex lock */
        sleep(1);
    }
    pthread_exit(NULL);
}

void *watch_count(void *t) 
{
	long my_id = (long)t;

	printf("Starting watch_count(): thread %ld\n", my_id);

	/*
	 * Lock mutex and wait for signal. Note that the pthread_cond_wait routine
	 * will automatically and atomically unlock mutex while it waits.
	 * Also, note that if COUNT_LIMIT is reached before this routine is run by
	 * the waiting thread, the loop will be skipped to prevent pthread_cond_wait
	 * from never returning.
	 */
	pthread_mutex_lock(&count_mutex);
	if (count < COUNT_LIMIT)
	{
		printf("watch_count(): thread %ld. Going into wait...\n", my_id);
		pthread_cond_wait(&count_threshold_cv, &count_mutex);
		printf("watch_count(): thread %ld. Condition signal received\n", my_id);
		count += 125;
		printf("watch_count(): thread %ld. Count now = %d\n", my_id, count);
	}
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i, rc; 
	long t1 = 1, t2 = 2, t3 = 3;
	pthread_t threads[3];

	/* Initialize mutex and condition variable objects */
	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init(&count_threshold_cv, NULL);

	pthread_create(&threads[0], NULL, &watch_count, (void *)t1);
	pthread_create(&threads[1], NULL, &inc_count, (void *)t2);
	pthread_create(&threads[2], NULL, &inc_count, (void *)t3);

	/* Wait for all threads to complete */
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	printf("main(): Waited on %d threads. Final value of count = %d. Done.\n", 
			NUM_THREADS, count);

	/* Clean up and exit */
	pthread_cond_destroy(&count_threshold_cv);
	pthread_mutex_destroy(&count_mutex);
	return 0;
}
