#ifndef VM_H
#define VM_H

#include <stdint.h>
#include <stddef.h>
#include "errors.h"

vm_errors vm_run(uint8_t *code, size_t size);

#endif
