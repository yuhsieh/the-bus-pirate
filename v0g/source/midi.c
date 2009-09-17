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

extern struct _modeConfig modeConfig;

struct _UART{
	unsigned char eu:1;//echo uart
	unsigned char HiZ:1;
} midiSettings;

void midiProcess(unsigned char cmd, unsigned char val){
	static unsigned char c;

	switch(cmd){
		case CMD_PERIODIC_SERVICE:
		 	if(UART2RXRdy()){//data ready
				if(midiSettings.eu==1){
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
			midiSettings.eu=1;//open uart
			modeConfig.periodicService=1;//start periodic service calls
			bpWline("LIVE DISPLAY OF UART DATA, } TO STOP");
			break;
		case CMD_STOP:
			//close bridge
			midiSettings.eu=0;// uart
			modeConfig.periodicService=0;//start periodic service calls
			bpWline("LIVE DISPLAY STOPPED");
			break;
		case CMD_PRESETUP:
			bpWmessage(MSG_OPT_OUTPUT_TYPE);			
			midiSettings.HiZ=(bpUserNumberPrompt(1, 2, 1)-1);
			modeConfig.HiZ=~midiSettings.HiZ;
			modeConfig.allowlsb=0;
			modeConfig.allowpullup=1;
			//31250, 8,n,1
			//@32MHz, BRGH=0:SPBRG=31, **BRGH=1:SPBRG=127
			UART2Setup(127,midiSettings.HiZ, 0, 0, 0);
			break;
		case CMD_SETUP:
			bpWline("* NOTE: UART TX IS ON MOSI PIN");
			bpWline("* MIDI REQUIRES AN ADAPTER");
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
