#!/bin/bash

paramCount=$#

for (( i = 1; i <= $paramCount; i++ ))
do
    echo "Param $i's value is ${!i}"
done

echo "Parameters print finish."

exit 0
