#!/bin/bash

echo "`date '+%F %T.%N'` START: Resolve command line."

while [ -n "$1" ]
do
    case "$1" in
        -a)
            echo "Found the -a option."
            echo;;
        -b)
            param=$2
            echo "Found the -b option, with parameter value $param."
            shift
            echo;;
        -c)
            echo "Found the -c option."
            echo;;
        --)
            echo "$1 is an end of option."
            shift
            break
            echo;;
        *)
            echo "$1 is not an option."
            echo;;
    esac
    shift
done

echo "`date '+%F %T.%N'` END: Resolve command line. "

exit 0
