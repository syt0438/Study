#!/bin/bash

file=/etc/passwd
fileContent=`head -n 3 $file`

IFS.OLD=$IFS
IFS=$'\n'

lineNo=0
for line in $fileContent
do
    lineNo=$(( $lineNo + 1 ))
    columnNo=0
    echo "line $lineNo: $line"

    IFS=$':'
    for column in $line
    do
        columnNo=$(( $columnNo + 1 ))

        echo "    $columnNo: $column"
    done
done

exit 0
