#!/bin/bash

for (( n = 11; n < 20; n++ ))
do
    echo "The number is $n."
done >> out42.txt

echo "Out to out42.txt file finish."

exit 0
