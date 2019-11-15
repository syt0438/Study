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

echo "#OPTIND = $OPTIND"

echo "Command line parameters: $@"
