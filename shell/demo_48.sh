#!/bin/bash

in="/etc/passwd"

IFS=:

while read -r userId pwd uid gid other
do
    echo "$userId --- $pwd --- $uid --- $gid"
    echo "        other-> $other"
done < "$in" | tail -n 8 > demo48.txt

exit 0
