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
#include "raw2wire.h"
#include "r2wMacros.h"

#define R2WDATASETTLE 	20
#define R2WCLOCK 		100

#define R2WCLK_TRIS 	BP_CLK_DIR
#define R2WCLK 			BP_CLK 

#define R2WDIO_TRIS 	BP_MOSI_DIR
#define R2WDIO 			BP_MOSI

extern struct _modeConfig modeConfig;

void r2wSetup(void);
void r2wWriteByte(unsigned char c);
unsigned char r2wReadBit(void);
void r2wWriteBit(unsigned char c);
unsigned char r2wReadDataState(void);
void r2wDataLow(void);
void r2wDataHigh(void);
void r2wClockLow(void);
void r2wClockHigh(void);
void r2wStart(void);
void r2wStop(void);
void r2wi(void);
void r2wo(void);

struct _R2W{
	unsigned char HiZ:1;
} r2wSettings;

void r2wProcess(unsigned char cmd, unsigned int numVal, unsigned int repeatVal){
	static unsigned char c;
	static unsigned int i;

	switch(cmd){
		case CMD_PRESETUP:
			//set the options avaiable here....
			modeConfig.allowlsb=1;
			modeConfig.allowpullup=1; 
			bpWmessage(MSG_OPT_OUTPUT_TYPE);
			r2wSettings.HiZ=(bpUserNumberPrompt(1, 2, 1)-1);
			modeConfig.HiZ=~r2wSettings.HiZ;
			break;
		case CMD_SETUP:
			r2wSetup();
			bpWline("RAW2WIRE READY");
			break;
		case CMD_CLEANUP:
			
			break;
		case CMD_STARTR:
		case CMD_START:
			r2wStart();
			bpWline("I2C START CONDITION (\\-/_\\)");
			break;
		case CMD_STOP:
			r2wStop();
			bpWline("I2C STOP CONDITION (_/-\\)");
			break;
		case CMD_READ:
			if(repeatVal==1){
				bpWmessage(MSG_READ);
				c=r2wReadByte();
				bpWbyte(c);
			}else{
				bpWmessage(MSG_READBULK);
				bpWbyte(repeatVal);
				bpWstring(" BYTES:\x0D\x0A");
				for(i=0;i<repeatVal;i++){	
					bpWbyte(r2wReadByte());
					bpWstring(" ");
				}
			}
			bpWBR;
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);	
			r2wWriteByte(numVal);
			bpWbyte(numVal);
			bpWBR;
			break;
		case CMD_BIT_READ:
			c=r2wReadBit();
			bpWmessage(MSG_BIT_READ);
			bpEchoState(c);
			bpWmessage(MSG_BIT_NOWINPUT);	
			break;
		case CMD_BIT_PEEK:
			bpWmessage(MSG_BIT_PEEK);
			c=r2wReadDataState();
			bpEchoState(c);
			bpWmessage(MSG_BIT_NOWINPUT);
			break;
		case CMD_BIT_CLK:
			bpWbyte(repeatVal);
			bpWmessage(MSG_BIT_CLK);
			r2wClockTicks(repeatVal);
			break;
		case CMD_BIT_CLKH:
			bpWmessage(MSG_BIT_CLKH);
			r2wClockHigh();
			break;
		case CMD_BIT_CLKL:
			bpWmessage(MSG_BIT_CLKL);
			r2wClockLow();
			break;
		case CMD_BIT_DATH:
			bpWmessage(MSG_BIT_DATH);
			r2wDataHigh();
			break;
		case CMD_BIT_DATL:
			bpWmessage(MSG_BIT_DATL);
			r2wDataLow();
			break;
		case CMD_MACRO:
			switch(numVal){
				case MENU:
					r2wMacro_Menu();
					break;
				case ISO78133ATR:
					r2wMacro_78133Write(r2wSettings.HiZ);
				case ISO78133ATR_PARSE:
					r2wMacro_78133Read();
					break;
				default:
					bpWmessage(MSG_ERROR_MACRO);
			}
			break;
		default:
			bpWmessage(MSG_ERROR_MODE);
	}

}

void r2wSetup(void){
	//writes to the PORTs write to the LATCH
	R2WCLK=0;			//B8 scl 
	R2WDIO=0;			//B9 sda
	R2WDIO_TRIS=1;//data input
	R2WCLK_TRIS=0;//clock output
}

//a generic I2C stop and start condition for raw2wire
void r2wStart(void){
	//clock low
	R2WCLK=0;//begin with clock low...
	bpDelayUS(R2WDATASETTLE);//delay
	//data high
	r2wDataHigh();//setup the data pin
	//clock high
	r2wClockHigh();//set clock high
	bpDelayUS(R2WDATASETTLE);//delay
	//data low
	r2wDataLow();//setup the data pin
	//clock low
	r2wClockLow();//set clock low
}	

void r2wStop(void){
	//clock low
	r2wo();
	//data low
	r2wDataLow();//setup the data pin
	//clock high
	r2wClockHigh();//set clock high
	//data high
	r2wDataHigh();//setup the data pin
	bpDelayUS(R2WDATASETTLE);//delay
	//clock low	
	r2wClockLow();//set clock low
}
void r2wi(void){
	R2WCLK=0;//begin with clock low...
	R2WCLK_TRIS=0;//set clock output for HIGHZ
	bpDelayUS(R2WDATASETTLE);//delay
	R2WDIO_TRIS=1;//set data input
	R2WDIO=0;//set data 
	bpDelayUS(R2WDATASETTLE);//delay
}

void r2wo(void){
	R2WCLK=0;//begin with clock low...
	R2WCLK_TRIS=0;//set clock output for HIGHZ
	bpDelayUS(R2WDATASETTLE);//delay
	R2WDIO_TRIS=0;//set data output
}

void r2wWriteByte(unsigned char c){
	unsigned char b,d,i;

	b=c;//????
	r2wo();//prepare for output
	
	if(modeConfig.lsbEN==0){d=0x80;}else{d=0x01;}

	for(i=0;i<8;i++){
		if( (b & d)== 0)r2wDataLow(); else r2wDataHigh();//setup the data pin

		if(modeConfig.lsbEN==0)b=b<<1; else b=b>>1;//-- Shift next bit into position		

		r2wClockTicks(1);
	}
}

unsigned char r2wReadByte(void){
	unsigned char i,j,c=0;

	r2wi();//prepare for input
	for(i=0;i<8;i++){
		r2wClockHigh();//set clock high
		j=R2WDIO;
		if(modeConfig.lsbEN==1){//get LSB first
			c=c>>1;
			if(j)c+=0b10000000;
		}else{//get MSB first
			c=c<<1;
			if(j)c++;
		}
		r2wClockLow();//set clock low
	}
	return c;
}

unsigned char r2wReadBit(void){
	unsigned char c;

	r2wi();//prepare for input

	r2wClockHigh();//set clock high
	c=R2WDIO;
	r2wClockLow();//set clock low
	return c;
}


void r2wWriteBit(unsigned char c){

	r2wo();//prepare pins for data output

	if(c==0){
		r2wDataLow();
	}else{
		r2wDataHigh();
	}
	r2wClockTicks(1);
}

void r2wClockTicks(unsigned char c){
	unsigned char i;

	for(i=0;i<c;i++){
		r2wClockHigh();
		r2wClockLow();
	}
}

unsigned char r2wReadDataState(void){
	R2WDIO_TRIS=1;//set input
	//pause incase we just set it to input, need some time to settle..
	Nop();
	Nop();
	Nop();
	return R2WDIO;
}

void r2wDataLow(void){
	R2WDIO=0; //data low
	R2WDIO_TRIS=0;//set to output for HIGHZ low
	bpDelayUS(R2WDATASETTLE);//delay
}

void r2wDataHigh(void){
	R2WDIO_TRIS=(~r2wSettings.HiZ);//
	R2WDIO=r2wSettings.HiZ; //
	bpDelayUS(R2WDATASETTLE);//delay
}

void r2wClockLow(void){
	R2WCLK=0;//set clock low	
	R2WCLK_TRIS=0;//set clock output for HIGHZ
	bpDelayUS(R2WCLOCK);//delay
}
void r2wClockHigh(void){
	R2WCLK_TRIS=(~r2wSettings.HiZ);//
	R2WCLK=r2wSettings.HiZ;
	bpDelayUS(R2WCLOCK);//delay
}


