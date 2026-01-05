#include "errors.h"

const char *vm_error_string(vm_errors err) {
    switch (err) {
        case VM_OK: return "ok";
        case VM_ERR_OUT_OF_MEMORY: return "ERROR: couldn't initialize memory";
        case VM_ERR_STACK_OVERFLOW: return "ERROR: stack overflow";
        case VM_ERR_STACK_UNDERFLOW: return "ERROR: stack underflow";
        case VM_ERR_INVALID_OPCODE: return "ERROR: invalid opcode";
        case VM_ERR_INVALID_JUMP: return "ERROR: invalid jump";
        case VM_ERR_DIV_BY_ZERO: return "ERROR: division by zero";
        case VM_ERR_OUT_OF_BOUNDS: return "ERROR: out of bounds access";
        case VM_ERR_EXEC_LIMIT: return "ERROR: execution limit exceeded";
        case VM_ERR_MISSING_HALT: return "ERROR: missing HALT instruction";
        default: return "ERROR: unknown error";
    }
}