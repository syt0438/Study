#!/bin/bash

n1=10
n2=11

if [ $n1 -gt 5 ]
then
    echo "The test value $n1 is greater than 5"
fi

if [ $n1 -eq $n2 ]
then
    echo "The values are equal"
else
    echo "The values are different"
fi
