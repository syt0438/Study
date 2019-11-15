#!/bin/bash

outfile="$SHELL_HOME/logs/out75"

touch $outfile && exec 3> "$outfile" && echo "INFO: FD[3] -> $outfile"

echo "This should display on the monitor"
echo "and this should be stored in the file" >&3
echo "Then this should be back on the monitor"

exit 0
