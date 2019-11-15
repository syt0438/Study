#!/bin/bash

for (( n = 1; n <= 10; n++ ))
do
    echo "The next number is $n."
done

if (( $n == 11 )); then
    echo "The last number is $n."

    exit 0
else
    echo "WARN: The last number is $n."

    exit 1
fi
