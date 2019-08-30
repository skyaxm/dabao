#!/bin/bash


./phy_init.arm
echo "   "
echo "phy_init.....done!!"
echo "   "

echo "kernel current dma buffer max_block_size is:"
cat /sys/module/industrialio_buffer_dma/parameters/max_block_size

echo "set kernel buffer max_block_size to 64M, default 16M"

#echo 67108864 > /sys/module/industrialio_buffer_dma/parameters/max_block_size

echo "kernel current dma buffer max_block_size is:"
cat /sys/module/industrialio_buffer_dma/parameters/max_block_size

rm $2.txt
param=$2                                      
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
    devmem 0x43c30004 32 0x0
    devmem 0x43c30010 32 0x8400b000

elif [[ $param = "tx_loopback" ]]; then
    echo "tx loop back"
    devmem 0x43c30010 32 0x8200b000
    
elif [ $param = "cpr_data" ]; then
    echo "cpr_data"
    devmem 0x43c30004 32 0x0
    devmem 0x43c30010 32 0x8000b000
    devmem 0x43c30014 32 0xc000b000

elif [ $param = "fft_data" ]; then
    echo "fft_data"
    devmem 0x43c30004 32 0x0
    devmem 0x43c30010 32 0x8000b000
    devmem 0x43c30014 32 0xa000b000

elif [[ $param = "com_data" ]]; then
    echo "com_data"
    devmem 0x43c30004 32 0x0
    devmem 0x43c30010 32 0x8000b000
    devmem 0x43c30014 32 0x8800b000

elif [[ $param = "scd_data" ]]; then
    echo "scd_data"
    devmem 0x43c30004 32 0x0
    devmem 0x43c30010 32 0x8000b000
    devmem 0x43c30014 32 0x8400b000
        
elif [[ $param = "rx_loopback" ]]; then
    echo "rx loop back"
    devmem 0x43c30004 32 0x0
    devmem 0x43c30010 32 0x8000b000
    devmem 0x43c30014 32 0x8200b000    
    
fi


#echo "enable harden_sync..........."
sleep 1
devmem 0x43c30038 32 0xa
devmem 0x43c30004 32 0x1
echo "enable harden_tx.........& scm_data"


chmod +x stream-test
way=6



if [[ $1 -eq 3 ]]; then
	./stream-test -w $way -f $3 -s $4 -p $1 -o $param
elif [[ $1 -eq 1 ]]; then	
	./stream-test -w $way -f $3 -p $1 -o $param
elif [[ $1 -eq 2 ]]; then
	./stream-test -w $way -f $3 -p $1 -o $param
else
	echo "error port input."
fi


sz $2.txt

#./rxGo.sh 3 scm_data filename1 filename2





