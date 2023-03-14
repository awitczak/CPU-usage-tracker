#include "mpsc_queue.h"

void mpsc_queue_init(mpsc_queue_t *queue) {
    mpsc_queue_node_t *init = (mpsc_queue_node_t *) malloc(sizeof(mpsc_queue_node_t));
    init->data = NULL;
    init->next = NULL;

    queue->head = queue->tail = init;
    atomic_init(&queue->cnt, 0);
}

void mpsc_queue_push_back(mpsc_queue_t *queue, void* data) {
    mpsc_queue_node_t *new = (mpsc_queue_node_t *) malloc(sizeof(mpsc_queue_node_t));
    new->data = data;
    new->next = NULL;
    
    mpsc_queue_node_t *prev_tail = atomic_exchange(&queue->tail, new);
    prev_tail->next = new;

    atomic_fetch_add(&queue->cnt, 1);
}

void *mpsc_queue_pop(mpsc_queue_t *queue) {
    mpsc_queue_node_t *head = queue->head;
    mpsc_queue_node_t *new_head = head->next;

    if (new_head == NULL) {
        return NULL;
    }

    void *data = new_head->data;
    queue->head = new_head;

    atomic_fetch_sub(&queue->cnt, 1);
    free(head);

    return data;
}

unsigned int get_mpsc_queue_size(mpsc_queue_t *queue) {
    return atomic_load(&queue->cnt);
}

bool mpsc_queue_destroy(mpsc_queue_t *queue) {
    while (mpsc_queue_pop(queue)) {}
    free(queue->head);

    return true;
}