# Cradle Virtual Machine

Cradle is a small, stack-based virtual machine built to execute bytecode generated from the Enor language.

The goal of Cradle is not performance or completeness. It exists to be understandable, predictable, and easy to reason about while learning how virtual machines actually work under the hood.

This VM is intentionally minimal. Every feature is added only when it earns its place.

---

## What Cradle Does

Cradle is responsible for:
- Loading bytecode
- Executing instructions sequentially
- Managing a stack for operands
- Maintaining an instruction pointer
- Halting cleanly or failing loudly

Cradle does **not** parse source code.  
It only understands bytecode.

---

## Design Principles

Cradle is built with a few clear rules:
- Simple over clever
- Explicit over magical
- Easy to debug over fast to run

If something happens during execution, you should be able to explain *why* by looking at the bytecode and the VM rules.

---
 
## What Cradle Is Not

Cradle is not:
- A general-purpose runtime
- A JIT compiler
- A sandbox or secure VM
- A production-grade interpreter

There is no garbage collector, no optimizer, and no hidden state.

---

## Relationship to Enor

Enor is the language.  
Cradle is the machine.

Enor source code is assembled into bytecode.
Cradle executes that bytecode without knowing anything about Enor syntax.

This separation is intentional and enforced.

---

## Assembler

Cradle includes a simple assembler used during development and testing.

The assembler translates Enor assembly files into Cradle bytecode.
It performs a direct, mostly one-to-one translation from instructions
to their binary representation.

The assembler is not part of the runtime execution model.
Cradle itself only executes bytecode.

Implementation details and encoding rules are documented separately.


## Current Status

Cradle is under active development.
The instruction set and execution model may evolve as the VM grows, but changes are kept small and deliberate.

If something exists, it exists for a reason.

## Documentation

- [Execution Model](execution.md)
- [Instruction Set](instruction-set.md)
- [Bytecode Format](bytecode.md)
- [Assembler](assembler.md)
- [Glossary](glossary.md)

Internal design notes and implementation details live in `internal/`