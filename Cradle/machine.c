#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define EXEC_LIMIT 100 //inclater
#define MEM_SIZE 256 //inc later

#define REQUIRED(n) \
if (ip + n > limit) { \
    printf("ERROR: no enough bytecode at ip:%d \n", ip); \
    return 8; \
}

typedef enum {
    HALT = 255,
    NOP = 0,
    PUSH = 1,
    POP = 2,
    ADD = 3,
    SUB = 4,
    MUL = 5,
    DIV = 6,
    DUP = 7,
    JMP = 8,
    JZ = 9,
    PRINT = 10,
    LOAD = 11,
    STORE = 12,
} inst;

typedef struct stack {
    int32_t *data;
    size_t cap;
    size_t sp;
} stack;

int OP_READ(stack *p, int32_t *memory, unsigned char *code, size_t limit);
int stack_init(stack *pm, size_t cap);

int stackoverflow(stack *pm);
int stackunderflow(stack *pm);

int push(stack *pm, int32_t push_value);
int pop(stack *pm, int32_t *pop_value);

int OP_POP(stack *p);
int OP_ADD(stack *p);
int OP_SUB(stack *p);
int OP_MUL(stack *p);
int OP_DIV(stack *p);
int OP_DUP(stack *pm);
int OP_JMP(size_t *ip, size_t limit ,size_t target);
int OP_JZ(stack *p, size_t *ip, size_t limit ,size_t target);
int OP_PRINT(stack *p);
int OP_LOAD(stack *p, int32_t *mem, int32_t index);
int OP_STORE(stack *p, int32_t *mem, int32_t index);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <bytecode_file>\n", argv[0]);
        return 1;
    }

    FILE *file;
    stack pmem;
    int32_t *memory = malloc(MEM_SIZE * sizeof(int32_t));
    if (!memory) return 1;
    memset(memory, 0, MEM_SIZE * sizeof(int32_t));

    file = fopen(argv[1],"rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
   
    unsigned char *buffer = malloc(size);
    if (!buffer) return 1;

    size_t read = fread(buffer, 1, size, file); 
    fclose(file);

    if (read != size) {
        printf("ERROR while reading the file");
        return 2;
    }

    if (stack_init(&pmem, 4)) {
        printf("stack init failed\n");
        return 1;
    }

    OP_READ(&pmem, memory, buffer, size); 

    free(buffer);
    free(pmem.data);
    free(memory);
}

int stack_init(stack *pm, size_t cap) {
    pm->cap = cap;
    pm->sp = 0;
    pm->data = malloc(sizeof(int32_t) * pm->cap);
    if (!pm->data) return 3;
    return 0;
}

int OP_READ(stack *p, int32_t *memory, unsigned char *code, size_t limit) {
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
                REQUIRED(2);
                if(push(p, code[ip + 1])) return 4;
                ip+=2;
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
                REQUIRED(2);
                if (OP_JMP(&ip, limit, code[ip + 1])) return 10;
                break;
            
            case JZ:
                REQUIRED(2);
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

            case HALT:
                REQUIRED(1);
                return 0;

            default:
                printf("ERROR: unidentfied byte at %d\n", ip);
                return 404;
        }
    }

    printf("missing HALT\n");
    return 6;
}

int stackoverflow(stack *pm) {
    if (pm->cap == pm->sp) {
        int *tmp = realloc(pm->data, sizeof(int32_t) * pm->cap * 2);
        if (tmp == NULL) {
            printf("couldnt allocate more memory");
            return 4;
        }
        pm->cap = pm->cap * 2;
        pm->data = tmp;
    }
    return 0;
}

int stackunderflow(stack *pm) {
    if (pm->sp <= 0) {
        printf("trying to access memory that is not avalible\n");
        pm->sp = 0;
        return 5;
    }
    return 0;
}

int push(stack *pm, int32_t push_value) {
    if (stackoverflow(pm)) return 4; 

    pm->data[pm->sp++] = push_value;
    return 0;
}

int pop(stack *pm, int32_t *pop_value) {
    if (stackunderflow(pm)) return 5;

    *pop_value = pm->data[--pm->sp];
    return 0;
}

int OP_POP(stack *p) {
    int32_t trash;
    return pop(p, &trash);
}

int OP_ADD(stack *p) {
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    int32_t result = val_1 + val_2;
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
    int32_t val_1, val_2;

    if (pop(p, &val_1)) return 5;
    if (pop(p, &val_2)) return 5;

    //printf("val_1 = %d, val_2 = %d\n", val_1, val_2);

    int32_t result = val_2 / val_1;
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

int OP_LOAD(stack *p, int32_t *mem, int32_t index) {
    //check if mem is out of bounds
    if (index >= MEM_SIZE) return 5;
    push(p, mem[index]);
    return 0;
}

int OP_STORE(stack *p, int32_t *mem, int32_t index) {
    if (index >= MEM_SIZE) return 5;
    int32_t value;
    pop(p, &value);
    mem[index] = value;
    return 0;                                                                                           
}