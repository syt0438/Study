#!/bin/bash

n1=10

while (( $n1 > 0 ))
do
    echo "The next value $n1."
    
    n1=$[ $n1 - 1 ]
done

exit 0
