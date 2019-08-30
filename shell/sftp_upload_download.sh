#!/bin/bash
option=$1
user=$2
password=$3
host=$4
local_path=$5
remote_path=$6

echo "$#"
echo "$@"
if [[ $# != 5 && $# != 6 ]]; then
    exit 1
fi

if [[ $# == 5 ]]; then
    password=""
    host=$3
    local_path=$4
    remote_path=$5
fi

if [[ ! -e ${local_path} ]]; then
    echo $local_path
    exit 2
fi

sftp_upload()
{
    /usr/bin/expect <<-EOF
    set timeout 1
    spawn sftp ${user}@${host}
    expect {
    "*yes/no" {send "yes\r"; exp_continue}
    "*password:" {send "${password}\r"}
    }
    set timeout -1
    expect "sftp>"
    send "put -r ${local_path} ${remote_path}\r"
    expect "sftp>"
    send "bye\r"
    expect eof
EOF
}

sftp_download()
{
    if [[ ! -d ${local_path} ]]; then
        mkdir -p ${local_path}
    fi
    /usr/bin/expect <<-EOF
    set timeout 1
    spawn sftp ${user}@${host}
    expect {
    "*yes/no" {send "yes\r"; exp_continue}
    "*password:" {send "${password}\r"}
    }
    set timeout -1
    expect "sftp>"
    send "get -r ${remote_path} ${local_path}\r"
    expect "sftp>"
    send "bye\r"
    expect eof
EOF
}

if [[ ${option} == "-U" ]]; then
    sftp_upload
elif [[ ${option} == "-D" ]]; then
    sftp_download
else
    exit -2
fi

