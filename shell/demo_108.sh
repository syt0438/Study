#!/bin/bash

MYSQL=`which mysql`

dbs=`$MYSQL -h $linshucloud -u root -D study -Bse 'show databases' `

echo $dbs
