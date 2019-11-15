#!/bin/bash

exec 3<&0
exec 0< /root/readin

count=0
while read line
do
    count=$[ $count + 1 ]

    echo "Line #$count: $line"
done

exec 0<&3

read -p "Are you done now? : " answer

echo "Answer: $answer"

exit 0
