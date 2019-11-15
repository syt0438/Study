#!/bin/bash

echo "Program name is $0"

result=1
for (( n = 1; n <= $1 ; n++ ))
do
    result=$[ $result * $n ]
done

echo "The factorial of $1 is $result."

exit 0
