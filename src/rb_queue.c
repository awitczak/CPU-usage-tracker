#include "rb_queue.h"

void rb_queue_init(rb_queue_t *queue, size_t size) {
    queue->data = malloc(sizeof(void *) * size);
    queue->size = size;
    queue->head = 0;
    queue->tail = 0;

    for (size_t i = 0; i < size; i++) {
        queue->data[i] = NULL;
    }

    pthread_mutex_init(&queue->lock, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
    pthread_cond_init(&queue->not_full, NULL);
}

void rb_queue_push_back(rb_queue_t *queue, void *data) {
    pthread_mutex_lock(&queue->lock);

    while ((queue->tail + 1) % queue->size == queue->head) {
        pthread_cond_wait(&queue->not_full, &queue->lock);
    }

    queue->data[queue->tail] = data;
    queue->tail = (queue->tail + 1) % queue->size;

    pthread_cond_signal(&queue->not_empty);
    pthread_mutex_unlock(&queue->lock);
}

void *rb_queue_pop(rb_queue_t *queue) {
    pthread_mutex_lock(&queue->lock);

    while (queue->head == queue->tail) {
        pthread_cond_wait(&queue->not_empty, &queue->lock);
    }

    void *data = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->size;

    pthread_cond_signal(&queue->not_full);
    pthread_mutex_unlock(&queue->lock);

    return data;
}

size_t rb_queue_count(rb_queue_t *queue) {
    pthread_mutex_lock(&queue->lock);
    size_t count = (queue->tail - queue->head + queue->size) % queue->size;
    pthread_mutex_unlock(&queue->lock);
    return count;
}

void rb_queue_destroy(rb_queue_t *queue, size_t size) {
    
    // if (queue->data != NULL) {
    //     for (size_t i = 0; i < size; i++) {
    //         if (queue->data[i] != NULL) {
    //             free(queue->data[i]);
    //         }
    //     }
    //     free(queue->data);
    // }

    free(queue->data);

    queue->data = NULL;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;

    pthread_cond_destroy(&queue->not_empty);
    pthread_cond_destroy(&queue->not_full);
    pthread_mutex_destroy(&queue->lock);
}
