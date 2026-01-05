#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    VM_OK = 0,

    VM_ERR_OUT_OF_MEMORY,

    VM_ERR_STACK_OVERFLOW,
    VM_ERR_STACK_UNDERFLOW,

    VM_ERR_INVALID_OPCODE,
    VM_ERR_INVALID_JUMP,
    VM_ERR_DIV_BY_ZERO,

    VM_ERR_OUT_OF_BOUNDS,
    VM_ERR_EXEC_LIMIT,

    VM_ERR_MISSING_HALT

} vm_errors;

const char *vm_error_string(vm_errors err);

#endif