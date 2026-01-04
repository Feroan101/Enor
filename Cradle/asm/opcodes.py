opcodes = {
    "HALT": { "opcode": 0xFF, "operands": 0},
    "NOP":  { "opcode": 0x00, "operands": 0}, 
    "PUSH": { "opcode": 0x01, "operands": 1}, 
    "POP":  { "opcode": 0x02, "operands": 0}, 
    "ADD":  { "opcode": 0x03, "operands": 0}, 
    "SUB":  { "opcode": 0x04, "operands": 0}, 
    "MUL":  { "opcode": 0x05, "operands": 0}, 
    "DIV":  { "opcode": 0x06, "operands": 0}, 
    "DUP":  { "opcode": 0x07, "operands": 0}, 
    "JMP":  { "opcode": 0x08, "operands": 1}, 
    "JZ":   { "opcode": 0x09, "operands": 1}, 
    "PRINT":{ "opcode": 0x0A, "operands": 0}, 
    "LOAD": { "opcode": 0x0B, "operands": 1},
    "STORE":{ "opcode": 0x0C, "operands": 1},
    "SWAP": { "opcode": 0x0D, "operands": 0},
    "EQ":   { "opcode": 0x0E, "operands": 0},
    "LT":   { "opcode": 0x0F, "operands": 0}
}