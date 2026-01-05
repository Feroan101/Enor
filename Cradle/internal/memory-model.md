# Memory Model

This document describes implementation details of Cradle. It is not a user-facing specification.

This file explains the memory layout used by the Cradle VM and the rules governing access to it.
Cradle intentionally uses a simple, explicit memory model to keep execution predictable.

## Memory Regions

Cradle operates with three distinct memory regions:

- Stack
- Arena
- Bytecode buffer

Each region has a fixed role and strict access rules.
No region overlaps or aliases another.

## Stack

The stack is used for all temporary values and computation.

- Values are pushed and popped explicitly
- All arithmetic and logical operations operate on the stack
- Stack size is fixed at initialization

Stack overflow and underflow are treated as execution errors.
The stack is never resized during execution.

## Arena

The arena is a fixed-size array of 32-bit values.

- Accessed only via LOAD and STORE instructions
- Indexed using immediate operands
- Bounds-checked on every access

The arena does not support allocation, deallocation, or resizing.
It exists solely as a simple, deterministic storage space for programs.

Arena access is explicit and predictable.
Invalid indices result in an execution error.

## Bytecode Buffer

The bytecode buffer is a read-only sequence of bytes.

- Instructions are fetched from this buffer
- Immediate operands are read directly from it
- It is never modified during execution

The instruction pointer always refers to an offset within this buffer.

## LOAD and STORE Semantics

LOAD:
- Reads a value from the arena at a given index
- Pushes the value onto the stack
- Fails if the index is out of bounds or the stack overflows

STORE:
- Pops a value from the stack
- Writes the value to the arena at a given index
- Fails if the index is out of bounds or the stack underflows

Neither instruction performs implicit conversion or allocation.

## What This Is Not

The arena is not a heap.
There is no dynamic memory allocation.
There is no garbage collection.
There are no pointers exposed to the program.

Cradle does not attempt to model a full system memory hierarchy.

## Rationale

The memory model prioritizes simplicity and correctness over flexibility.

A fixed-size arena:
- Makes programs easier to reason about
- Prevents memory leaks
- Keeps the VM implementation small

More complex memory features can be layered later without breaking the core model.
