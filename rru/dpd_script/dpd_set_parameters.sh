
###########################################################################
#base address
#--------------------------------------------------------------------------
BASE_ADDR=0xA4000000


###########################################################################
# $1: address
# $2: value
#--------------------------------------------------------------------------
function reg_r() {
	let "val=$1 << 2"
	addr=$(( $val + $BASE_ADDR))
	#formatTx=$(printf "0x%08x" $addr)
	printf "devmem %08x\n" $addr
	ret=$(devmem $addr)
	#if [[ $ret -ne $2 ]]; then
	#	echo "ERROR: $1"
	#	printf "0x%08x != 0x%08x\n" $ret $2
	#	exit
	#fi
}


###########################################################################
# $1: address
# $2: value
#--------------------------------------------------------------------------
function reg_w() {
	let "val=$1 << 2"
	addr=$(( $val + $BASE_ADDR))
	ToAddr=$(printf "0x%x" $addr)
	value=$(printf "0x%x" $2)
	echo "$ToAddr --> $value"
	devmem $ToAddr 32 $value
}





###########################################################################
# read value from file($2), write these value to address($1)
# $1: address
# $2: the value set what you wana to write
# reg_range_w 0x00000200 cfg_value.txt
#--------------------------------------------------------------------------
function reg_range_w() {

    if [[ -e $2 ]]; then
    	cfg_files=( $(cat $2 ) )
    else
	echo "file: $2 no found!"
	exit
    fi


    let "val=$1 << 2"
    addr_base=$(( $val + $BASE_ADDR ))

    if [[ ${#cfg_files[@]} -ne 512 ]]; then
        echo "cfg_file.txt only cfg 512-values, the file is ${#cfg_files[@]}"
        exit
    fi
	
    for (( i=0; i<${#cfg_files[@]}; i++ ));
    do
        let "temp=$i*4"
        addr=$(( $addr_base + $temp))
        value=$(echo $((16#${cfg_files[i]})) )
        printf "devmem %08x 32 %08x\n" $addr $value
        #devmem $addr 32 $2
    done
}
#reg_range_w 0x00000200 $1
#exit

###########################################################################
# read a value from address($1), until the value is $2
# $1: address
# $2: value
#--------------------------------------------------------------------------
function WaitStatus() {                                                           
                                                                                 
    let "val=$1 << 2"                                                            
    addr=$(( $val + $BASE_ADDR))                                                 
    ret=$(devmem $addr 32)                                                          
    #echo "ret=$ret ipt=$2"                                                                             
    
    until (( $ret == $2 ))                                                      
    do
        ret=$(devmem $addr 32)
    done
    echo "pass $ret"
}


#WaiteStatus 0x00000000 $1

###########################################################################
# 1. Verify CODEPOINTER is WAITING_FOR_TRIGGER.
#  CODEPOINTER: 19  ---> 0x13
#  WAITING_FOR_TRIGGER 128 ---> 0x80
#--------------------------------------------------------------------------
function VerifyCODEPOINTER_To_WAITING_FOR_TRIGGER() {
	echo "1.Verify CODEPOINTER is WAITING_FOR_TRIGGER"
	WaitStatus 0x00000013 0x00000080
}

###########################################################################
# 2. Write the number of the required control mode to CONTROLMODEREGISTER.
#  CONTROLMODEREGISTER: 1  ---> 0x1
# $1: mode, what u wana to set
#--------------------------------------------------------------------------
function SetControlMode() {
	echo "2.Write the number of the required control mode to CONTROLMODEREGISTER"
	reg_w 0x00000001 $1
}

###########################################################################
# 3. Write the port (antenna) number (0 to 7) and Request Type to PORTNUM.
#  PORTNUM: 2  ---> 0x2
# $1: 0-7 port
#--------------------------------------------------------------------------
function WritePortNumberToPORTNUM() {
	echo "3.Write the port(antenna) number(0 to 7)and Request Type to PORTNUM"
	reg_w 0x00000002 $1
}

###########################################################################
# 4. Write optional parameters as specified in Updating and Reporting 
#    DPD Parameters.
#--------------------------------------------------------------------------
function WriteParam() {
	echo "4.Write optional parameters as specified in Updating and Reporting"
	reg_w 0x00000001 $1
}

###########################################################################
# 5. Write trigger value to CONTROLMODETRIGGER register.
# address  CONTROLMODETRIGGER 0 ---> 0x1
# trigger value :0xABCDEF12
#--------------------------------------------------------------------------
function WriteValueToCONTROLMODETRIGGER() {
	echo "5.Write trigger value to CONTROLMODETRIGGER register."
	reg_w 0x00000000 0xABCDEF12
}

###########################################################################
# 6.Wait for trigger acknowledge (read TRIGGERACK until it goes to 1).
# address  ：TRIGGERACK ---> 18
#--------------------------------------------------------------------------
function WaitAckToTRUE() {
	echo "6.Wait for trigger acknowledge (read TRIGGERACK until it goes to 1."
	WaitStatus 0x00000012 0x00000001
}

###########################################################################
# 7.Wait for command to complete (wait for CODEPOINTER to equal
#    WAITING_FOR_TRIGGER_RESET).
#  CODEPOINTER: 19  ---> 0x13
#  WAITING_FOR_TRIGGER_RESET 129  --> 0x81
#--------------------------------------------------------------------------
function WaitCommandToComplete() {
	echo "7.Wait for cmd to complete(CODEPOINTER equal WAITING_FOR_TRIGGER_RESET)"
	WaitStatus 0x00000013 0x00000081
}

###########################################################################
# 8. Reset the trigger (write 0 to CONTROLMODETRIGGER).
# $1: address  CONTROLMODETRIGGER ---> 0
# $2: value
#--------------------------------------------------------------------------
function ResetTrigger() {
	echo "8.Reset the trigger (write 0 to CONTROLMODETRIGGER)"
	reg_w 0x00000000 0x00000000
}

###########################################################################
# 9.Wait for trigger acknowledge to reset (TRIGGERACK goes to zero).
# $1: address  ：TRIGGERACK ---> 18
# $2: value
#--------------------------------------------------------------------------
function WaitTriggerToRESET() {
	echo "9.Wait for trigger acknowledge to reset (TRIGGERACK goes to zero)"
	WaitStatus 0x00000012 0x00000000
}

###########################################################################
# 10. Read COMMANDSTATUS.
# $1: address  COMMANDSTATUS ---> 16  -->0x10
# SUCCESSFUL 2
#--------------------------------------------------------------------------
function ReadCOMMANDSTATUS() {
	echo "10.Read COMMANDSTATUS"
	WaitStatus 0x00000010 0x00000002
}


#DPD SW Boot Sequence
function DPD_SWBootSequence() {

	#CODEPOINTER 19, WAITING_FOR_SW_BOOT_CODE 125
	echo "Boot Sequence: Boot Sequence=WAITING_FOR_SW_BOOT_CODE"
	WaitStatus 0x00000013 0x0000007D
	
	#CONTROLMODETRIGGER 0xA5A5A5A5
	echo "Boot Sequence: CONTROLMODETRIGGER = 0xA5A5A5A5" 
	reg_w 0x00000000 0xA5A5A5A5A
	
	#CODEPOINTER 19, WAITING_FOR_TRIGGER_RESET_AT_START 130
	echo "Boot Sequence: CODEPOINTER = WAITING_FOR_TRIGGER_RESET_AT_START" 
	WaitStatus 0x00000013 0x00000082
	
}

function InitStartConfig() {
	devmem 0x43c30004 32 0xffff
	sleep 1	
	#/root/xlnx-dpd/dpd-smp &
	./dpd-smp &
	echo Connect JTAG to ZC706 and Open Matlab
	#sleep 2	
	
	DPD_SWBootSequence
	
	# release user_rst
	sleep 5
	devmem 0x43c30000 32 0xffffffff	
	#ControlModeTrigger=RESET (if succeed,codepoint is 128:WaitingForTrigger)
	devmem 0xA4000000 32 0x0
}


#DPD Command Shell
function CommandShell() {
	
	InitStartConfig
	VerifyCODEPOINTER_To_WAITING_FOR_TRIGGER
	#SetControlMode 0x2b
	#WritePortNumberToPORTNUM 0x02
	#WriteParam
	#WriteValueToCONTROLMODETRIGGER 0xABCDEF12
	
	#WaitAckToTRUE
	#WaitCommandToComplete
	#ResetTrigger
	#WaitTriggerToRESET
	#ReadCOMMANDSTATUS
}


InitStartConfig
#CommandShell
exit



#--- start of dpd_set_control_mode (0xXX) ---
# $1: control mode what u wanna set
#--------------------------------------------
function dpd_set_control_mode() {
	reg_r 0x00000013 0x00000080
    reg_w 0x00000001 $1
    reg_w 0x00000000 0xABCDEF12
    reg_r 0x00000012 0x00000001
    reg_r 0x00000032 0x00000000
    reg_r 0x00000013 0x00000081
    reg_w 0x00000000 0x00000000
    reg_r 0x00000010 0x00000002
}




###########################################################################
#--- start of DPD_SET_PARAMETERS driver ---
###########################################################################

#--- REPORT_ECF_PARAMETERS (0x2c) ---
function REPORT_ECF_PARAMETERS() {
	echo "--- REPORT_ECF_PARAMETERS (0x2c) ---"
	reg_w 0x00000004 0x00000000
	dpd_set_control_mode $1
}



#--- UPDATE_ECF_PARAMETERS (0x2b) ---
function UPDATE_ECF_PARAMETERS() {
	echo "--- UPDATE_ECF_PARAMETERS (0x2b) ---"
	reg_w 0x000000A7 $2
	reg_w 0x00000004 0x00000000
	dpd_set_control_mode $1
}
#--------------------------------------------------------------------------





#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#--- REPORT_ECF_PARAMETERS (0x2c) ---
function REPORT_ECF_PARAMETERS() {
	echo "--- REPORT_ECF_PARAMETERS (0x2c) ---"
	reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x2c) ---
	dpd_set_control_mode $1
	reg_r 0x000000A0 0x00003E80
    reg_r 0x000000A1 0x7FDF3B64
    reg_r 0x000000A2 0x33333333
    reg_r 0x000000A3 0xFFFFFFF6
    reg_r 0x000000A4 0x00000001
    reg_r 0x000000A5 0x00000001
    reg_r 0x000000A6 0x00000000
    reg_r 0x000000A7 0x40000000
    reg_r 0x000000A8 0x00000050
    reg_r 0x000000A9 0x00000001
    reg_r 0x000000AA 0x000003E8
    reg_r 0x000000AB 0x00000000
}



#--- REPORT_ARCH_PARAMETERS (0x2e) ---
function REPORT_ARCH_PARAMETERS() {
	echo "--- REPORT_ARCH_PARAMETERS (0x2e) ---"
	reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x2e) ---
	dpd_set_control_mode $1
    reg_r 0x000000A0 0x00000043
    reg_r 0x000000A1 0x00000001
}



#--- REPORT_DCL_PARAMETERS (0x32) ---
function REPORT_DCL_PARAMETERS() {
	echo "--- REPORT_ARCH_PARAMETERS (0x2e) ---"
	reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x32) ---
	dpd_set_control_mode $1
	reg_r 0x000000A0 0x00000001
    reg_r 0x000000A1 0x00000000
    reg_r 0x000000A2 0x00000000
    reg_r 0x000000A3 0x00000000
    reg_r 0x000000A4 0x00000000
    reg_r 0x000000A5 0x00000000
    reg_r 0x000000A6 0x00000000
    reg_r 0x000000A7 0x000003E8
    reg_r 0x000000A8 0x00000836
    reg_r 0x000000A9 0x0000106C
    reg_r 0x000000AA 0x0000000A
    reg_r 0x000000AB 0x00000000
}



#--- REPORT_CAPTURE_PARAMETERS (0x30) ---
function REPORT_CAPTURE_PARAMETERS() {
	echo "--- REPORT_CAPTURE_PARAMETERS (0x30) ---"
	reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x30) ---
	dpd_set_control_mode $1
    reg_r 0x000000A0 0x00000000
    reg_r 0x000000A1 0x00000000
    reg_r 0x000000A2 0x00000000
    reg_r 0x000000A3 0x00000000
    reg_r 0x000000A4 0x000003FF
}



#--- REPORT_MET_PARAMETERS (0x36) ---
function REPORT_MET_PARAMETERS() {
	echo "--- REPORT_MET_PARAMETERS (0x36) ---"
    reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x36) ---
	dpd_set_control_mode $1
    reg_r 0x000000A0 0x00258000
    reg_r 0x000000A1 0x00000000
}



#--- REPORT_TXQMC_PARAMETERS (0x38) ---
function REPORT_TXQMC_PARAMETERS() {
	echo "--- REPORT_TXQMC_PARAMETERS (0x38) ---"
    reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x38) ---
	dpd_set_control_mode $1
    reg_r 0x000000A0 0x00000000
    reg_r 0x000000A1 0x00000001
    reg_r 0x000000A2 0x00199999
    reg_r 0x000000A3 0x00199999
    reg_r 0x000000A4 0x00199999
}



#--- REPORT_ODD_PARAMETERS (0x34) ---
function REPORT_ODD_PARAMETERS() {
	echo "--- REPORT_ODD_PARAMETERS (0x34) ---"
    reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x34) ---
	dpd_set_control_mode $1
    reg_r 0x000000A0 0x014248F0
    reg_r 0x000000A1 0x00000003
    reg_r 0x000000A2 0x000065AC
    reg_r 0x000000A3 0x00007214
    reg_r 0x000000A4 0x00000196
    reg_r 0x000000A5 0x000001C7
}



#--- REPORT_CAPWIN_PARAMETERS (0x3a) ---
function REPORT_CAPWIN_PARAMETERS() {
	echo "--- REPORT_CAPWIN_PARAMETERS (0x3a) ---"
    reg_w 00000004 00000000
	#--- start of dpd_set_control_mode (0x3a) ---
	dpd_set_control_mode $1
    reg_r 0x000000A0 0xFFFFFFFF
    reg_r 0x000000A1 0xFFFFFFFF
    reg_r 0x000000A2 0xFFFFFFFF
    reg_r 0x000000A3 0xFFFFFFFF
    reg_r 0x000000A4 0xFFFFFFFF
    reg_r 0x000000A5 0xFFFFFFFF
    reg_r 0x000000A6 0xFFFFFFFF
    reg_r 0x000000A7 0xFFFFFFFF
    reg_r 0x000000A8 0xFFFFFFFF
    reg_r 0x000000A9 0xFFFFFFFF
    reg_r 0x000000AA 0xFFFFFFFF
    reg_r 0x000000AB 0xFFFFFFFF
    reg_r 0x000000AC 0xFFFFFFFF
    reg_r 0x000000AD 0xFFFFFFFF
    reg_r 0x000000AE 0xFFFFFFFF
    reg_r 0x000000AF 0xFFFFFFFF
    reg_r 0x000000B0 0xFFFFFFFF
    reg_r 0x000000B1 0xFFFFFFFF
    reg_r 0x000000B2 0xFFFFFFFF
    reg_r 0x000000B3 0xFFFFFFFF	
}



###########################################################################
#--- start of DPD_SET_PARAMETERS driver ---
###########################################################################
function DPD_SET_PARAMETERS() {
	echo "--- start of DPD_SET_PARAMETERS driver ---"
	REPORT_ECF_PARAMETERS 0x2c
	UPDATE_ECF_PARAMETERS 0x2b $1
}



###########################################################################
#--- start of DPD_GET_CONFIGURATION driver ---
###########################################################################
function DPD_GET_CONFIGURATION() {
	echo "--- start of DPD_GET_CONFIGURATION driver ---"
	REPORT_ECF_PARAMETERS 0x2c
	REPORT_ARCH_PARAMETERS 0x2e
	REPORT_DCL_PARAMETERS 0x32
	REPORT_CAPTURE_PARAMETERS 0x30
	REPORT_MET_PARAMETERS 0x36
	REPORT_TXQMC_PARAMETERS 0x38
	REPORT_ODD_PARAMETERS 0x34
	REPORT_CAPWIN_PARAMETERS 0x3a
	echo "function done!"
	echo ""
	
	reg_w 0x00000004 0x00000000
	#--- start of dpd_set_control_mode (0x1) ---
	dpd_set_control_mode 0x1
	reg_r 0x00000023 0x00A45421
	reg_r 0x00000021 0x00001CB3
	reg_r 0x00000022 0x000079AC
	reg_r 0x00000020 0x00257234
	reg_r 0x00000023 0x00A45421
	reg_r 0x00000024 0x02090000
}



###############################################################################
# MAIN start
###############################################################################
#echo ""
#echo "main start..................."
#DPD_SET_PARAMETERS 0x40000000
#DPD_GET_CONFIGURATION

#------------------------------------------------------------------------------



