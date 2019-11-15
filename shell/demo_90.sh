#!/bin/bash

func1() {
    echo "function 1 call."

    ls -l badfile
}

echo "Testing the function1: "

func1

echo "The exit status is: $?"
