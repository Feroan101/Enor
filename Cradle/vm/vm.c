#include <string.h>
#include <stdlib.h>
#include "vm.h"
#include "stack.h"
#include "memory.h"
#include "instructions.h"
#include "opcodes.h"

#define EXEC_LIMIT 100 //inc later

#define REQUIRED(n) \
if (ip + n > limit) { \
    printf("ERROR: no enough bytecode at ip:%zu \n", ip); \
    return 8; \
}

static int vm_execute(stack *p, int32_t *memory, uint8_t *code, size_t limit);

int vm_run(uint8_t *code, size_t size) {
    stack s;
    int32_t memory[MEM_SIZE];

    memset(memory, 0, sizeof(memory));

    if (stack_init(&s, 4)) return 1;

    int rc = vm_execute(&s, memory, code, size);

    free(s.data);
    return rc;
}

static int vm_execute(stack *p, int32_t *memory, uint8_t *code, size_t limit) {
    size_t ip = 0;
    int32_t exec_count = 0;

    while (ip < limit) {
        if (++exec_count > EXEC_LIMIT) {
            printf("ERROR: execution limit exceeded\n");
            return 200;
        }

        switch(code[ip]) {
            case NOP:
                REQUIRED(1);
                ip++;
                break;

            case PUSH:
                REQUIRED(3);
                 int16_t val = code[ip + 1] | (code[ip + 2] << 8); // little endian
                if(push(p, (int32_t)val)) return 4;
                ip += 3;
                break;
            
            case POP:
                REQUIRED(1);
                if(OP_POP(p)) return 5;
                ip += 1;
                break;

            case ADD:
                REQUIRED(1);
                if (OP_ADD(p)) return 5;
                ip++;
                break;

            case SUB:
                REQUIRED(1);
                if (OP_SUB(p)) return 5;
                ip++;
                break;

            case MUL:
                REQUIRED(1);
                if (OP_MUL(p)) return 5;
                ip++;
                break;

            case DIV:
                REQUIRED(1);
                if (OP_DIV(p)) return 5;
                ip++;
                break;
            
            case DUP:
                REQUIRED(1);
                if(OP_DUP(p)) return 9;
                ip++;
                break;
            
            case JMP:
                REQUIRED(3);
                if (OP_JMP(&ip, limit, code[ip + 1])) return 10;
                break;
            
            case JZ:
                REQUIRED(3);
                if (OP_JZ(p ,&ip, limit, code[ip + 1])) return 11;
                break;

            case PRINT:
                REQUIRED(1);
                if (OP_PRINT(p)) return 5;
                ip++;
                break;

            case LOAD:
                REQUIRED(2);
                if (OP_LOAD(p, memory, code[ip + 1])) return 5;
                ip += 2;
                break;

            case STORE:
                REQUIRED(2);
                if (OP_STORE(p, memory, code[ip + 1])) return 5;
                ip += 2;
                break;

            case SWAP:
                REQUIRED(1);
                if (OP_SWAP(p)) return 5;
                ip++;
                break;
            
            case EQ:
                REQUIRED(1);
                if (OP_EQ(p)) return 5;
                ip++;
                break;
            
            case LT:
                REQUIRED(1);
                if (OP_LT(p)) return 5;
                ip++;
                break;

            case HALT:
                REQUIRED(1);
                return 0;

            default:
                printf("ERROR: unidentfied byte at %zu\n", ip);
                return 404;
        }
    }

    printf("missing HALT\n");
    return 6;
}