#!/bin/bash

function testit {
    echo 
    echo "The parameters are: $@"
    echo 

    local thisarray
    thisarray=($(echo "$@"))
    echo "The received array[1]: ${thisarray[1]}"
    echo "The received array[5]: ${thisarray[5]}"
    echo "The received array is ${thisarray[*]}"
}

myarray=("yzz sjc kxr" "冬饮寒水 夜渡断桥" 3 4 5 6)
echo
echo "The original array is: ${myarray[*]}"
echo

testit ${myarray[*]}
