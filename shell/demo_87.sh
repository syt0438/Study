#!/bin/bash

trap "echo kill-9 this program!!!" 9

count=1
while [ $count -le 5 ]
do
    echo "Loop #$count"
    sleep 2
    count=$[ $count + 1 ]
done

trap "echo ' I modified the trap Ctrl-C!'" 2

count=1
while [ $count -le 5 ]
do
    echo "Second Loop #$count"
    sleep 10
    count=$[ $count + 1 ]
done


count=1
trap -- 2
while [ $count -le 5 ]
do
    echo "Third Loop #$count"
    sleep 2
    count=$[ $count + 1 ]
done


