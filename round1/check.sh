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

TESTS=(
    input/a_example.txt
    input/b_read_on.txt
    input/c_incunabula.txt
    input/d_tough_choices.txt
    input/e_so_many_books.txt
    input/f_libraries_of_the_world.txt
)

SCORE_SUM="0"

POWER=(
    # "2.0"
    # "3.0"
    # "4.0"
    # "5.0"
    # "6.0"
    # "7.0"
    # "8.0"
    # "9.0"
    # "10.0"
    # "11.0"
    # "12.0"
    # "13.0"
    # "14.0"
    "15.0"
    # "16.0"
    # "17.0"
)

LAMBDA=(
    # "0.5"
    # "1.0"
    # "1.8"
    # "2.0"
    "2.2"
    # "3.0"
    # "4.0"
)

for f in "${TESTS[@]}"
do

    for p in "${POWER[@]}"
    do
        for lambda in "${LAMBDA[@]}"
        do
            "${BINARY}" < "${f}" "${p}" "${lambda}" > "output/$(basename ${f})"
            echo -n " ${f} ${p} ${lambda} Score: "
            SUB_SCORE=$(cat "output/$(basename ${f})" | "${SCORE}" "${f}" | tail -n 1 | cut -d ' ' -f 2)
            echo "${SUB_SCORE}"
        done
    done

    SCORE_SUM=$(( SCORE_SUM + SUB_SCORE ))
done

echo "Total score: ${SCORE_SUM}"
