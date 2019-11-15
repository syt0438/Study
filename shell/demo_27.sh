#!/bin/bash

if [ ! -e file1 ]; then
    echo "ERROR: The file1 does not exist"
    exit 1
fi

if [ ! -e file2 ]; then
    echo "ERROR: The file2 does not exist"
    exit 1
fi


if [ file1 -nt file2 ]; then
    echo "The file1 is newer then file2"
else
    echo "The file2 is newer then file1"
fi
