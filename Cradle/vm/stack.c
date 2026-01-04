#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int stack_init(stack *pm, size_t cap) {
    pm->cap = cap;
    pm->sp = 0;
    pm->data = malloc(sizeof(int32_t) * pm->cap);
    if (!pm->data) return 3;
    return 0;
}

int stackoverflow(stack *pm) {
    if (pm->cap == pm->sp) {
        int *tmp = realloc(pm->data, sizeof(int32_t) * pm->cap * 2);
        if (tmp == NULL) {
            printf("couldnt allocate more memory");
            return 4;
        }
        pm->cap = pm->cap * 2;
        pm->data = tmp;
    }
    return 0;
}

int stackunderflow(stack *pm) {
    if (pm->sp <= 0) {
        printf("trying to access memory that is not avalible\n");
        pm->sp = 0;
        return 5;
    }
    return 0;
}

int push(stack *pm, int32_t push_value) {
    if (stackoverflow(pm)) return 4; 

    pm->data[pm->sp++] = push_value;
    return 0;
}

int pop(stack *pm, int32_t *pop_value) {
    if (stackunderflow(pm)) return 5;

    *pop_value = pm->data[--pm->sp];
    return 0;
}
