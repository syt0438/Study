#!/bin/bash

exec 3> /root/readin

echo "冬饮寒水，夜渡断桥" >&3

exec 3>&-

echo "This is don't work!!!" >&3

exit 0
