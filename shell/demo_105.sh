#!/bin/bash -x

get_answer() {
    local ASK_COUNT=0
    local ANSWER=""

    while [ -z "$ANSWER" ]
    do
        ASK_COUNT=$[ $ASK_COUNT + 1 ]

        case $ASK_COUNT in
            1)
                echo
                echo "Please enter the username of the user "
                echo -e "account you wish to delete from system."
                ;;
            2)
                echo
                echo "Please answer the question."
                ;;
            3)
                echo
                echo "One last try...please answer the question."
                ;;
            4)
                echo
                echo "Since you refuse to answer the question..."
                echo "exiting program."
                echo
                
                exit
                ;;
        esac


        read -t 60 -p "Enter username: " ANSWER

        uname=$ANSWER
    done
}

get_answer

user_acount_record=$(cat /etc/passwd | grep -w $uname)

if [ $? -ne 0 ]; then
    echo
    echo "Account, $uname, not found. "
    echo "Leaving the script..."
    echo

    exit 1
fi

echo
echo "Found User count info:"
echo "$user_acount_record"
echo

ps -u $uname >/dev/null 2>&1

case $? in
    1)
        echo "There are no processes for this account currently running."
        echo
        ;;
    0)
        echo "$uname has the following processes running: "
        echo

        ps -u $uname

        echo
        echo "Will kill this processes."
        echo
        ;;
esac

commandList=`ps -u $uname --no-heading 2>/dev/null`
commandPIDList=`echo "$commandList" | gawk '{ print $1 }'`

if [ -n "$commandPIDList" ]; then
    echo "$commandPIDList" | xargs -d \\n /bin/kill -9
    
    if [ $? -eq 0 ]; then
        echo 
        echo "Process(es) killed."
        echo
    else
        tailCommandList=`ps -u $uname --no-heading 2>/dev/null`

        if [ -n "$tailCommandList" ]; then
            echo "Process(es) incomplete killed!"

            exit 1
        else
            echo "Process(es) killed."
        fi
    fi
else
    echo "User $uname not running any process."
fi

userFileList=`find / -user $uname 2>/dev/null`

echo "$userFileList"

read -n 1 -p "Remove $uname's account from system? [y/n]" answer
echo

if [ "$answer" = "y" -o "$answer" = "Y" ]; then
    formattedUserFileList=`echo "$userFileList" | sed ':repeat; N; s/\n/ /g; t repeat'`

    /bin/rm -rvf $formattedUserFileList

    echo "User file list delete successed."
else
    echo "You answer no, stop delete user"

    exit 1
fi

echo "Delete User Start ##############################"

userdel $uname

if [ $? -eq 0 ]; then
    echo "Delete User $uname Successed"
else
    echo "Delete User $uname Failed"
fi

echo "Delete User End ##############################"




