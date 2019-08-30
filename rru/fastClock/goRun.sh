#!/bin/bash

rm rx_txtdata.txt

./phy_init.arm
echo "   "
echo "phy_init.....done!!"
echo "   "

echo "enable harden_sync..........."
devmem 0x43c30004 32 0x1
echo "enable harden_tx.........& scm_data"
devmem 0x43c30010 32 0x8200b000
#devmem 0x43c30014 32 0x8200b000

chmod +x stream-test

./stream-test -w 6 -p $2 -f $1 -o scm_data






