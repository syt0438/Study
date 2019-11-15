#!/bin/bash

set -- $( getopt -q a:b:c: "$@" )

echo "Formatted command line parameter: $@"
echo

echo "Handle option Start"
echo

while [ -n "$1" ]
do
    case "$1" in 
        -a)
            param="$2"
            echo "Found the $1 option, with parameter value $param"
            shift
            ;;
        -b)
            param="$2"
            echo "Found the $1 option, with parameter value $param"
            shift
            ;;
        -c)
            param="$2"
            echo "Found the $1 option, with parameter value $param"
            shift
            ;;
        --)
            shift
            echo
            break;;
        *)
            echo "$1 is not an option."
            ;;
    esac

    shift
done

echo "Handle option End"

echo

echo "Handle parameter Start"
echo

count=1
for param in "$@"
do
    echo "Parameter #$count = $param"

    count=$[ $count + 1 ]
done

echo
echo "Handle parameter End"
