#!/bin/bash

u=linshu

if [ $USER != $u ]
then
    echo "This is not $u"
else
    echo "Welcome to Debian, $u"
fi
