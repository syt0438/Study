#!/bin/bash

n=3

until [ $n -eq 0 ]
do
    echo "Outer loop: $n"
    
    i=1

    while [ $i -lt 5 ]
    do
        j=$(echo "scale=4; $n / $i" | bc)

        echo "    Inner loop: $n / $i = $j"
        i=$[ $i + 1 ]
    done

    n=$[ $n - 1 ]
done
