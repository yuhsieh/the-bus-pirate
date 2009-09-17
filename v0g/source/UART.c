/*
 * This file is part of the Bus Pirate project (buspirate.com).
 *
 * Originally written by hackaday.com <legal@hackaday.com>
 *
 * To the extent possible under law, hackaday.com <legal@hackaday.com> has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "base.h"
#include "uart2io.h"
//#include "UART.h"

extern struct _modeConfig modeConfig;

struct _UART{
	unsigned char speed;
	unsigned char dbp:2; //databits and parity
	unsigned char sb:1;//stop bits
	unsigned char rxp:1;//receive polarity
	unsigned char eu:1;//echo uart
	unsigned char HiZ:1;
} uartSettings;

static unsigned int UARTspeed[]={13332,3332,1666,832,416,207,103,68,34,};//BRG:300,1200,2400,4800,9600,19200,38400,57600,115200

void uartProcess(unsigned char cmd, unsigned char val){
	static unsigned char c;

	switch(cmd){
		case CMD_PERIODIC_SERVICE:
		 	if(UART2RXRdy()){//data ready
				if(uartSettings.eu==1){
					bpWBR;
					bpWstring("UART READ: ");				
					c=UART2RX();
					bpWbyte(c);
					bpWBR;
				}else{
					UART2RX();//clear the buffer....
				}
			}
			break;
		case CMD_READ:
			if(UART2RXRdy()){
				bpWmessage(MSG_READ);			
				c=UART2RX();
				bpWbyte(c);
				bpWBR;
			}else{
				bpWline("UART READ FAIL: NO DATA");	
			}
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(val);
			bpWBR;
			UART2TX(val);//send byte
			break;
		case CMD_STARTR:
		case CMD_START:
			//open, start bridge
			//start
			//UART2Enable();
			uartSettings.eu=1;//open uart
			modeConfig.periodicService=1;//start periodic service calls
			bpWline("LIVE DISPLAY OF UART DATA, } TO STOP");
			break;
		case CMD_STOP:
			//close bridge
			//UART2Disable();
			uartSettings.eu=0;// uart
			modeConfig.periodicService=0;//start periodic service calls
			bpWline("LIVE DISPLAY STOPPED");
			break;
		case CMD_PRESETUP:
			//bpWstring("Set speed: (bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A SPEED>");
			bpWmessage(MSG_OPT_TERMBAUD); //write text (baud rate)
			uartSettings.speed=(bpUserNumberPrompt(1, 9, 1)-1); //get user reply
	
			bpWstring("Data bits and parity:\x0D\x0A 1. 8, NONE *default \x0D\x0A 2. 8, EVEN \x0D\x0A 3. 8, ODD \x0D\x0A 4. 9, NONE \x0D\x0A");
			//bpWmessage(MSG_OPT_UART_DBP); //write text (data bit and parity)
			uartSettings.dbp=(bpUserNumberPrompt(1, 4, 1)-1);

			bpWstring("Stop bits:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2 \x0D\x0A");
			//bpWmessage(MSG_OPT_UART_STOPBITS); //write text 
			uartSettings.sb=(bpUserNumberPrompt(1, 2, 1)-1);

			bpWstring("Receive polarity:\x0D\x0A 1. Idle 1 *default\x0D\x0A 2. Idle 0\x0D\x0A");				
			//bpWmessage(MSG_OPT_UART_RXP); //write text 
			uartSettings.rxp=(bpUserNumberPrompt(1, 2, 1)-1);

			bpWmessage(MSG_OPT_OUTPUT_TYPE);			
			uartSettings.HiZ=(bpUserNumberPrompt(1, 2, 1)-1);
			modeConfig.HiZ=~uartSettings.HiZ;
			modeConfig.allowlsb=0;
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			break;
		case CMD_SETUP:
			UART2Setup(UARTspeed[uartSettings.speed],uartSettings.HiZ, uartSettings.rxp, uartSettings.dbp, uartSettings.sb );
			bpWline("NOTE: UART TX IS ON MOSI PIN");
			bpWline("UART READY");
			//modeConfig.periodicService=1;//start periodic service calls
			UART2Enable();
			break;
		case CMD_CLEANUP:
			//turn off UART
			UART2Disable();
			break;
		case CMD_MACRO:
			switch(val){
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}


