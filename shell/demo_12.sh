#!/bin/bash

u=linshu

if grep $u /etc/passwd
then
    echo "This is my first command"
    echo "This is my second command"
    echo "I can even put in other commands besides echo:"

    ls -a /home/$u/
fi
