#!/bin/bash

echo "--------------------------------------------------------------------------------"

count=1
shiftCount=$1

shift

until [ -z "$1" ]
do
    echo "WARN: \$1 = $1, Parameter #$count = $1"

    count=$[ $count + $shiftCount ]

    for (( i = 1; i <= $shiftCount; i++ ))
    do
        shift
    done
done

exit 0
