# Enor

Enor is a small, *low-level programming language*.  
It's designed to be explicit, simple, and easy to reason about — and it runs on its own virtual machine called **Cradle**.  

> ⚠️ Enor is still in development. Things will change as the language matures.

---

## Cradle

Cradle is the *virtual machine* that executes Enor programs.  
It defines the runtime environment, handles bytecode execution, and even comes with a built-in assembler for turning Enor source into bytecode.  

You can think of it as the backbone of Enor: without Cradle, the language doesn’t do much.  

### Using Cradle

Clone the repository and build the VM using `make`:

```bash
make
```

This produces the `Cradle` executable inside the `build/` folder.

You can then run an ens program in `Cradle/programs` like this:

```bash
make asm PROGRM=<program_name>
```

For development and testing, there’s also:

```bash
make test
```
This runs the included test programs in `Cradle/tests` to verify the VM is behaving as expected.

to clean builds:

```bash
make clean
```
This remove the files in `Cradle/tests/bin` and `Cradle/builds`

For detailed technical documentation on Cradle, including its instruction set, execution model, bytecode format, and assembler, see the [Cradle Overview](Cradle/docs/overview.md)

## Status

- **Enor language** - basic syntax in place, but still under development
- **Cradle VM** - mostly functional, can execute core bytecode, has built-in assembler
- **Compiler** - still in progress
- **Advanced features** - optimizations, extended instructions, and error handling are being worked on
  
> The VM and language are under active development and may change frequently.
