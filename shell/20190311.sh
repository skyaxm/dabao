#!/bin/bash
localPath=$1
remotePath=$2
serverIP=$3
sftpUser=$4
sftpPass=$5

SYSDATE=`date +%Y%m%d`
STATION_ARR[0]="k0001"
STATION_ARR[1]="k0253"
STATION_ARR[3]="zdfile"

#-----------------------------------
# 0 成功
# 1 参数传递异常
# 2 处理文件夹异常
# 3 获取文件异常
#-----------------------------------
retRunCode()
{
    if [ ${result} -eq "1" ]; then
        RETURNCODE=$1
        echo ${RETURNCODE}
    fi
}

if [[ $# != 5 ]]; then
    exit
fi
result=$?
retRunCode "1"

createForlder()
{
    cd $1
    if [[ ! -d ${SYSDATE} ]]; then
        mkdir ${SYSDATE}
        chmod 755 ${SYSDATE}
    fi
    cd ${SYSDATE}
}

sftp_certificate_download()
{
    sftp shikuiyang@10.180.8.21 <<EOF
    get helloworld.c
    bye
    EOF
}

sftp_password_download()
{

    lftp -u ${sftpUser},${sftpPass} sftp://${serverIP} <<EOF
    cd ${remotePath}
    get helloworld.c
    bye
    EOF
}

sftp_expect_download()
{
    /usr/bin/expect <<EOF
    set timeout 5
    spawn sftp $1@$2
    expect {
    "(yes/no)?" {send "yes\r"; expect_continue}
    "password:" {send "$3\r"}
    }
    expect "sftp>"
    send "cd $4\r"
    set timeout -1
    expect "sftp>"
    send "get helloworld.c\r"
    expect "sftp>"
    send "bye\r"
    EOF
}

createForlder ${localPath}
reslut=$?
retRunCode "2"

for station in ${STATION_ARR[@]}; do
    remoteDir=${remotePath}${station}
    sftp_download ${sftpUser} ${serverIP} ${sftpPass} ${remoteDir}
done
result=$?
retRunCode "3"
