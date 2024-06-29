/* GAIBU Marius - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

// Structura reprezintă indivii unei căi ferate dintre orașele sursă și destinație
typedef struct cell {
    int src, dest;
    struct cell *next;
} Cell, *TList;

// Structura care reprezintă coada
typedef struct queue {
    TList head, tail;
} Queue;

// Funcțiile de prelucrare a cozii
Queue *create_queue();
void push(Queue *q, int src, int dest);
void pop(Queue *q);
void destroy_queue(Queue* q);
