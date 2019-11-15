#!/bin/bash

func() {
    local oldList
    local newList
    local result
    oldList=($@)
    newList=($@)
    result=0

    for (( i = 0; i < $[ $# - 1 ]; i++ ))
    do
        result=$[ ${oldList[$i]} * 2 ]

        newList[$i]=$result
    done

    echo ${newList[*]}
}

result=`func $@`

echo "The final result is $result"
