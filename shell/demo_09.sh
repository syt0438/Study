#!/bin/bash

n1=10.46
n2=43.64
n3=33.2
n4=71

result=$(bc << EOF
	scale=5
	a1 = $n1 * $n2
	a2 = $n3 * $n4
	a1 + a2 
EOF
)

echo "The result is $result"
