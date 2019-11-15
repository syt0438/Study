#!/bin/bash

if read -t 5 -p "Please enter your name: "; then
    echo "Nice to meet you, $REPLY, Welcome to my script!"
else
    echo
    echo "Sorry, You are too slow! "
fi
