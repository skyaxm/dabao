#!/bin/bash
HOST=10.180.8.21
USER=shikuiyang
PASS=foxconn167
echo "Starting sftp..."
lftp -u ${USER},${PASS} sftp://${HOST}:22 <<EOF
cd /home/shikuiyang
get helloworld.c /home/shikuiyang/projects/test/
bye
EOF
echo "done"
