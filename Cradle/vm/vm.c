#include <string.h>
#include <stdlib.h>
#include "vm.h"
#include "stack.h"
#include "arena.h"
#include "instructions.h"
#include "opcodes.h"

#define EXEC_LIMIT 100 //inc later

#define REQUIRED(n) \
if (ip + n > limit) { \
    return VM_ERR_OUT_OF_BOUNDS; \
}

static vm_errors vm_execute(stack *p, int32_t *memory, uint8_t *code, size_t limit);

vm_errors vm_run(uint8_t *code, size_t size) {
    stack s;
    int32_t memory[MEM_SIZE];

    memset(memory, 0, sizeof(memory));

    if (stack_init(&s, 4)) return 1;

    vm_errors rc = vm_execute(&s, memory, code, size);

    free(s.data);
    return rc;
}

static vm_errors vm_execute(stack *p, int32_t *memory, uint8_t *code, size_t limit) {
    size_t ip = 0;
    int32_t exec_count = 0;
    vm_errors err;

    while (ip < limit) {
        if (++exec_count > EXEC_LIMIT) {
            printf("ERROR: execution limit exceeded\n");
            return VM_ERR_EXEC_LIMIT;
        }

        switch(code[ip]) {
            case NOP:
                REQUIRED(1);
                ip++;
                break;

            case PUSH:
                REQUIRED(3);
                int16_t val = code[ip + 1] | (code[ip + 2] << 8); // little endian
                err = push(p, (int32_t)val);
                if(err) return err;
                ip += 3;
                break;
            
            case POP:
                REQUIRED(1);
                err = OP_POP(p);
                if(err) return err;
                ip += 1;
                break;

            case ADD:
                REQUIRED(1);
                err = OP_ADD(p);
                if (err) return err;
                ip++;
                break;

            case SUB:
                REQUIRED(1);
                err = OP_SUB(p);
                if (err) return err;
                ip++;
                break;

            case MUL:
                REQUIRED(1);
                err = OP_MUL(p);
                if (err) return err;
                ip++;
                break;

            case DIV:
                REQUIRED(1);
                err = OP_DIV(p);
                if (err) return err;
                ip++;
                break;
            
            case DUP:
                REQUIRED(1);
                err = OP_DUP(p);
                if(err) return err;
                ip++;
                break;
            
            case JMP:
                REQUIRED(3);
                err = OP_JMP(limit, code[ip + 1]);
                if (err) return err;
                else ip = code[ip + 1];
                break;
            
            case JZ:
                REQUIRED(3);
                err = OP_JZ(p ,&ip, limit, code[ip + 1]);
                if (err) return err;
                break;

            case PRINT:
                REQUIRED(1);
                err = OP_PRINT(p);
                if (err) return err;
                ip++;
                break;

            case LOAD:
                REQUIRED(2);
                err = OP_LOAD(p, memory, code[ip + 1]);
                if (err) return err;
                ip += 2;
                break;

            case STORE:
                REQUIRED(2);
                err = OP_STORE(p, memory, code[ip + 1]);
                if (err) return err;
                ip += 2;
                break;

            case SWAP:
                REQUIRED(1);
                err = OP_SWAP(p);
                if (err) return err;
                ip++;
                break;
            
            case EQ:
                REQUIRED(1);
                err = OP_EQ(p);
                if (err) return err;
                ip++;
                break;
            
            case LT:
                REQUIRED(1);
                err = OP_LT(p);
                if (err) return err;
                ip++;
                break;

            case HALT:
                REQUIRED(1);
                return VM_OK;

            default:
                return VM_ERR_INVALID_OPCODE;
        }
    }

    return VM_ERR_MISSING_HALT;
}