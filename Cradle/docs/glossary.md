# Cradle Glossary

This glossary defines the key terms and concepts used in Cradle VM and the Enor language.  

---

## Terms

**Enor**  
The low-level language you write that runs on the Cradle VM. Programs are written in human-readable assembly and then assembled into bytecode.

**Cradle VM**  
The virtual machine that executes Enor bytecode. It reads instructions sequentially from memory, manages a stack, memory, and the instruction pointer (IP).

**Bytecode**  
The binary representation of Enor programs that Cradle VM can execute. Each instruction is a 1-byte opcode followed by optional immediate operands.

**Opcode**  
A 1-byte value representing an instruction in bytecode. For example, `0x01` for `PUSH`, `0x03` for `ADD`.

**Immediate Operand**  
Data that follows an opcode in bytecode. Examples: numbers for `PUSH`, memory addresses for `LOAD`/`STORE`, or jump offsets for `JMP`/`JZ`.  

**Instruction Pointer (IP)**  
A pointer that tracks the current byte in the bytecode being executed. Normally increments after each instruction unless changed by jumps.

**Stack**  
A LIFO (last-in, first-out) data structure used by the VM for calculations and temporary storage. Instructions like `PUSH`, `POP`, `ADD` interact with it.

**Memory**  
A fixed-size array in the VM that can be read or written using `LOAD` and `STORE`.

**Label**  
A symbolic name in assembly code representing a bytecode offset, usually used for jump targets.

**Assembler**  
The tool that converts Enor assembly code into Cradle bytecode. It resolves opcodes, operands, and labels.

**Instruction Set**  
The collection of all instructions the VM can execute, along with their opcode, operands, size, and effect.

**Little-endian**  
A way of encoding multi-byte numbers where the least significant byte comes first in memory.

**NOP**  
“No Operation” instruction. Does nothing except advance the IP by 1 byte.

**HALT**  
Instruction that stops execution immediately.

**IP Offset**  
The number of bytes the instruction pointer moves after executing an instruction. Depends on the instruction size.

---

## Notes

- The glossary focuses on terms directly relevant to Cradle VM and Enor.  
- Understanding these terms will help you read the assembler, bytecode, and instruction set documentation more easily.  
