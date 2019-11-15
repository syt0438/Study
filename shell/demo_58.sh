#!/bin/bash

echo
count=1

until [ -z "$1" ]
do
    echo "Parameter #$count = $1"

    count=$(( $count + 1 ))

    shift
done

exit 0
