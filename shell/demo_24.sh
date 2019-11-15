#!/bin/bash

filepath=/etc/passwd

if [ -O /etc/passwd ]; then
    echo "You are the owner of the /etc/passwd file"
else
    echo "Sorry, you are not the onwer of the /etc/passwd file"
fi
