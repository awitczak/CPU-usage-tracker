#include "queue.h"

void queue_init(queue_t *queue) {
    queue_node_t *tmp = malloc(sizeof(queue_node_t));
    tmp->next = NULL;
    queue->head = tmp;
    queue->tail = tmp;

    pthread_mutex_init(&queue->head_lock, NULL);
    pthread_mutex_init(&queue->tail_lock, NULL);
}

void queue_destroy(queue_t *queue) {
    queue_node_t *tmp = queue->head;

    while (tmp != NULL) {
        queue_node_t *next = tmp->next;
        free(tmp);
        tmp = next;
    }

    pthread_mutex_destroy(&queue->head_lock);
    pthread_mutex_destroy(&queue->tail_lock);
}

void queue_push_back(queue_t *queue, void *data) {
    queue_node_t *tmp = malloc(sizeof(queue_node_t));

    tmp->data = data;
    tmp->next = NULL;

    pthread_mutex_lock(&queue->tail_lock);
    queue->tail->next = tmp;
    queue->tail = tmp;
    pthread_mutex_unlock(&queue->tail_lock);
}

void *queue_pop_back(queue_t *queue) {
    pthread_mutex_lock(&queue->head_lock);
    queue_node_t *tmp = queue->head;
    queue_node_t *new_head = tmp->next;
    
    /* if queue is empty */
    if (new_head == NULL) {
        pthread_mutex_unlock(&queue->head_lock);
        return NULL;
    }

    queue->head = new_head;
    pthread_mutex_unlock(&queue->head_lock);

    void *data = tmp->data;
    free(tmp);

    return data;
}