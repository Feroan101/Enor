// Factorial of 5
// Computes 5! = 120

START:
    // initialize n = 5
    PUSH 5
    STORE 0       // memory[0] = n

    // initialize result = 1
    PUSH 1
    STORE 1       // memory[1] = result

FACTORIAL:
    // load n
    LOAD 0
    PUSH 0
    EQ
    JZ END        // if n == 0, jump to END

    // multiply result *= n
    LOAD 1
    LOAD 0
    MUL
    STORE 1       // store result

    // decrement n
    LOAD 0
    PUSH 1
    SUB
    STORE 0

    JMP FACTORIAL

END:
    // print result
    LOAD 1
    PRINT
    HALT
