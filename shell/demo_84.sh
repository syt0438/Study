#!/bin/bash

outfile="${SHELL_HOME}/datas/members.sql"
IFS=','

while read lname fname address city state zip
do
    data=`cat << EOF 
INSERT INFO members (lname, fname, address, city, state, zip)
    VALUES('$lname','$fname', '$address', '$city', '$state', '$zip');
EOF
`
    echo "Data start >>>"
#    echo $data | tee -a $outfile
    tee -a $outfile << EOF
$data
EOF
    echo "<<< Data end"
    echo
done < ${1}

exit 0
