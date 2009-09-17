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

//abstraction for m_i2c_1.c
#include "m_i2c_1.h"
#include "I2C.h"
#include "base.h"

extern struct _modeConfig modeConfig;

void I2C_Setup(void);

//this function links the underlying i2c functions to generic commands that the bus pirate issues
//put most used functions first for best performance
void i2cProcess(unsigned char cmd, unsigned char val){
	static unsigned char c,j;
	static unsigned int i;
	switch(cmd){
		case CMD_READ:
			bpWmessage(MSG_READ);
			c=i2cgetbyte();
			i2csendack();//need to move this to seperate command?
			bpWbyte(c);
			bpWBR;
			break;
		case CMD_READBULK:
			bpWmessage(MSG_READBULK);
			bpWbyte(val);
			bpWmessage(MSG_READBULK_BYTES);
			for(i=0;i<val;i++){	
				j=i2cgetbyte();
				i2csendack();//need to move this to seperate command?
				bpWbyte(j);
				bpWstring(" ");
			}
			bpWBR;
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(val);
 			i2csendbyte(val);
			if(!i2cgetack()){
				bpWline(" GOT ACK: NO");
			}else{
				bpWline(" GOT ACK: YES");			
			}
			break;
		case CMD_STARTR:
		case CMD_START:
			//start condition
			i2cstart();
			bpWstring("I2C START CONDITION\x0D\x0A");
			break;
		case CMD_STOP:
			//stop condition
			i2cstop();
			bpWstring("I2C STOP CONDITION\x0D\x0A");
			break;
		case CMD_PRESETUP:
			//set the options avaiable here....
			modeConfig.allowlsb=0;
			modeConfig.allowpullup=1; 
			modeConfig.HiZ=1;//yes, always HiZ
			break;
		case CMD_SETUP:
			I2C_Setup();
			bpWline("I2C routines Copyright (C) 2000 Michael Pearce");
			bpWline("Released under GNU General Public License");
			bpWline("I2C READY");
			break;
		case CMD_CLEANUP: //no cleanup needed...
			break;
		case CMD_MACRO:
			switch(val){
				case 0://menu
					bpWstring(" 0.Macro menu\x0D\x0A 1.7bit address search\x0D\x0A");
					break;
				case 1:
					bpWline("Searching 7bit I2C addresss space. \x0D\x0A   Found devices at:");
					for(i=0;i<0x100;i++){
						i2cstart();
			 			i2csendbyte(i);
						if(i2cgetack()){
							bpWbyte(i);
							bpWstring(" ");		
						}
						i2cstop();
					}
					bpWBR;	
					break;
				case 2:
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}

void I2C_Setup(void){
	//-- Ensure pins are in high impedance mode --
	SDA_TRIS=1;
	SCL_TRIS=1;
	//writes to the PORTs write to the LATCH
	SCL=0;			//B8 scl 
	SDA=0;			//B9 sda
}
