#!/bin/bash

BINARY=""

[ -f "build/solve" ] && BINARY="build/solve"
[ -f "build/greedy" ] && BINARY="build/greedy"
[ -f "build/osx-x64-ninja-debug/solve" ] && BINARY="build/osx-x64-ninja-debug/solve"
[ -f "build/osx-x64-ninja-debug/solve" ] && BINARY="build/osx-x64-ninja-debug/greedy"

[ -f "build/score" ] && SCORE="build/score"
[ -f "build/osx-x64-ninja-debug/score" ] && SCORE="build/osx-x64-ninja-debug/score"

[ -f "${BINARY}" ] || echo "No binary found"
[ -f "${BINARY}" ] || exit 1

echo "Using binary: ${BINARY} and ${SCORE}"

mkdir -p output

for f in input/*.txt; do
    echo "----- Checking ${f} -----"

    "${BINARY}" < "${f}" > "output/$(basename ${f})"
    echo -n "  Score: "
    cat "output/$(basename ${f})" | "${SCORE}" "${f}" | tail -n 1 | cut -d ' ' -f 2
done
