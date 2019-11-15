#!/bin/bash

in="46.csv"
IFS=$", "

while read -r userid name
do
    echo "WARN: Adding User $userid - $name"

    useradd -c "$name" -m $userid
done < $in
