#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

int create_thread(pthread_t *thread_id, const pthread_attr_t *attr,
                        void *(*fn) (void *), void *arg);

int thread_wait(pthread_t thread, void **ret);

#endif
