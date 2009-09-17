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
void I2C_SnifferSetup(void);
void I2C_Sniffer(void);

//this function links the underlying i2c functions to generic commands that the bus pirate issues
//put most used functions first for best performance
void i2cProcess(unsigned char cmd, unsigned int numVal, unsigned int repeatVal){
	static unsigned char c,j;
	static unsigned int i;
	switch(cmd){
		case CMD_READ:
			if(repeatVal==1){
				bpWmessage(MSG_READ);
				c=i2cgetbyte();
				i2csendack();//need to move this to seperate command?
				bpWbyte(c);
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(repeatVal);
				bpWmessage(MSG_READBULK_BYTES);
				for(i=0;i<repeatVal;i++){	
					j=i2cgetbyte();
					i2csendack();//need to move this to seperate command?
					bpWbyte(j);
					bpWstring(" ");
				}
			}
			bpWBR;
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(numVal);
 			i2csendbyte(numVal);
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
			switch(numVal){
				case 0://menu
					bpWstring(" 0.Macro menu\x0D\x0A 1.7bit address search\x0D\x0A");// 2. I2C bus sniffer\x0D\x0A");
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
					bpWline("I2C BUS SNIFFER, PRESS ANY KEY TO EXIT");	
					I2C_SnifferSetup();
					while(1){
						I2C_Sniffer();

						if(U1STAbits.URXDA == 1){//any key pressed, exit
							i=U1RXREG;
							bpWstring("\x0D\x0A");
							break;
						}
					}
					break;				
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

static enum _i2cstate
	{
	IDLE=0,
	 START,
	 DATA,
	 ACK,
	 STOP
	} I2C_state=IDLE;
static struct _i2csniff
	{
	unsigned char pSDA:1;
	unsigned char cSDA:1;
	unsigned char pSCL:1;
	unsigned char cSCL:1;
	} I2Cpin;

unsigned char I2C_bits;//=0;

void I2C_SnifferSetup(void){
//we dont actually use interrupts, we poll the interrupt flag
/*
1. Ensure that the CN pin is configured as a digital input by setting the associated bit in the
TRISx register.
2. Enable interrupts for the selected CN pins by setting the appropriate bits in the CNENx
registers.
3. Turn on the weak pull-up devices (if desired) for the selected CN pins by setting the
appropriate bits in the CNPUx registers.
4. Clear the CNxIF interrupt flag.
*/
	//-- Ensure pins are in high impedance mode --
	SDA_TRIS=1;
	SCL_TRIS=1;
	//writes to the PORTs write to the LATCH
	SCL=0;			//B8 scl 
	SDA=0;			//B9 sda
	
	//enable change notice on SCL and SDA
	CNEN2bits.CN21IE=1;//MOSI
	CNEN2bits.CN22IE=1;

	//clear the CNIF interrupt flag
	IFS1bits.CNIF=0;

	I2C_state=IDLE;
	I2C_bits=0;
	I2Cpin.pSDA=SDA; //save current pin state in var
	I2Cpin.pSCL=SCL; //use to see which pin changes on interrupt

}

//S/[ - start
//0x - data
//A/+ - ACK +
//N/- - NACK -
//P/] - stop

void I2C_Sniffer(void){
	static unsigned char I2C_val;//=0;
	unsigned char I2C_ack;//=0;

	//check for change in pin state, if none, return
	if(IFS1bits.CNIF==0) return;

	I2Cpin.cSDA=SDA;
	I2Cpin.cSCL=SCL;
	IFS1bits.CNIF=0;

	//if data changed while clock is high, start condition (HL) or stop condition (LH)
	if(I2Cpin.pSCL==1 && I2Cpin.cSCL==1 ){//clock high, must be data transition

		if(I2Cpin.pSDA==1 && I2Cpin.cSDA==0){//start condition
			I2C_state=DATA;
			I2C_bits=0;
			//say start
			UART1TX('[');//might be better to use bus pirate syntax to display data
		}else if(I2Cpin.pSDA==0 && I2Cpin.cSDA==1){//stop condition
			I2C_state=IDLE;
			I2C_bits=0;
			//say stop
			UART1TX(']');		
		}


	} else if (I2Cpin.pSCL==0 && I2Cpin.cSCL==1){//sample when clock goes low to high 

		switch (I2C_state){
			//case IDLE: //do nothing
			//	break;
			//case START: //do nothing
			//	break;
			case DATA:
				//the next 8 bits are data
				I2C_val = I2C_val << 1; //move over one bit
				I2C_val += I2Cpin.cSDA; //get bit
				I2C_bits++;
				if(I2C_bits==8){
					I2C_bits=0;
					I2C_state=ACK;
				}
				break;
			case ACK:
				//delay, 
				I2C_ack=SDA; //check for ACK/NACK
				bpWbyte(I2C_val); //write byte value
				if(I2C_ack)UART1TX('-'); else UART1TX('+'); //write ACK status
				I2C_state=DATA; //next time start a new byte
				break;
			//case STOP:
			//	break;
			default:
				break;
	
		}

	}	
	I2Cpin.pSDA=I2Cpin.cSDA;//move current pin state to previous pin state
	I2Cpin.pSCL=I2Cpin.cSCL;
}
