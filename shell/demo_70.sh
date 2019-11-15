#!/bin/bash

count=0

while read line
do
    count=$[ $count + 1 ]

    echo "Line $count: $line"
done < "/etc/passwd"

echo
echo "Read file completion."

exit 0
