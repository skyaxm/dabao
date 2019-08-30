

# hold on user_rst
devmem 0x43c30004 32 0xffff
sleep 1

./dpd-smp &
echo Connect JTAG to ZC706 and Open Matlab

sleep 2
devmem 0xA400004C 32
devmem 0xA4000000 32 0xA5A5A5A5

devmem 0xA400004C 32
devmem 0xA4000000 32 0xABCDEF12

# release user_rst
sleep 5
devmem 0x43c30000 32 0xffffffff

#ControlModeTrigger=RESET (if succeed,codepoint is 128:WaitingForTrigger)
devmem 0xA4000000 32 0x0

###################################################
##  The sequence of events is as follows
##  1. Verify CODEPOINTER is WAITING_FOR_TRIGGER
##  2. Write the number of the required control mode to CONTROLMODEREGISTER
##  3. Write the port (antenna) number (0 to 7) and Request Type to PORTNUM
##  4. Write optional parameters as specified in Updating and Reporting DPD Parameters
##     Note: PARAMETER_0 should be set to 0 when used for all commands
##  5. Write trigger value to CONTROLMODETRIGGER register
##  6. Wait for trigger acknowledge (read TRIGGERACK until it goes to 1)
##  7. Wait for command to complete (wait for CODEPOINTER to equal WAITING_FOR_TRIGGER_RESET)
##  8. Reset the trigger (write 0 to CONTROLMODETRIGGER).
##  9. Wait for trigger acknowledge to reset (TRIGGERACK goes to zero)
##  10. Read COMMANDSTATUS
##	Note: Events 2,3, and 4 can occur at any time and in any sequence before the trigger is applied in
##		  event 5. The CONTROLMODEREGISTER, PORTNUM and any optional parameters will be read by the
##	      DPD software during event 5
###################################################

#change Update_ECF_Parameters Parameters RXPHASESTEP 0.25->0
#first report ecf parameters
devmem 0xA4000010 32 0x00000000
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x0000002C #REPORT_ECF_PARAMETERS(DPD Control Modes:44)
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Check for external port switch control
devmem 0xA400004C 32			#Wait for command to complete(0x00000081 is complete)
devmem 0xA4000000 32 0x00000000 #Reset the trigger
devmem 0xA4000040 32            #[0x00000002]Indicates successful completion of the requested command
#second update ecf parameters
devmem 0xA400029C 32 0x00000000 #offset adderss:167
devmem 0xA4000010 32 0x00000000
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x0000002B #UPDATE_ECF_PARAMETERS(DPD Control Modes:43)
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Check for external port switch control
devmem 0xA400004C 32			#Wait for command to complete(0x00000081 is complete)
devmem 0xA4000000 32 0x00000000 #Reset the trigger
devmem 0xA4000040 32            #[0x00000002]Indicates successful completion of the requested command

###########################
#Essential checks
###########################

###########################
#1、Test Power Meters
###########################
devmem 0xA4000050 32            #Read ACTIVEPORT indicates which port is active
devmem 0xA4000110 32            #Read TXPOWERLSW
devmem 0xA4000114 32            #Read TXPOWERMSW
devmem 0xA4000118 32            #Read TXPOWERCOUNT
#tx_power = TXPOWERLSW + 2^32*TXPOWERMSW
#tx_dbfs = 10*log10((256*tx_power)/2^30/TXPOWERCOUNT)

devmem 0xA4000108 32            #Read SRXLSW
devmem 0xA400010C 32            #Read SRXMSW
#srx_power = (SRXLSW & 0x0FFFFFFF) | ((SRXLSW & 0x0FFFFFFF)<<28)
#srx_dbfs = 10*log10((256*srx_power)/2^30/ TXPOWERCOUNT)

########################
##Reading Coefficient
########################
##1. write 0 to all register
devmem 0xA4000800 32 0x00000000 #1 Coefficient offset adderss (total have 512 Coefficients!!!)
devmem 0xA4000804 32 0x00000000 #2 Coefficient
devmem 0xA4000808 32 0x00000000 #3 Coefficient
##......                        #......
devmem 0xA4000FFC 32 0x00000000 #512 Coefficient

##2. Run the DPD command REPORT_COEFFICIENTS
devmem 0xA4000008 32 0x00000000 #WRITE PORTNUM indicates which you want to read coefficients
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x0000000B #Run the DPD command REPORT_COEFFICIENTS
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Check for external port switch control
devmem 0xA400004C 32			#Wait for command to complete(0x00000081 is complete)
devmem 0xA4000000 32 0x00000000 #Reset the trigger
devmem 0xA4000040 32            #[0x00000002]Indicates successful completion of the requested command
devmem 0xA4000800 32			#1 Coefficient offset adderss (total have 512 Coefficients!!!)
devmem 0xA4000804 32			#2 Coefficient
devmem 0xA4000808 32			#3 Coefficient
##......                        #......
devmem 0xA4000FFC 32			#512 Coefficient

########################
##Loading Coefficient
########################
##1. write Coefficient to all register(Coefficient should from one file)
devmem 0xA4000800 32 0x00000800
devmem 0xA4000800 32 0x00000001
devmem 0xA4000804 32 0x00000002
devmem 0xA4000808 32 0x00000003 #3 Coefficient
##......                        #......
devmem 0xA4000FFC 32 0x00001024 #512 Coefficient

##2. Run the DPD command LOAD_COEFFICIENTS
devmem 0xA4000008 32 0x00000000 #WRITE PORTNUM indicates which you want to load coefficients
devmem 0xA4000010 32 0xC0E00XXX #By default all SID sets are loaded.write the desired SID number to 
								#PARAMETER_0 register in the format 0xC0E00XX (where XX is the desired 
								#SID/SET number). The value of XX can range from 0 to 2F4.

##3. Run the DPD command LOAD_COEFFICIENTS
     ##(this loads the coefficients into the DPD memory)
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x0000000C #Run the DPD command LOAD_COEFFICIENTS
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Check for external port switch control
devmem 0xA400004C 32			#Wait for command to complete(0x00000081 is complete)
devmem 0xA4000000 32 0x00000000 #Reset the trigger
devmem 0xA4000040 32            #[0x00000002]Indicates successful completion of the requested command

##4. Trigger command DPD_ON to load the required coefficient set into the DPD filter
devmem 0xA4000050 32            #Read ACTIVEPORT indicates which port is active
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x0000000A #Run the DPD command DPD_ON
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Check for external port switch control
devmem 0xA400004C 32			#Wait for command to complete(0x00000081 is complete)
devmem 0xA4000000 32 0x00000000 #Reset the trigger
devmem 0xA4000040 32            #[0x00000002]Indicates successful completion of the requested command


########################
##Run DCL
########################
devmem 0xA4000050 32            #Read ACTIVEPORT indicates which port is active
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x00000013 #Run DCL(DPD Control Modes:13)
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Check for external port switch control
devmem 0xA4000000 32 0x00000000 #Reset the trigger

############################
##DCL Monitors(read only)
############################
#Update Counter(ACTIVEPORT=0)
devmem 0xA4000414 32 			#UPDATE_INPROGESS
devmem 0xA400041C 32 			#LAST_UPDATED_STATUS
devmem 0xA400044C 32 			#POWER_METER_UPDATE_COUNTER
devmem 0xA4000410 32 			#COUNTER
#Coefficent Psets(ACTIVEPORT=0)
devmem 0xA4000420 32 			#UPDATING_SID
devmem 0xA4000418 32 			#LAST_UPDATED_SID
#Capture Diagnostics(ACTIVEPORT=0)
devmem 0xA4000404 32 			#TX_POWER_NORMAL
devmem 0xA4000408 32 			#RX_POWER_NORMAL
devmem 0xA4000400 32 			#FCM
devmem 0xA4000424 32 			#FCM_CAPT_METRIC
devmem 0xA400040C 32 			#LOOPGAIN
devmem 0xA4000454 32 			#CAPT_LOOPGAIN
devmem 0xA4000450 32 			#PER_MSE
devmem 0xA400043C 32 			#MSE
devmem 0xA4000438 32 			#MEASUREDPEAKEXPANSION
devmem 0xA400047C 32 			#MEASURED_AVEPWR_GAIN
devmem 0xA4000434 32 			#MAX_MIN_LUT_VALUE


########################
##EXIT DCL
########################
devmem 0xA400001C 32 0x00000000 #DCL_AUTO_EXIT_RANGE
devmem 0xA4000020 32 0x00000000 #DCL_AUTO_EXIT_PORTS
devmem 0xA4000004 32 0x00000014 #EXIT DCL(DPD Control Modes:20)
devmem 0xA400004C 32            #Maybe CODEPOINTER is COMMAND_IN_PROGRESS(0x00000001)
devmem 0xA40000C0 32            #Read 0xA40000C0 until it goes to 0
devmem 0xA4000008 32 0x00000000 #Restore the default configuration
devmem 0xA400004C 32       		#Verify CODEPOINTER is WAITING_FOR_TRIGGER(0x00000080)
devmem 0xA4000004 32 0x00000000 #READ_CONFIGURATION
devmem 0xA4000000 32 0xABCDEF12
devmem 0xA4000048 32       		#Read TRIGGERACK until it goes to 1
devmem 0xA40000C8 32			#Read 0xA40000C8 until it goes to 0
devmem 0xA400004C 32			#Wait for command to complete(0x00000081 is complete)
devmem 0xA4000000 32 0x00000000 #Reset the trigger
devmem 0xA4000040 32            #[0x00000002]Indicates successful completion of the requested command

