#!/bin/bash

TESTING=0   # set to 1 for test mode (never set it to 1, use ./test.sh) [REMOVE LATER]

if [ $# -lt 1 ]; then
    echo "Usage: $0 <program_name>"
    exit 1
fi

PROGRAM="$1"
EXEC="./builds/machine"
ASM="./asm/assembler.py"
OUT="./builds"

if [ "$TESTING" -eq 1 ]; then
    SRC_DIR="./tests"
    echo "[WARNING] TEST MODE ENABLED"
else
    SRC_DIR="./programs"
fi

INPUT="$SRC_DIR/$PROGRAM.asm"
OUTPUT="./builds/$PROGRAM.bin"

if [ ! -f "$EXEC" ]; then
    echo "VM not found. Please build first."
    exit 1
fi

if [ ! -f "$INPUT" ]; then
    echo "Source '$INPUT' not found."
    exit 1
fi

mkdir -p builds

python3 "$ASM" "$INPUT" "$OUTPUT"
if [ $? -ne 0 ]; then
    echo "Assembler failed"
    exit 1
fi

echo "Running $PROGRAM on Cradle..."
"$EXEC" "$OUT/$PROGRAM.bin"