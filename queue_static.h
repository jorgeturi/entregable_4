#ifndef QUEUE_STATIC_H_INCLUDED
#define QUEUE_STATIC_H_INCLUDED

#include "reading.h"
#define t_elem reading*

typedef struct _queue{
    t_elem* a;
    int head;   //mark the first element
    int tail;   //mark the next empty position
    int maxsize;
    int count;
} queue;

queue* queue_new(int maxsize);

void queue_free (queue* q);

int queue_getmaxsize(queue* q);

int queue_getsize(queue* q);

int queue_isfull (queue* q);

int queue_isempty (queue* q);

void enqueue (queue* q, t_elem elem);

t_elem dequeue (queue* q);

t_elem peek (queue* q);


#endif // QUEUE_STATIC_H_INCLUDED
