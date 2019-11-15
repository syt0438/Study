#!/bin/bash

outfile="$SHELL_HOME/logs/out76"

touch $outfile && echo "create outfile $outfile sucessed."

exec 3>&1
exec 1>$outfile

echo "This should store in the output file"
echo "along with this line."

exec 1>&3

echo "冬饮寒水，夜渡断桥"

exit 0
