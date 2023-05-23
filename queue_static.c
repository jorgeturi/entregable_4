#include <stdio.h>
#include <stdlib.h>

#include "queue_static.h"

queue* queue_new(int maxsize){
    queue* q = (queue*)malloc(sizeof(queue));
    q->a = (t_elem*)malloc(sizeof(t_elem)*maxsize);
    q->head = 0;
    q->tail = 0;
    q->maxsize = maxsize;
    q->count = 0;
    return q;
}

void queue_free (queue* q){
    free(q->a);
    free(q);
}

int queue_getmaxsize(queue* q){
    return q->maxsize;
}

int queue_getsize(queue* q){
    return q->count;
}

int queue_isfull (queue* q){
    //return (q->count == q->maxsize)?1:0;
    return q->count == q->maxsize;
}

int queue_isempty (queue* q){
    //return (q->count == 0)?1:0;
    return q->count == 0;
}

void enqueue (queue* q, t_elem elem){
    if (queue_isfull(q)){
        printf("Queue overflow\n");
        exit(1);
    }

    q->a[q->tail] = elem;
    q->tail = (q->tail+1)%(q->maxsize);
    q->count++;
}

t_elem dequeue (queue* q){

    if (queue_isempty(q)){
        printf("Queue underflow\n");
        exit(1);
    }

    t_elem result = (t_elem) q->a[q->head];
    q->head = (q->head+1)%(q->maxsize);
    q->count--;
    return result;
}

t_elem peek (queue* q){
    if (queue_isempty(q)){
        printf("Queue underflow\n");
        exit(1);
    }
    return q->a[q->head];
}
