#!/bin/bash

echo $$
echo
exec 3> /root/readin

echo "冬饮寒水，夜渡断桥" >&3
echo "忍性吞气，茹苦饮痛" >&3


sleep 60

exec 3>&-

cat /root/readin

echo
echo
echo

exec 3> /root/readin

sleep 30

echo "Bad data" >&3

exit 0
