/* GAIBU Marius - 315CB */
#include "queue.h"

// Crează coada de prioritate
Queue* create_queue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

// Adaugă indicii unei căi ferate noi la sfârșitul cozii
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

// Elimină indicii căii ferate din vârful cozii
void pop(Queue *q) {
    TList aux = q->head;

    if (q->head == q->tail) {
        q->head = q->tail = NULL;
    } else {
        q->head = q->head->next;
    }
    free(aux);
}

// Distruge coada de prioritate
void destroy_queue(Queue *q) {
    free(q);
}
