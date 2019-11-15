#!/bin/bash

if [ -z $CONFIG_FILE ]; then
    echo "\$CONFIG_FILE Environment Variable not configured!"

    exit 1
fi

if [ ! -f $CONFIG_FILE ]; then
    echo "\$CONFIG_FILE does not exists!"

    exit 1
fi

backFileList=""
lineNo=0
while read backFileName
do
    lineNo=$[ $lineNo + 1 ]

    if [ -f "$backFileName" ]; then
        backFileList="$backFileList $backFileName"

        continue
    fi

    subFileList=`ls $backFileName 2> /dev/null`

    if [ -n "$subFileList" ]; then
        backFileList="$backFileList $subFileList"

        continue
    fi

    echo
    echo "$backFileName does not exist."
    echo "Obviously, I will not include it in this archive."
    echo "It is listed on line $lineNo of the config file."
    echo "Continuing to build archive list..."
    echo
done 0< $CONFIG_FILE

echo "Backup file list: "
echo $backFileList

