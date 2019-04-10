#!/bin/bash
sftpUser=$1
serverIP=$2
sftpPass=$3
remotePath=$4
#localPath="/home/shikuiyang/projects/shell/download/"
localPath=$5

#-----------------------------------
# 0 成功
# 1 验证错误
# 2 SFTP错误
# 3 文件未找到
# 4 内部原因导致操作失败
# 5 执行期间源文件丢失
#-----------------------------------

if [[ $# != 4 && $# != 5 ]]; then
    exit 1
fi

echo '$# =' $#

if [[ $# == 4 ]]; then
    sftpPass=""
    remotePath=$3
    localPath=$4
fi

echo ${remotePath}

if [[ ! -f "/usr/bin/sftp" ]]; then
    exit 2
fi

if [ ! -d "${localPath}" ]; then
    mkdir -p ${localPath}
fi

sftp_password_download()
{
    /usr/bin/expect <<-EOF
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
EOF
}

sftp_password_download
