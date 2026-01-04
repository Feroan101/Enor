#!/bin/bash
shopt -s nullglob

ASM="./asm/assembler.py"
EXEC="./builds/machine"

PASS_DIR="./tests/asm/pass"
FAIL_DIR="./tests/asm/fail"
BIN_DIR="./tests/bin"

mkdir -p "$BIN_DIR"

failures=0

if [ ! -f "$EXEC" ]; then
    echo "VM not found. Please build first."
    exit 1
fi

echo "===== PASS TESTS ====="

for file in "$PASS_DIR"/*.asm; do
    name=$(basename "$file" .asm)
    output="$BIN_DIR/$name.bin"

    echo "------------------------"
    echo "PASS: $name"

    python3 "$ASM" "$file" "$output"
    asm_rc=$?

    if [ $asm_rc -ne 0 ]; then
        echo "❌ Assembler failed (unexpected)"
        failures=$((failures + 1))
        continue
    fi

    "$EXEC" "$output"
    vm_rc=$?

    if [ $vm_rc -ne 0 ]; then
        echo "❌ Runtime failure"
        failures=$((failures + 1))
        continue
    fi
done

echo
echo "===== FAIL TESTS ====="

for file in "$FAIL_DIR"/*.asm; do
    name=$(basename "$file" .asm)
    output="$BIN_DIR/$name.bin"

    echo "------------------------"
    echo "FAIL: $name"

    python3 "$ASM" "$file" "$output"
    asm_rc=$?

    if [ $asm_rc -eq 0 ]; then
        echo "Assembler succeeded (unexpected)"
        failures=$((failures + 1))
        continue
    fi

    echo "Failed as expected"
done

VM_PASS_DIR="./tests/vm/pass"

echo
echo "===== VM PASS TESTS ====="

for file in "$VM_PASS_DIR"/*.asm; do
    name=$(basename "$file" .asm)
    output="$BIN_DIR/$name.bin"

    echo "------------------------"
    echo "VM PASS: $name"

    python3 "$ASM" "$file" "$output"
    asm_rc=$?

    if [ $asm_rc -ne 0 ]; then
        echo "❌ Assembler failed (unexpected)"
        failures=$((failures + 1))
        continue
    fi

    "$EXEC" "$output"
    vm_rc=$?

    if [ $vm_rc -ne 0 ]; then
        echo "❌ Runtime failed (unexpected)"
        failures=$((failures + 1))
        continue
    fi

    echo "Runtime succeeded as expected"
done

VM_FAIL_DIR="./tests/vm/fail"

echo
echo "===== VM FAIL TESTS ====="

for file in "$VM_FAIL_DIR"/*.asm; do
    name=$(basename "$file" .asm)
    output="$BIN_DIR/$name.bin"

    echo "------------------------"
    echo "VM FAIL: $name"

    python3 "$ASM" "$file" "$output"
    asm_rc=$?

    if [ $asm_rc -ne 0 ]; then
        echo "❌ Assembler failed (unexpected)"
        failures=$((failures + 1))
        continue
    fi

    "$EXEC" "$output"
    vm_rc=$?

    if [ $vm_rc -eq 0 ]; then
        echo "VM succeeded (unexpected)"
        failures=$((failures + 1))
        continue
    fi

    echo
    echo "Runtime failed as expected"
done

if [ $failures -eq 0 ]; then
    echo "All tests behaved as expected."
    exit 0
else

    echo "$failures test(s) failed."
    exit 1
fi
