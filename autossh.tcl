#!/usr/bin/expect

spawn /usr/bin/ssh root@211.159.216.48

expect {
	"*password*" {
		send "ds.10262018\n"

		exp_continue
	}
}
