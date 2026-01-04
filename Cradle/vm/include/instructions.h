#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H 

#include "stack.h"
#include <stddef.h>
#include <stdint.h>

int OP_POP(stack *p);
int OP_ADD(stack *p);
int OP_SUB(stack *p);
int OP_MUL(stack *p);
int OP_DIV(stack *p);
int OP_DUP(stack *pm);
int OP_JMP(size_t *ip, size_t limit ,size_t target);
int OP_JZ(stack *p, size_t *ip, size_t limit ,size_t target);
int OP_PRINT(stack *p);

int OP_SWAP(stack *p);
int OP_EQ(stack *p);
int OP_LT(stack *p);

#endif