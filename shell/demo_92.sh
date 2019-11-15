#!/bin/bash

function hello() {
    read -p "Enter a value: " value

    echo "###### Result Start ######"
    echo $[ $value * 2 ]
    echo "###### Result  End  ######"
}

result=`hello`

echo "$result"
