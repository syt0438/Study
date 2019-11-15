#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage is $0 basepath";

    exit 1
fi

path="$1"

declare -A list;

while read line;
do
    ftype=`file -b "$line" | cut -d ',' -f1`

    let list["$ftype"]++
done <<< `find $path -type f`

echo ============ File types and counts =============

for ftype in "${!list[@]}"
do
    echo $ftype: ${list["$ftype"]}
done

exit 0
