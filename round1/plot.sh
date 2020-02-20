#!/usr/bin/env bash


for f in input/*.txt; do
	cat "${f}" | ./build/greedy | ./build/score "${f}" | gnuplot -p -e 'set terminal pdfcairo; plot "-" using 1:2 notitle' > ${f}.pdf
done
