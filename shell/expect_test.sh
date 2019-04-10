#!/bin/expect -f

spawn sftp shikuiyang@10.180.8.21
expect {
"*yes/no" {send "yes\r"; exp_continue}
"*password:" {send "foxconn168\r"}
}
expect "sftp>"
send "cd /home/samba\r"
set timeout -1
expect "sftp>"
send "cd /home/shikuiyang\r"
expect "sftp>"
send "get hello.c\r"
expect {
"File*not found."; {send "bye\r"}
}
#expect "sftp>"
#send "exit\r"
#catch waite ret;
#exit [lindex \$ret 3]
#expect eof
#interact
#set timeout -1
#EOF
