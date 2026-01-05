# Execution Model

This document describes implementation details of Cradle. It is not a user-facing specification.

This file explains how Cradle executes bytecode at runtime.
It focuses on the execution loop, instruction behavior, and the invariants the VM relies on to stay correct.

## Execution Loop

Cradle executes bytecode using a single, linear fetch–decode–execute loop.

The instruction pointer (ip) is a byte offset into the bytecode buffer.
Execution begins at ip = 0.

On each iteration:
- The opcode is read from code[ip]
- The opcode determines how many immediate bytes are consumed
- The instruction performs its operation
- ip is updated explicitly by the instruction

The VM is byte-addressed, not instruction-addressed.
All jumps, bounds checks, and limits are expressed in bytes.

The execution loop does not attempt recovery.
Any error immediately aborts execution and is returned to the caller.

## Instruction Semantics

Each opcode maps to exactly one instruction with well-defined behavior.

Instructions:
- Operate on the stack, arena memory, or instruction pointer
- Read immediate operands directly from the bytecode stream
- Never allocate memory
- Either succeed fully or return an error

Instruction handlers are expected to:
- Validate preconditions
- Perform exactly one logical operation
- Return a vm_errors value

No instruction prints, logs, or exits the process.

## Termination Rules

Execution stops when one of the following occurs:
- A HALT instruction is encountered
- An unrecoverable error is returned
- The execution limit is exceeded

If execution reaches the end of the bytecode without HALT, this is treated as an error.

An execution limit (EXEC_LIMIT) exists to prevent infinite loops during development.
It is not a correctness feature and may change or be removed later.

## Control Flow

Cradle supports explicit control flow via jump instructions.

- JMP performs an unconditional jump
- JZ performs a conditional jump based on the stack top

All jumps use absolute byte offsets.

Relative jumps were intentionally avoided to:
- Simplify the assembler
- Make debugging easier
- Keep bytecode inspection predictable

Jump targets must point to a valid opcode boundary.
Invalid targets result in an execution error.

## Invariants

The VM relies on the following invariants at all times:

- ip always points to the start of an instruction
- The stack is valid before and after every instruction
- Bytecode is treated as read-only
- No instruction mutates global VM state directly
- Errors are propagated upward and never swallowed

Violating any of these invariants is considered a VM bug, not a user error.
