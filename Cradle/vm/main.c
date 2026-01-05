#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "errors.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <bytecode_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("fopen");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *buffer = malloc(size);
    if (!buffer) return 1;

    fread(buffer, 1, size, file);
    fclose(file);

    vm_errors rc = vm_run(buffer, size);
    if (rc) fprintf(stderr, "Cradle %s\n", vm_error_string(rc));

    free(buffer);
    return (int)rc;
}

