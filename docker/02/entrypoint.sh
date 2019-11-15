#!/bin/sh

echo 'This is study 02 tests'

echo 'Parameter count is '$#

count=0
for param in "$@"
do
	count=$(( $count + 1 ))

	echo "Parameter [#$count] is $param"
done

exit 0
