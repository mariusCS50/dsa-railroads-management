/* GAIBU Marius - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

// Structure representing a railroad between source and destination cities
typedef struct cell {
    int src, dest;
    struct cell *next;
} Cell, *TList;

// Structure representing the queue
typedef struct queue {
    TList head, tail;
} Queue;

// Functions for processing the queue
Queue *create_queue();
void push(Queue *q, int src, int dest);
void pop(Queue *q);
void destroy_queue(Queue* q);
