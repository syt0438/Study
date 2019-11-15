#!/bin/bash

exec 3< /root/readin

read line <&3
echo "Read: $line"

exec 4> /root/readin
echo "This is a test line" >&4

exit 0

