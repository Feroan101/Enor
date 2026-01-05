#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H 

#include "stack.h"
#include "errors.h"
#include <stdio.h>
#include <stdint.h>

vm_errors OP_POP(stack *p);
vm_errors OP_ADD(stack *p);
vm_errors OP_SUB(stack *p);
vm_errors OP_MUL(stack *p);
vm_errors OP_DIV(stack *p);
vm_errors OP_DUP(stack *pm);
vm_errors OP_JMP(size_t *ip, size_t limit ,size_t target);
vm_errors OP_JZ(stack *p, size_t *ip, size_t limit ,size_t target);
vm_errors OP_PRINT(stack *p);

vm_errors OP_SWAP(stack *p);
vm_errors OP_EQ(stack *p);
vm_errors OP_LT(stack *p);
vm_errors OP_JNZ(stack *p, size_t *ip, size_t limit ,size_t target);

#endif