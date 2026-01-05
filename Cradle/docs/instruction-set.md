# Instruction Set

This document defines the instruction set supported by the Cradle virtual machine.
Cradle is a stack-based VM. All instructions operate on the operand stack and the
instruction pointer (IP).

---

## Instruction Reference

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| NOP | `0x00` | None | 1 | None | No operation. Advances IP by 1 without changing state. |
| HALT | `0xFF` | None | 1 | None | Terminates program execution immediately. |

---

## Stack Operations

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| PUSH | `0x01` | 2 bytes (value) | 3 | None | Pushes immediate value onto the stack. |
| POP | `0x02` | None | 1 | Stack size ≥ 1 | Pops top value from the stack. |
| DUP | `0x07` | None | 1 | Stack size ≥ 1 | Duplicates the top stack value. |

---

## Arithmetic Operations

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| ADD | `0x03` | None | 1 | Stack size ≥ 2 | Pops two values, pushes `val_1 + val_2`. |
| SUB | `0x04` | None | 1 | Stack size ≥ 2 | Pops two values, pushes `val_1 - val_2`. |
| MUL | `0x05` | None | 1 | Stack size ≥ 2 | Pops two values, pushes `val_1 * val_2`. |
| DIV | `0x06` | None | 1 | Stack size ≥ 2, `val_1 != 0` | Pops two values, pushes `val_1 / val_2`. |

---

## Control Flow

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| JMP | `0x08` | 2 bytes (target) | 3 | `0 < target ≤ limit` | Sets IP to target byte offset. |
| JZ | `0x09` | 2 bytes (target) | 3 | `0 < target ≤ limit` | Jumps to target if top of stack is zero. |
| JNZ | `0x10` | 2 bytes (target) | 3 | `0 < target ≤ limit` | Jumps to target if top of stack is non-zero. |

---

## I/O Operations

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| PRINT | `0x0A` | None | 1 | Stack size ≥ 1 | Pops value and prints it. |

---

## Memory Operations

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| LOAD | `0x0B` | 2 bytes (index) | 3 | `index < MEM_SIZE` | Pushes `memory[index]` onto the stack. |
| STORE | `0x0C` | 2 bytes (index) | 3 | Stack size ≥ 1, `index < MEM_SIZE` | Pops value and stores it at `memory[index]`. |

---

## Comparison Operations

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| EQ | `0x0E` | None | 1 | Stack size ≥ 2 | Pushes `1` if values are equal, else `0`. |
| LT | `0x0F` | None | 1 | Stack size ≥ 2 | Pushes `1` if `top < top-1`, else `0`. |

---

## Stack Manipulation

| Mnemonic | Opcode | Immediate Operands | Size (bytes) | Requirements | Effect |
|--------|--------|--------------------|--------------|--------------|--------|
| SWAP | `0x0D` | None | 1 | Stack size ≥ 2 | Swaps the top two stack values. |
