# Roadmap

This document outlines the intended direction of the Cradle VM and the Enor language.
It reflects current goals and may change as the project evolves.

## Short Term

- Stabilize the instruction set
- Finalize error handling semantics
- Complete and harden the assembler
- Improve internal documentation coverage

Focus at this stage is correctness and clarity.

## Mid Term

- Implement an Enor compiler targeting Cradle bytecode
- Add better diagnostics and error context
- Introduce basic debugging support
- Improve test coverage for edge cases

This phase focuses on usability for developers.

## Long Term

- Bytecode optimizer
- Optional tracing or instrumentation
- Tooling around inspection and debugging
- Cleaner separation between VM core and tooling

These are goals, not guarantees.

## Explicit Non-Goals

The following are intentionally out of scope:

- JIT compilation
- Dynamic memory allocation
- High-level runtime features
- OS-level virtualization

Cradle is intended to remain a small, explicit virtual machine.
