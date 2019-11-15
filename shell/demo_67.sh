#!/bin/bash

read -N 11 -p "Do you want to continue [Y/N]? " answer

echo

case $answer in
    Y | y)
        echo "Fine, continue to..."
        ;;
    N | n)
        echo "Ok, goodbye"
        ;;
    *)
        echo "You are a rubbish with $answer."
        ;;
esac

echo
echo "This is the end of the script."
