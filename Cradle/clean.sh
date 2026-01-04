#!/bin/bash

echo "Cleaning build artifacts..."

rm -f ./builds/*.bin
rm -f ./builds/machine
rm -f ./tests/bin/*.bin

echo "Clean complete."
