#!/bin/bash

index=1
for param in $@
do
    echo "Parameter #$index = $param"
    index=$[ $index + 1 ]
done

exit 0
