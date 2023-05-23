#include <stdio.h>
#include <stdlib.h>


#include "stack_static.h"

stack* stack_new(int maxsize){
    stack* s = (stack*)malloc(sizeof(stack));
    s->s = (t_elems*)malloc(sizeof(t_elems)*maxsize);
    s->maxsize = maxsize;
    s->top = -1;
    return s;
}

void stack_free(stack* s){
    free(s->s);
    free(s);
}

int stack_getsize(stack* s){
    return s->top+1;
}

int stack_getmaxsize(stack* s){
    return s->maxsize;
}

void push(stack* s, t_elems elem){
    if(s->top == s->maxsize-1){
        printf("Stack overflow\n");
        exit(1);
    }
    s->top++;
    s->s[s->top] = elem;
}

t_elems pop(stack* s){
    if(s->top == -1){
        printf("Stack underflow\n");
        exit(1);
    }
    t_elems elem = s->s[s->top];
    s->top--;
    return elem;
}

t_elems top(stack* s){
    if(s->top == -1){
        printf("Stack underflow\n");
        exit(1);
    }
    return s->s[s->top];
}

int stack_isempty(stack* s){
    //return (s->top == -1)?1:0;
    return s->top == -1;
}

int stack_isfull(stack* s){
    //return (s->top == s->maxsize-1)?1:0;
    return s->top == (s->maxsize-1);
}

void stack_destroy(stack* s, void elem_free(t_elems)){
    while (!stack_isempty(s)){
        elem_free(pop(s));
    }
}
