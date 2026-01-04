# Cradle Bytecode Format

Cradle bytecode is the binary representation of Enor programs for the Cradle VM. It is a **sequential, byte-addressed stream of instructions**. The VM reads this bytecode to execute programs.

Each instruction consists of:

- **Opcode** (1 byte)  
- **Optional immediate operands** (size depends on instruction)  

All multi-byte values (immediate values, memory indices, jump targets) are **little-endian**.

The **instruction pointer (IP)** points to the current byte in the bytecode stream. After execution, IP advances according to instruction size, except for jump instructions which set IP directly.

---

## Instruction Encoding

| Instruction | Opcode | Immediate Operand(s) | Total Size | Effect |
|------------|--------|--------------------|------------|--------|
| **NOP** | `0x00` | None | 1 byte | No operation; IP += 1 |
| **HALT** | `0xFF` | None | 1 byte | Ends program execution |
| **PUSH** | `0x01` | 2 bytes (value) | 3 bytes | Push value onto stack; IP += 3 |
| **POP** | `0x02` | None | 1 byte | Pop top value from stack; IP += 1 |
| **ADD** | `0x03` | None | 1 byte | Pop two values, push sum; IP += 1 |
| **SUB** | `0x04` | None | 1 byte | Pop two values, push difference; IP += 1 |
| **MUL** | `0x05` | None | 1 byte | Pop two values, push product; IP += 1 |
| **DIV** | `0x06` | None | 1 byte | Pop two values, push quotient (divisor ≠ 0); IP += 1 |
| **DUP** | `0x07` | None | 1 byte | Duplicate top of stack; IP += 1 |
| **JMP** | `0x08` | 2 bytes (absolute target) | 3 bytes | Set IP = target |
| **JZ** | `0x09` | 2 bytes (absolute target) | 3 bytes | Jump if top of stack is 0; IP = target |
| **PRINT** | `0x0A` | None | 1 byte | Pop value and print; IP += 1 |
| **LOAD** | `0x0B` | 2 bytes (memory index) | 3 bytes | Push memory[index] onto stack; IP += 3 |
| **STORE** | `0x0C` | 2 bytes (memory index) | 3 bytes | Pop value into memory[index]; IP += 3 |
| **SWAP** | `0x0D` | None | 1 byte | Swap top two stack values; IP += 1 |
| **EQ** | `0x0E` | None | 1 byte | Pop two values, push 1 if equal else 0; IP += 1 |
| **LT** | `0x0F` | None | 1 byte | Pop two values, push 1 if top < top-1 else 0; IP += 1 |

---

## Operand Encoding

- **PUSH values:** 2-byte signed integers, little-endian  
- **JMP / JZ targets:** 2-byte unsigned integers, little-endian  
- **LOAD / STORE memory indices:** 2-byte unsigned integers, little-endian  

---

## Example Bytecode

Assembly:
```asm
PUSH 2
PUSH 3
ADD
PRINT
HALT
```

Bytecode (hex representation):
```bin
01 02 00 // PUSH 2
01 03 00 // PUSH 3
03 // ADD
0A // PRINT
FF // HALT
```

This shows how instructions and operands are arranged sequentially in the bytecode.

---

## Notes

- Instructions are executed sequentially; IP moves according to instruction size  
- Jump instructions override IP with the target offset  
- Bytecode after HALT is ignored  
- Malformed bytecode immediately stops execution  
