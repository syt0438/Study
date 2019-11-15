#!/bin/bash

outfile="$SHELL_HOME/logs/out72"

if [ ! -f "$outfile" ]; then
    touch "$outfile"
fi

exec 1> "$outfile"

echo "yzzsjckxrtbf"
echo "ds10262018"
echo "520863.syt"

exit 0
