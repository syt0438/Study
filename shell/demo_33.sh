#!/bin/bash

list=`ls -al $SHELL_HOME`

for item in $list
do
    if [ -x $SHELL_HOME/$item ]; then
        echo "$item can executable."
    fi
done

exit 0
