#!/bin/bash

echo "Handle \$*=$* Start: "
count=1

for param in "$*"
do
    echo "\$* Parameter #$count = $param"
    count=$[ $count + 1 ]
done

echo "Handle \$@=$@ Start: "
count=1

for param in "$@"
do
    echo "\$@ Parameter #$count = $param"

    count=$[ $count + 1 ]
done
