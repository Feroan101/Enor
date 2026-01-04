#!/bin/bash

BUILD="V0.1"
echo "Build $BUILD - $(date '+%Y-%m-%d %H:%M:%S')"

gcc ./vm/main.c memory.c stack.c vm.c instructions.c -o ./builds/machine
if [ $? -ne 0 ]; then
    echo "VM compilation failed"
    exit 1
fi

VM_SIZE=$(ls -lh ./builds/machine | awk '{print $5}')
echo "VM compiled successfully ($VM_SIZE)"
echo "Build complete"