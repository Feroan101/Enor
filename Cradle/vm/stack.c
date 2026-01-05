#include "stack.h"


vm_errors stack_init(stack *pm, size_t cap) {
    pm->cap = cap;
    pm->sp = 0;
    pm->data = malloc(sizeof(int32_t) * pm->cap);
    if (!pm->data) return VM_ERR_OUT_OF_MEMORY;
    return VM_OK;
}

vm_errors stackoverflow(stack *pm) {
    if (pm->cap == pm->sp) {
        int32_t *tmp = realloc(pm->data, sizeof(int32_t) * pm->cap * 2);
        if (tmp == NULL) {
            return VM_ERR_STACK_OVERFLOW;
        }
        pm->cap = pm->cap * 2;
        pm->data = tmp;
    }
    return VM_OK;
}

vm_errors stackunderflow(stack *pm) {
    if (pm->sp <= 0) {
        pm->sp = 0;
        return VM_ERR_STACK_UNDERFLOW;
    }
    return VM_OK;
}

vm_errors push(stack *pm, int32_t push_value) {
    if (stackoverflow(pm)) return VM_ERR_STACK_OVERFLOW; 
    pm->data[pm->sp++] = push_value;
    return VM_OK;
}

vm_errors pop(stack *pm, int32_t *pop_value) {
    if (stackunderflow(pm)) return VM_ERR_STACK_UNDERFLOW;

    *pop_value = pm->data[--pm->sp];
    return VM_OK;
}
