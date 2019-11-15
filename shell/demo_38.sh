#!/bin/bash

n1=100

until [ $n1 -lt 0 ]
do
    echo "The value is $n1."

    n1=$[ $n1 - 25 ]
done

exit 0
