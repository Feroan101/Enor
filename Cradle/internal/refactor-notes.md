# Refactor Notes

This document describes implementation details of Cradle. It is not a user-facing specification.

This file exists to document intentional design decisions, known rough edges, and boundaries
that should not be crossed casually. It is written primarily for maintainers.

## Known Weirdness

Some parts of the codebase may look odd or overly manual at first glance.

Examples include:
- Absolute byte-based jumps instead of relative jumps
- Manual instruction pointer manipulation
- Explicit bounds checks in many instructions
- A hard execution limit during runtime

These are intentional choices made to keep the VM simple, debuggable, and predictable.

## Technical Debt

The following areas are acknowledged technical debt:

- Execution limit is a temporary safety mechanism
- Error messages are minimal and not contextual
- Instruction decoding is tightly coupled to execution
- No formal validation pass before execution

These are postponed intentionally to avoid premature complexity.

## Hard Boundaries

Certain boundaries should not be broken during refactors:

- Opcode handlers must not print or log
- Opcode handlers must not exit the process
- Memory access must remain bounds-checked
- Bytecode must remain read-only during execution

Violating these boundaries risks destabilizing the VM.

## Future Cleanup Candidates

The following areas may be revisited later:

- Separating decode and execute stages
- Improving error diagnostics
- Adding optional debug hooks
- Making execution limits configurable

Any cleanup should preserve existing semantics unless explicitly redesigned.
