#!/bin/bash
sftp shikuiyang@10.180.8.21 <<EOF
get helloworld.c
bye
EOF
