#!/bin/bash

echo "Start the test script"
count=1
while [ $count -le 5 ]
do
    echo "Loop #$count"
    sleep 5
    count=$[ $count + 1 ]
done
#
echo "Test script is complete"

exit 0
