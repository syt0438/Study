#!/bin/bash

if [ -z $1 ]; then
    echo "\$1 must be not empty."

    exit 1
fi

if [ -z $2 ]; then
    echo "\$2 must be not empty."

    exit 1
fi

total=$[ ${1} * ${2} ]

echo "The total value is ${total}"
