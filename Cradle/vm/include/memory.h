#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "stack.h"

#define MEM_SIZE 256

int stackoverflow(stack *pm);
int stackunderflow(stack *pm);

int OP_LOAD(stack *p, int32_t *mem, int32_t index);
int OP_STORE(stack *p, int32_t *mem, int32_t index);

#endif