#!/bin/bash

rm *.txt

./phy_init.arm
echo "   "
echo "phy_init.....done!!"
echo "   "

echo "enable harden_sync..........."
devmem 0x43c30004 32 0x1
echo "enable harden_tx.........& scm_data"

param=$3                                      
if [ $param = "scm_data" ]; then
    echo "scm_data"
    devmem 0x43c30010 32 0xc000b000

elif [ $param = "dec_data" ]; then
    echo "dec_data"
    devmem 0x43c30010 32 0xa000b000

elif [[ $param = "ifft_data" ]]; then
    echo "ifft_data"
    devmem 0x43c30010 32 0x9000b000

elif [[ $param = "cpi_data" ]]; then
    echo "cpi_data"
    devmem 0x43c30010 32 0x8400b000

elif [[ $param = "loopback" ]]; then
    echo "loop back"
    devmem 0x43c30010 32 0x8200b000
fi



chmod +x stream-test

./stream-test -w 6 -p $2 -f $1 -o $param






