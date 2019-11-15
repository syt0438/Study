#!/bin/bash

index=1
for param in "$@"
do
    echo "#$index = $param"

    index=$[ $index + 1 ]
done
