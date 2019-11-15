#!/bin/bash

case $USER in
    root | linshu)
        echo "Allow User $USER view."
        exit 0;;
    other)
        echo "Not allow other user view."
        exit 1;;
    *)
        echo "Default View: $(date +%F)."
        exit 1;;
esac
        
