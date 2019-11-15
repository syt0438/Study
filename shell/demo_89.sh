#!/bin/bash

exec 1> $SHELL_HOME/logs/out89

count=1

while [ $count -le 10 ]
do
    echo "Line #$count: $count"

    count=$[ $count + 1 ]

    sleep 10
done
