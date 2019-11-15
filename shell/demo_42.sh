#!/bin/bash

for (( n = 1; n < 10; n++ ))
do
    echo "The number is $n."
done > out42.txt

echo "Out to out42.txt file finish."

exit 0
