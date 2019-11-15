#!/bin/bash -x

function generateId {
   echo `uuid | sed 's/\-//g'`
}

function execSql {
#    if [ $# -ne 3 ]; then
#        echo "Illegal Parameter: $@"
#
#        return 1
#    fi

    local MYSQL=`which mysql`

    $MYSQL -h $linshucloud -u root -D study 0<&3
}

execSql 3<< EOF
    INSERT INTO user VALUES('`generateId`', '$1', '$2', '$3');
EOF

[ $? -eq 0 ] && echo OK
