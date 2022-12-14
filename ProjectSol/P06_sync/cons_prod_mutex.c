#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>

static sem_t sem;

struct job
{
    int data;
    struct job* next;
};

static struct job* job_queue;

static pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

void random_sleep(int factor)
{
    int s;

    s = 1 + (int)((1.0 * rand() / RAND_MAX) * factor);
    sleep(s);
}

void process_job(struct job* next_job, long no)
{
    int id;

    id = (int)pthread_self();
    printf("\nThread %ld (%u) finished job %d\n", no, id, next_job->data);
    random_sleep(1);
}
void *consumer(void *arg)
{
    struct job *next_job;

    while (1)
    {

        if (sem_trywait(&sem) == 0) {
            pthread_mutex_lock(&job_queue_mutex);
            if (job_queue == NULL)
                next_job = NULL;
            else
            {
                next_job = job_queue;
                job_queue = job_queue->next;
            }
            pthread_mutex_unlock(&job_queue_mutex);

            if (next_job == NULL)
                continue;
            process_job(next_job, (long)(arg));
            free(next_job);
        }
        else {

            // DO something else
        }
    }
    printf("\nThread %ld Done.\n", (long)(arg));
    return NULL;
}

void enqueue_job(void)
{
    static int i = 0;
    struct job *new_job;
    new_job->data = i++;

    sem_wait(&sem1);
    pthread_mutex_lock(&job_queue_mutex);
    new_job->next = job_queue;
    job_queue = new_job;
    sem_post(&sem);
    pthread_mutex_unlock(&job_queue_mutex);

    printf("\nJob no %d is added.\n", i - 1);
}
void *producer(void *arg)
{
    int i;

    while (1)
    {
        enqueue_job();
        random_sleep(4);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t th_id1, th_id2, th_prod;

    sem_init(&sem, 0, 0);
    sem_init(&sem1, 0, 100);

    for(i = 0; i < 6; i++) // Put some jobs to start with
    {
        enqueue_job();
    }
    pthread_create(&th_id1, NULL, &consumer, (void *)(1L));
    pthread_create(&th_id2, NULL, &consumer, (void *)(2L));
    pthread_create(&th_prod, NULL, &producer, NULL);

    pthread_join(th_prod, NULL);

    return 0;
}
