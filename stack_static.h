#ifndef _STACK
#define _STACK

#include "reading.h"
#define t_elems reading*

typedef struct _stack {
  t_elems* s;
  int top;
  int maxsize;
} stack;

stack* stack_new(int maxsize);

void stack_free(stack* s);

int stack_getsize(stack* s);

int stack_getmaxsize(stack* s);

void push(stack* s, t_elems elem);

t_elems pop(stack* s);

t_elems top(stack* s);

int stack_isempty(stack* s);

int stack_isfull(stack* s);

void stack_destroy(stack* s, void elem_free(t_elems));

#endif
