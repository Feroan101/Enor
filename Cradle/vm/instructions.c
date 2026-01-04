#include "instructions.h"
#include "stack.h"
#include <stdio.h>


int OP_POP(stack *p) {
    int32_t trash;
    return pop(p, &trash);
}

int OP_ADD(stack *p) {
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    result = val_1 + val_2;
    push(p, result);
    return 0;
}

int OP_SUB(stack *p) {
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    int32_t result = val_2 - val_1;
    push(p, result);
    return 0;
}

int OP_MUL(stack *p) {
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    int32_t result = val_1 * val_2;
    push(p, result);
    return 0;
}

int OP_DIV(stack *p) {
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);
    if (val_2 == 0) return 12;

    if (val_1 == 0) result = val_2;
    else result = val_2 / val_1;
    push(p, result);
    return 0;
}

int OP_DUP(stack *pm) {
    if (pm->sp < 1) return 5;
    if (stackoverflow(pm)) return 4;

    pm->data[pm->sp] = pm->data[pm->sp - 1];
    pm->sp++;
    return 0;
}

int OP_JMP(size_t *ip, size_t limit ,size_t target) {
    if (target >= limit) return 4;

    //printf("JMP to %d\n", target);
    *ip = target;
    return 0;
}

int OP_JZ(stack *p, size_t *ip, size_t limit ,size_t target) {
    if (target >= limit)  return 4;
    int32_t value;

    if (pop(p, &value)) return 5;
    if (value != 0) {
        *ip += 2;
    } 
    else {
        //printf("JMP to %d\n", target);
        *ip = target;
    }
    return 0;
}

int OP_PRINT(stack *p) {
    int32_t value;
    if (pop(p, &value)) return 5;
    printf("%d\n", value);
    return 0;
}

int OP_SWAP(stack *p) {
    if (p->sp < 2) return 5;
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    push(p, val_1);
    push(p, val_2);
    return 0;
}

int OP_EQ(stack *p) {
    if (p->sp < 2) return 5;
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    if (val_1 == val_2) result = 1;
    else result = 0;

    push(p, result);
    return 0;
}

int OP_LT(stack *p) { 
    if (p->sp < 2) return 5;
    int32_t val_1, val_2, result;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    if (val_2 < val_1) result = 1;
    else result = 0;

    push(p, result);
    return 0;
}