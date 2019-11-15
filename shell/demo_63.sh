#!/bin/bash

echo "Command line parameters: $@"

echo "#OPTIND = $OPTIND"

while getopts :a:b:c: opt
do
    echo "#OPTIND = $OPTIND"
    case "$opt" in
        a)
            echo "Found the -$opt option, with value $OPTARG."
            ;;
        b)
            echo "Found the -$opt option, with value $OPTARG."
            ;;
        c)
            echo "Found the -$opt option, with value $OPTARG."
            ;;
        *)
            echo "Unknow option: -$opt."
            ;;
    esac
done

shift $[ $OPTIND - 1 ]

echo

count=1

for param in "$@"
do
    echo "Parameter #$count: $param"

    count=$[ $count + 1 ]
done

echo "Command line parameters: $@"
