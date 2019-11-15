#!/bin/bash

n1=10

if (( $n1 ** 2 > 90 )); then
    (( result=$n1 ** 2 ))
    echo "The square of $n1 is $result"
fi
