#include "instructions.h"

vm_errors OP_POP(stack *p) {
    int32_t trash;
    return pop(p, &trash);
}

vm_errors OP_ADD(stack *p) {
    int32_t val_1, val_2, result;
    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    result = val_1 + val_2;
    push(p, result);
    return VM_OK;
}

vm_errors OP_SUB(stack *p) {
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    int32_t result = val_2 - val_1;
    push(p, result);
    return VM_OK;
}

vm_errors OP_MUL(stack *p) {
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    int32_t result = val_1 * val_2;
    push(p, result);
    return VM_OK;
}

vm_errors OP_DIV(stack *p) {
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);
    if (val_2 == 0) return VM_ERR_DIV_BY_ZERO;

    if (val_1 == 0) result = val_2;
    else result = val_2 / val_1;
    push(p, result);
    return VM_OK;
}

vm_errors OP_DUP(stack *pm) {
    if (pm->sp < 1) return VM_ERR_STACK_UNDERFLOW;
    if (stackoverflow(pm)) return VM_ERR_STACK_OVERFLOW;

    pm->data[pm->sp] = pm->data[pm->sp - 1];
    pm->sp++;
    return VM_OK;
}

vm_errors OP_JMP(size_t *ip ,size_t limit ,size_t target) {
    if (target >= limit) return VM_ERR_INVALID_JUMP;

    // printf("JMP to %zu\n", target);
    *ip = target;
    return VM_OK;
}

vm_errors OP_JZ(stack *p, size_t *ip, size_t limit ,size_t target) {
    if (target >= limit)  return VM_ERR_INVALID_JUMP;
    int32_t value;

    if (pop(p, &value)) return VM_ERR_STACK_UNDERFLOW; 

    if (value == 0) {
        if (target >= limit) return VM_ERR_INVALID_JUMP;
        // printf("JZ to %zu\n", target);
        *ip = target;
    } else {
        *ip += 3;  
    }

    return VM_OK;
}

vm_errors OP_PRINT(stack *p) {
    int32_t value;
    if (pop(p, &value)) return VM_ERR_STACK_UNDERFLOW;
    printf("%d\n", value);
    return VM_OK;
}

vm_errors OP_SWAP(stack *p) {
    if (p->sp < 2) return VM_ERR_STACK_UNDERFLOW;
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    push(p, val_1);
    push(p, val_2);
    return VM_OK;
}

vm_errors OP_EQ(stack *p) {
    if (p->sp < 2) return VM_ERR_STACK_UNDERFLOW;
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    if (val_1 == val_2) result = 1;
    else result = 0;

    push(p, result);
    return VM_OK;
}

vm_errors OP_LT(stack *p) { 
    if (p->sp < 2) return VM_ERR_STACK_UNDERFLOW;
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return VM_ERR_STACK_UNDERFLOW;
    if (pop(p, &val_2)) return VM_ERR_STACK_UNDERFLOW;

    if (val_2 < val_1) result = 1;
    else result = 0;

    push(p, result);
    return VM_OK;
}

vm_errors OP_JNZ(stack *p, size_t *ip, size_t limit ,size_t target) {
    if (target >= limit)  return VM_ERR_INVALID_JUMP;
    int32_t value;

    if (pop(p, &value)) return VM_ERR_STACK_UNDERFLOW; 

    if (value != 0) {
        if (target >= limit) return VM_ERR_INVALID_JUMP;
        // printf("JZ to %zu\n", target);
        *ip = target;
    } else {
        *ip += 3;  
    }

    return VM_OK;
}