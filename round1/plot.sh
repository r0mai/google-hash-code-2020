#!/usr/bin/env bash

[ -f "build/solve" ] && BINARY="build/solve"
[ -f "build/greedy" ] && BINARY="build/greedy"
[ -f "build/osx-x64-ninja-debug/solve" ] && BINARY="build/osx-x64-ninja-debug/solve"
[ -f "build/osx-x64-ninja-debug/solve" ] && BINARY="build/osx-x64-ninja-debug/greedy"

[ -f "build/score" ] && SCORE="build/score"
[ -f "build/osx-x64-ninja-debug/score" ] && SCORE="build/osx-x64-ninja-debug/score"

for f in input/*.txt; do
	cat "${f}" | ${BINARY} | ${SCORE} "${f}" | gnuplot -p -e 'set terminal pdfcairo; plot "-" using 1:2 notitle' > ${f}.pdf
done
