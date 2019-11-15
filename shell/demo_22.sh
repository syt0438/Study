#!/bin/bash

filename=empty2

if [ -f $filename ]
then
    if [ -s $filename ]
    then
        echo "The $filename file exists and has data in it."
        echo "Will not remove this file."
    else
        echo "The $filename file exists, but is empty."
        echo "Deleting empty file..."

        rm $filename
    fi
else
    echo "File, $filename, does not exist"
fi
