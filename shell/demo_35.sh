#!/bin/bash

for item in $HOME/* /opt/* /hello/* /yzzsjc/*
do
    if [ -d "$item" ]; then
        echo "$item is directory."
    elif [ -L "$item" ]; then
        echo "$item is link file."
    elif [ -f "$item" ]; then
        echo "$item is file."
    else
        echo "$item unknow file type."
    fi
done
