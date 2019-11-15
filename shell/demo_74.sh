#!/bin/bash

exec 0< "/root/readin"

count=0
line="start"
while [ "$line" != "exit" ]
do
    read line

    while [ -z "$line" ]
    do
        sleep 1

        read line
    done

    count=$[ $count + 1 ]

    echo "Line #$count: $line" 

    sleep 1
done

exit 0
