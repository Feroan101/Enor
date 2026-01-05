#include "arena.h"

vm_errors OP_LOAD(stack *p, int32_t *mem, int32_t index) {
    //check if mem is out of bounds
    if (index < 0 || index >= MEM_SIZE) return VM_ERR_OUT_OF_BOUNDS;
    if (push(p, mem[index])) return VM_ERR_STACK_OVERFLOW;             
    return VM_OK;
}

vm_errors OP_STORE(stack *p, int32_t *mem, int32_t index) {
    if (index < 0 || index >= MEM_SIZE) return VM_ERR_OUT_OF_BOUNDS;
    int32_t value;
    if (pop(p, &value)) return VM_ERR_STACK_UNDERFLOW;  
    mem[index] = value;
    return VM_OK;
}
