#!/bin/bash

exec 3<> /root/readin

read line <&3

echo "Read: $line"
echo "This is a test line" >&3

exit 0
