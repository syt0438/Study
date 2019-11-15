#!/bin/bash

for (( n = 1; n <= 3; n++ ))
do
    echo "Outer layer value: $n."

    for (( j = 1; j <= 3; j++ ))
    do
        echo "Inner layer value: $j."
    done
done

exit 0
