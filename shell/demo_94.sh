#!/bin/bash

badfunc(){
    echo $[ $1 * $2 ]
}

if [ $# -eq 2 ]; then
    value=$(badfunc $@)

    echo "The result is $value"
else
    echo "Usage: badfunc a b"
fi

exit 0
