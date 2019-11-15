#!/bin/bash

trap "echo 'Goobye, Linshu!'" EXIT
trap "echo 'Goobye By Ctrl-C!'" SIGINT

count=1
while [ $count -le 5 ]
do
    if [ $count -eq 3 ]; then
        exit 130
    fi

    echo "Loop #$count"
    sleep 1
    count=$[ $count + 1 ]
done
