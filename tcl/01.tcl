#!/usr/bin/expect

spawn /opt/study/shell/demo_116.sh

expect {
    "*folder*" {
        send "大盛魁_100\n"

        exp_continue
    }

    "*type*" {
        send "mp4\n"
        
        exp_continue
    }
}
