// Factorial of 5
// Computes 5! = 120

START:
    // n = 5
    PUSH 5
    STORE 0        // memory[0] = n

    // result = 1
    PUSH 1
    STORE 1        // memory[1] = result

FACTORIAL:
    // if n == 0 goto END
    LOAD 0         // push n
    PUSH 0
    EQ             // push (n == 0)
    JNZ END         // consumes condition

    // result = result * n
    LOAD 1         // push result
    LOAD 0         // push n
    MUL
    STORE 1

    // n = n - 1
    LOAD 0
    PUSH 1
    SUB
    STORE 0

    JMP FACTORIAL

END:
    LOAD 1
    PRINT
    HALT
