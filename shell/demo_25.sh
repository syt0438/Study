#!/bin/bash

filepath=/etc/passwd

if [ -G /etc/passwd ]; then
    echo "You are in the same group as the file"
else
    echo "The file is not owned by your group"
fi
