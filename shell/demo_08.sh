#!/bin/bash

n1=20
n2=3.14159
result=$(echo "scale=4; $n1 * $n2" | bc)

echo "The result is $result"
