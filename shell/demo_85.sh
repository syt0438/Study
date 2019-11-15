#!/bin/bash

trap "echo 'Sorry! I have trapped Ctrl-C'" SIGINT

trap "echo 'Sorry! I hava trapped Ctrl-Z'" SIGSTOP

echo "This is a test script"

count=1

while [ $count -le 10 ]
do
    echo "Loop #$count"
    sleep 3
    count=$[ $count + 1 ]
done

echo "This is the end of the test script"
