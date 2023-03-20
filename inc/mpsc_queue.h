/** @file mpsc_queue.h
 * 
 * @brief Multiple producers, one consumer queue funcitons.
 *
 */ 

#ifndef MPSC_QUEUE_H
#define MPSC_QUEUE_H

#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct mpsc_queue_node {
    void *data;
    struct mpsc_queue_node *next;
} mpsc_queue_node_t;

typedef struct mpsc_queue_node *ptr_mpsc_queue_node;
typedef _Atomic(ptr_mpsc_queue_node) atomic_ptr_mpsc_queue_node_t;

typedef struct {
    mpsc_queue_node_t *head;
    mpsc_queue_node_t *tail;
    atomic_ptr_mpsc_queue_node_t atomic_tail;
    atomic_uint cnt;
} mpsc_queue_t;

void mpsc_queue_init(mpsc_queue_t *queue);
void mpsc_queue_push_back(mpsc_queue_t *queue, void* data);
void *mpsc_queue_pop(mpsc_queue_t *queue);
unsigned int get_mpsc_queue_size(mpsc_queue_t *queue);
bool mpsc_queue_destroy(mpsc_queue_t *queue);

#endif /* MPSC_QUEUE_H */

