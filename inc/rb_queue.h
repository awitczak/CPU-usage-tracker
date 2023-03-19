/** @file queue.h
 * 
 * @brief Queue creation.
 *
 * @par       
 * 
 */ 

#ifndef RB_QUEUE_H
#define RB_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct rb_queue {
    void **data;
    size_t size;
    size_t head;
    size_t tail;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} rb_queue_t;

void rb_queue_init(rb_queue_t *queue, size_t size);
void rb_queue_push_back(rb_queue_t *queue, void *data);
void *rb_queue_pop(rb_queue_t *queue);
size_t rb_queue_count(rb_queue_t *queue);
void rb_queue_destroy(rb_queue_t *queue, size_t size);

#endif /* RB_QUEUE_H */

