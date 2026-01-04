# Execution Model

This document describes how the Cradle virtual machine executes bytecode.

Cradle follows a simple and deterministic execution model. There is no hidden state and no instruction reordering. What happens during execution is fully defined by the bytecode and the rules below.

---

## Program Start

Execution begins at the first byte of the bytecode stream.

The instruction pointer (IP) is initialized to the start of the program.
The operand stack is empty.

---

## Instruction Pointer

Cradle uses a single instruction pointer (IP).

- The IP refers to a byte offset in the bytecode
- Instructions are fetched starting at the current IP
- After an instruction is executed, the IP advances to the next instruction

The IP always moves forward unless explicitly modified by a control-flow instruction.

---

## Operand Stack

Cradle uses a single stack to store operands and intermediate values.

- The stack operates in last-in, first-out order
- Instructions may push values onto the stack
- Instructions may pop values from the stack
- Some instructions consume values and produce results

If an instruction requires more values than are available on the stack, execution fails with an error.

---

## Execution Cycle

Cradle executes programs using a fetch–decode–execute loop.

For each step:
1. Fetch the opcode at the current IP
2. Decode the instruction and its operands
3. Execute the instruction
4. Advance the IP

This process repeats until execution is halted or an error occurs.

---

## Halting

Execution stops when a HALT instruction is encountered.

After HALT:
- No further instructions are executed
- The VM terminates cleanly

Any instructions after HALT are ignored.

---

## Errors

Cradle is strict about invalid execution states.

Execution fails if:
- An unknown opcode is encountered
- The stack underflows
- An instruction reads beyond the bytecode bounds
- An instruction is malformed

On error, execution stops immediately.

Cradle does not attempt to recover from errors.

---

## Determinism

Given the same bytecode, Cradle will always produce the same result.

There is no randomness, concurrency, or external state involved in execution.
