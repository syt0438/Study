#!/bin/bash

limit=104

for (( i = 1; i < limit; i++ ))
do
    no=`printf "%02d" $i`

    oldFilePath="$SHELL_HOME/demo$no.sh"
    newFilePath="$SHELL_HOME/demo_$no.sh"

    mv -f $oldFilePath $newFilePath 2> /dev/null

    if [ $? -eq 0 ]; then
        echo "Move file $oldFilePath to $newFilePath successed!"
    else
        echo "Move file $oldFilePath to $newFilePath failed"
    fi
done
