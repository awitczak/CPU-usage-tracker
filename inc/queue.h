/** @file queue.h
 * 
 * @brief Queue creation.
 *
 * @par       
 * 
 */ 

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QUEUE_SIZE 64

typedef struct queue {
    void **data;
    size_t head;
    size_t tail;
    size_t size;
    size_t count;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} queue_t;

void queue_init(queue_t *queue, size_t queue_size);
void queue_push(queue_t *queue, void *item);
void *queue_pop(queue_t *queue);

#endif /* QUEUE_H */

