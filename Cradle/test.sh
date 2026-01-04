#!/bin/bash

ASM="./asm/assembler.py"
EXEC="./builds/machine"
TEST_DIR="./tests/asm"

if [ ! -f "$EXEC" ]; then
    echo "VM not found. Please build first."
    exit 1
fi

for file in "$TEST_DIR"/*.s; do
    name=$(basename "$file" .s)
    output="./tests/expected/$name.bin"

    echo "TEST: $name"

    python3 "$ASM" "$file" "$output"
    if [ $? -ne 0 ]; then
        echo "Assembler failed on $name"
        exit 1
    fi

    "$EXEC" "$output"
    if [ $? -ne 0 ]; then
        echo "Runtime failure on $name"
        exit 1
    fi
done

echo "All tests passed."