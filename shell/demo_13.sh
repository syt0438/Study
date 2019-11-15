#!/bin/bash

u=nolinshu

if grep $u /etc/passwd
then
    echo "User linshu exists"
else
    echo "User linshu does not exist"
fi
