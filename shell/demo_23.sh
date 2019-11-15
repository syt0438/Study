#!/bin/bash

filename=demo5

if [ -x $filename ]; then
    echo "You can run the script: $filename"
else
    echo "You are unable to execute the script $filename"
fi
