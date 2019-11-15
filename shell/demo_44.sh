#!/bin/bash

for (( i = 0; i < 10; i++ ))
do
    n=$[ $RANDOM % 100 ]

    echo "$n"
done | sort -n > out44.txt

echo "Out to out44.txt finish."

exit 0
