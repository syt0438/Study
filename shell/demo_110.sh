#!/bin/bash 

fmt_params=`getopt -qu u:f: "$@"`

set -- $fmt_params

uname=""
in_file=""
while [ -n "$1" ]
do
    opt=$1

    case $opt in
        -u)
            uname="$2"
            shift
            
            echo "$opt: $uname"
            ;;
        -f)
            in_file="$2"
            shift
            
            echo "$opt: $in_file"
            ;;
        --)
            ;;
        *)
            ;;
    esac

    shift
done

logged=$(who | grep -m 1 -w $uname | gawk '{print $1}')

if [ -z "$logged" ]; then 
    echo "$uname is not logged on."
    echo "Exiting script..."

    exit 1
fi

allowed_mesg=$(who -T | grep -i -m 1 $uname | gawk '{print $2}')

if [ $allowed_mesg != "+" ]; then
    echo "$uname does not allowing messaging."
    echo "Exiting script..."

    exit 1
fi

if [ -n "$in_file" -a -f "$in_file" ]; then
    in_msg=`cat $in_file`
else
    in_msg=`cat <&0`
fi


uterminals=$( who | grep $uname | gawk '{print $2}' )

for uterminal in $uterminals
do
    echo "$in_msg" | write $logged $uterminal
done













