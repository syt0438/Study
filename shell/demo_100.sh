#!/bin/bash

if [ ! -f "$1" ]; then
    echo "$1 data file not exist!!!" >&2

    exit 1
fi

for team in $(gawk -F "," '{print $2}' $1 | uniq)
do
    gawk -v team=$team '
        BEGIN {
            FS=","
            total=0
        }

        {
            if ($2 != team)
            {
                next
            }
                
            for (n=3; n <=$NF; n++)
            {
                total += $n
            }
        }

        END {
            avg = total / 6
            print "Total for", team, "is", total, ", the average is", avg
        }
    ' $1
done
