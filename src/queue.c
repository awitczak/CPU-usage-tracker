#include "queue.h"

void queue_init(queue_t *queue, size_t queue_size) {
    queue->head = 0;
    queue->tail = 0;
    queue->size = queue_size;
    queue->count = 0;

    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);
}

void queue_push(queue_t *queue, void *item) {
    /* acquire mutex */
    pthread_mutex_lock(&queue->lock);

    /* wait for the queue to not be full before trying to add an item */
    while (queue->count == queue->size) {
        pthread_cond_wait(&queue->not_full, &queue->lock);
    }

    queue->data[queue->tail] = item;
    queue->tail = (queue->tail + 1) % queue->size;
    queue->count++;

    /* signal not_empty, as an item was added to the queue */
    pthread_cond_signal(&queue->not_empty);

    /* release mutex */
    pthread_mutex_unlock(&queue->lock);
}   

void *queue_pop(queue_t *queue) {
    /* acquire mutex */
    pthread_mutex_lock(&queue->lock);

    /* wait for the queue to not be empty before trying to remove an item */
    while (queue->count == 0) {
        pthread_cond_wait(&queue->not_empty, &queue->lock);
    }

    void *item = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->size;
    queue->count--;

    /* signal not_full, as an item was removed from the queue */
    pthread_cond_signal(&queue->not_full);

    /* release mutex */
    pthread_mutex_unlock(&queue->lock);

    return item;
}