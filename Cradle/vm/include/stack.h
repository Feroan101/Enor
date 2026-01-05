#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "errors.h"

typedef struct stack {
    int32_t *data;
    size_t cap;
    size_t sp;
} stack;


vm_errors stack_init(stack *pm, size_t cap);

vm_errors stackunderflow(stack *pm);
vm_errors stackoverflow(stack *pm);

vm_errors push(stack *pm, int32_t push_value);
vm_errors pop(stack *pm, int32_t *pop_value);

#endif