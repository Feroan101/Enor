#include "memory.h"

int OP_LOAD(stack *p, int32_t *mem, int32_t index) {
    //check if mem is out of bounds
    if (index < 0 || index >= MEM_SIZE) return 5;
    if (push(p, mem[index])) return 4;             
    return 0;
}

int OP_STORE(stack *p, int32_t *mem, int32_t index) {
    if (index < 0 || index >= MEM_SIZE) return 5;
    int32_t value;
    if (pop(p, &value)) return 6;  
    mem[index] = value;
    return 0;
}
