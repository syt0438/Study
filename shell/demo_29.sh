#!/bin/bash

u=$USER

if [[ $u == *ro* ]]; then
    echo "Hello, $u"
else
    echo "I dont know you."
fi
