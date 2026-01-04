# Cradle Assembler

The Cradle assembler is the tool that converts Enor source code into Cradle VM bytecode. It reads `.asm` files containing human-readable instructions and produces a binary bytecode file that the VM can execute.

---

## Overview

- Input: Enor assembly file (`.asm`) containing instructions like `PUSH 3`, `ADD`, `JMP 0x10`  
- Output: Binary bytecode file (`.bin`) ready to run on the Cradle VM  
- The assembler resolves **opcodes**, **immediate operands**, and **labels** (if present) into proper byte sequences.  
- All multi-byte operands are encoded in **little-endian** format.  
- The assembler checks for syntax errors, invalid instructions, and stack-related issues if possible.

---

## Assembly Syntax

- **Instructions**: one per line  
- **Operands**: follow the instruction, separated by spaces  
- **Comments**: start with `//` and extend to the end of the line  
- **Labels**: optional, defined by `label_name:` and used as jump targets  

Example:

```
start:
PUSH 5 ; push 5 onto stack
PUSH 10
ADD
PRINT
HALT
```

---

## How the Assembler Works

1. **Parsing**: Reads each line of assembly and splits it into instruction and operands.  
2. **Opcode Resolution**: Maps the instruction mnemonic to its 1-byte opcode.  
3. **Immediate Encoding**: Converts operands into the correct binary format (3-byte values for `PUSH`, 2-byte addresses for jumps and memory operations).  
4. **Label Resolution**: Tracks label positions and replaces label references in jump instructions with the correct byte offset.  
5. **Bytecode Emission**: Writes opcode and immediate operands sequentially into the output file.  
6. **Error Checking**: Ensures instructions are valid, operand sizes match, and jump targets exist within the bytecode limit.

---

## Example Assembly → Bytecode

Assembly:

```
start:
PUSH 2
PUSH 3
ADD
PRINT
HALT
```

Assembler Output (hex bytecode):

```
01 02 00 // PUSH 2
01 03 00 // PUSH 3
03 // ADD
0A // PRINT
FF // HALT
```

Labels like `start:` are replaced with their **absolute byte offsets** during assembly.

---

## Notes

- Multi-pass assembly may be used to resolve labels before final bytecode emission.  
- All operands must be within the allowed ranges (e.g., memory indices < MEM_SIZE, JMP targets within program size).  
- The assembler only produces **raw bytecode**; it does not execute programs. Execution is handled by the Cradle VM.  
- Any syntax or operand errors prevent bytecode generation and are reported to the user.  
