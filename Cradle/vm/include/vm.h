#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>

int vm_run(uint8_t *code, size_t size);

#endif
