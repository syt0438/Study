#!/bin/bash

count=0

cat /etc/passwd | while read line
do
    count=$[ $count + 1 ]

    echo "Line $count: $line"
done

