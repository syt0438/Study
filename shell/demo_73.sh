#!/bin/bash

errorfile="$SHELL_HOME/logs/error73"
outfile="$SHELL_HOME/logs/out73"

if [ ! -f "$errorfile" ]; then
    touch "$errorfile" && echo "$errorfile does not exist, create $errorfile sucessed"
fi

if [ ! -f "$outfile" ]; then
    touch "$outfile" && echo "$outfile does not exist, create $outfile sucessed"
fi

exec 2> $errorfile

echo "This is the start of the script"
echo "now redirecting all output to another location"

exec 1> $outfile

echo "This output should go to the $outfile file"
echo "but this should go to the $errorfile file" >&2

exit 0
