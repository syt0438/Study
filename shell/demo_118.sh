#!/bin/bash

if [ $# -lt 1 ]; then
    echo 'Usage: $0 filename';

    exit 1;
fi

filename=$1

if [ ! -f "$filename" ]; then
    echo 'File not exists!'

    exit 1;
fi

egrep -o "\b[[:alpha:]]+\b" "$filename" | tr [:lower:] [:upper:] | gawk '
    {
        count[$0]++
    }
    END {
        printf("%-14s%s\n", "Word", "Count")

        for (item in count)
        {
            printf("%-14s: %d\n", item, count[item])
        }
    }
'

