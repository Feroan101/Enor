#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct stack {
    int32_t *data;
    size_t cap;
    size_t sp;
} stack;


int stack_init(stack *pm, size_t cap);

int stackunderflow(stack *pm);
int stackoverflow(stack *pm);

int push(stack *pm, int32_t push_value);
int pop(stack *pm, int32_t *pop_value);

#endif