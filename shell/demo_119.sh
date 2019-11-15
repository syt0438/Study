#!/bin/bash

if [ -z "$1" ]; then
    echo 'baseip must be not null.'

    exit 1
fi

for ip in $1.{1..255}
do
    (
        echo "try ping $ip"

        ping $ip -c 2 -W 3 &>/dev/null

        if [ $? -eq 0 ]; then
            echo "ping $ip reachable."
        else
            echo "ping $ip not reachable."
        fi
    ) &
done

wait && exit 0
