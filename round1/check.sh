#!/bin/bash

BINARY=""

[ -f "build/solve" ] && BINARY="build/solve"
[ -f "build/osx-x64-ninja-debug/solve" ] && BINARY="build/osx-x64-ninja-debug/solve"

[ -f "${BINARY}" ] || echo "No binary found"
[ -f "${BINARY}" ] || exit 1

echo "Using binary: ${BINARY}"

for f in input/*.txt; do
    echo "----- Checking ${f} -----"

    "${BINARY}" < "${f}" > "output/$(basename ${f})"
done
