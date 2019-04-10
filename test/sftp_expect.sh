#!/usr/bin/expect -f
spawn sftp shikuiyang@10.180.8.21
expect "sftp>"
send "get helloworld.c\r"
expect "sftp>"
send "cd /home/samba\r"
expect "sftp>"
send "pwd\r"
expect "sftp>"
send "bye\r"
