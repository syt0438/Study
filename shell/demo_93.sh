#!/bin/bash

function addem {
    echo
    echo "`date +'%F %T.%3N'` INFO: $@"
    echo

    if [ $# -eq 0 ] || [ $# -gt 2 ]
    then
        echo -1
    elif [ $# -eq 1 ]
    then
        echo $[ $1 + $1 ]
    else
        echo $[ $1 + $2 ]
    fi
}

echo "Adding 10 and 15: "
value=`addem 10 15`
echo $value

echo "Let's try adding just one number: "
value=`addem 10`
echo $value

echo "Now trying adding no numbers: "
value=`addem`
echo $value

echo "Finally, try adding three numbers: "
value=`addem 10 15 20`
echo $value

exit 0
