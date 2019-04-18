#!/bin/expect -f
set sftpUser "shikuiyang"
set serverIP "10.180.8.21"
set sftpPass "foxconn168"
set remotePath "/home/shikuiyang/hello"
#localPath="/home/shikuiyang/projects/shell/download/"
set localPath [lindex $argv 4]

puts $sftpUser
puts $serverIP
puts $sftpPass
puts $remotePath
puts $localPath
puts $argc

#-----------------------------------
# 0 成功
# 1 验证错误
# 2 SFTP错误
# 3 文件未找到
# 4 内部原因导致操作失败
# 5 执行期间源文件丢失
#-----------------------------------

if {$argc != 4 && $argc != 5} {
    exit 1
}

if {$argc == 4} {
    set remotePath [lindex $argv 2]
    set localPath [lindex $argv 3]
}
puts $remotePath
puts $localPath

if {! [file exists /usr/bin/sftp]} {
    exit 2
}

if {[file exists $localPath]} {
    if {! [file isdirectory $localPath]} {
        puts "$localPath exists, but it's a file"
    }
} else {
    file mkdir $localPath
}

set timeout 3
spawn sftp ${sftpUser}@${serverIP}
expect {
"*yes/no" {send "yes\r"; exp_continue}
"*password:" {send "${sftpPass}\r"}
}
set timeout -1
expect "sftp>"
send "get -r ${remotePath} ${localPath}\r"
expect "sftp>"
send "bye\r"
expect eof

