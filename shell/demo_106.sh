#!/bin/bash

MYSQL=`which mysql`

$MYSQL -h 211.159.216.48 -u root -D study << EOF
    select * from user;
EOF
