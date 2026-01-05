#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "stack.h"
#include "errors.h"

#define MEM_SIZE 32768

vm_errors OP_LOAD(stack *p, int32_t *mem, int32_t index);
vm_errors OP_STORE(stack *p, int32_t *mem, int32_t index);

#endif