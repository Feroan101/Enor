#ifndef OPCODE_H
#define OPCODE_H

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
    SWAP = 13,
    EQ = 14,
    LT = 15,
    JNZ = 16
} inst;

#endif