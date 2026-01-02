#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <program.bin>"
    exit 1
fi

PROGRAM="$1"
EXEC="./builds/machine"

if [ ! -f "$EXEC" ]; then
    echo "VM not found. Please build first."
    exit 1
fi

if [ ! -f "./builds/$PROGRAM" ]; then
    echo "Program './builds/$PROGRAM' not found."
    exit 1
fi

echo "Running $PROGRAM on VM..."
"$EXEC" "$PROGRAM"

#useage ./run.sh machine