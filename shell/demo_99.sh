#!/bin/bash

PS3="Enter option: "

menulist=`cat $SHELL_HOME/datas/menu99`

IFS=$'\n'
select option in $menulist
do
    case "$option" in
        "Exit Program")
            break
            ;;
        "Test 1")
            echo "Call Test 1"
            ;;
        "Test 2")
            echo "Call Test 2"
            ;;
        "Test 3")
            echo "Call Test 3"
            ;;
        *)
            clear
            echo "Sorry, Wrong selection"
            ;;
    esac
done

clear
