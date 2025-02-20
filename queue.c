/* GAIBU Marius - 315CB */
#include "queue.h"

// Create the priority queue
Queue* create_queue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

// Add indices for a new railway at the end of the queue
void push(Queue *q, int src, int dest) {
    TList aux = (TList)malloc(sizeof(Cell));
    aux->src = src;
    aux->dest = dest;
    aux->next = NULL;

    if (!q->tail) {
        q->head = q->tail = aux;
    } else {
        q->tail->next = aux;
        q->tail = aux;
    }
}

// Remove indices from the front of the queue
void pop(Queue *q) {
    TList aux = q->head;

    if (q->head == q->tail) {
        q->head = q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    free(aux);
}

// Destroy the priority queue
void destroy_queue(Queue *q) {
    free(q);
}
