#!/bin/bash

file="/etc/passwd"

IFS=$':\n'

for item in $(cat $file)
do
    echo "$item"
done

exit 0
