/** @file queue.h
 * 
 * @brief Queue creation.
 *
 * @par       
 * 
 */ 

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <pthread.h>

typedef struct queue_node {
    void *data;
    struct queue_node *next;
} queue_node_t;

typedef struct {
    queue_node_t *head;
    queue_node_t *tail;
    pthread_mutex_t head_lock;
    pthread_mutex_t tail_lock;
} queue_t;

void queue_init(queue_t *queue);
void queue_destroy(queue_t *queue);
void queue_push_back(queue_t *queue, void *data);
void *queue_pop_back(queue_t *queue);

#endif /* QUEUE_H */

