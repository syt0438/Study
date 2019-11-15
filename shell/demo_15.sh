#!/bin/bash

u=linshu

if grep $u /etc/passwd; then
    echo "The user $u exists on this system."
elif ls -d /home/$u/; then
    echo "However, $u has a directory."

    if rm -rf /home/$u; then
        echo "The user $u directory deleted"
    fi
fi
