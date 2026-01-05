# Error Model

This document describes implementation details of Cradle. It is not a user-facing specification.

This file explains how errors are represented, propagated, and reported inside the Cradle VM.
The goal of the error model is to make failures explicit, predictable, and easy to reason about.

## Error Philosophy

Errors in Cradle are values, not side effects.

The VM does not:
- Exit the process
- Print errors automatically
- Attempt recovery after failure

Instead, every failure is represented explicitly using a vm_errors value and returned upward.
Once an error occurs, execution stops immediately.

This design keeps control flow simple and prevents hidden state corruption.

## vm_errors Enum

All VM errors are represented using the vm_errors enum.

- VM_OK represents successful execution
- Any other value represents a specific failure condition

Errors are categorized conceptually into:
- Stack errors (overflow, underflow)
- Memory or arena errors (out of bounds access)
- Execution errors (invalid jump, missing HALT)
- Internal VM errors

The enum exists to describe what went wrong, not how it should be handled.

## Error Propagation

Errors propagate in a straight line upward.

The flow is:
- Opcode handler returns vm_errors
- Execution loop checks the return value
- vm_run returns the error to the caller

No opcode handler attempts to recover from errors.
No opcode handler prints error messages.
No opcode handler modifies global state after an error.

The first error encountered always wins.

## Reporting

Error reporting is the responsibility of the top-level caller.

The VM provides:
- vm_errors values
- A function to convert errors into human-readable strings

Printing errors is optional and external to the VM.
When printed, errors should be sent to stderr, not stdout.

This separation allows Cradle to be embedded, tested, or driven by other tools without forced output.

## Design Constraints

The error model follows these strict constraints:

- One instruction produces at most one error
- Errors are never ignored
- Errors are never stored globally
- Errors do not accumulate or stack
- No instruction continues execution after an error

Any violation of these rules is considered a VM implementation bug.

The error system is intentionally simple.
Complexity is pushed outward to callers, not inward into the VM core.
