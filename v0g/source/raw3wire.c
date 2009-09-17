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
#include "raw3wire.h"


#define R3WDATASETTLE 	20
#define R3WCLOCK 		100

#define R3WMOSI_TRIS 	BP_MOSI_DIR
#define R3WCLK_TRIS 	BP_CLK_DIR
#define R3WMISO_TRIS 	BP_MISO_DIR
#define R3WCS_TRIS 		BP_CS_DIR


#define R3WMOSI 		BP_MOSI
#define R3WCLK 			BP_CLK 
#define R3WMISO 		BP_MISO 
#define R3WCS 			BP_CS 

extern struct _modeConfig modeConfig;

void r3wSetup(void);
unsigned char r3wWriteByte(unsigned char c);
unsigned char r3wWriteBit(unsigned char c);
unsigned char r3wReadDataState(void);
void r3wDataLow(void);
void r3wDataHigh(void);
void r3wClockLow(void);
void r3wClockHigh(void);
void r3wClockTicks(unsigned char c);
void r3wCSHigh(void);
void r3wCSLow(void);
void r3wdelay(const char delay);

struct _R3W{
	unsigned char HiZ:1;
	unsigned char wwr:1;
} r3wSettings;

void r3wProcess(unsigned char cmd, unsigned char val, unsigned char val2){
	static unsigned char c;
	static unsigned int i;

	switch(cmd){
		case CMD_READ:
			c=r3wWriteByte(0xff);
			bpWmessage(MSG_READ);
			bpWbyte(c);
			bpWBR;
			break;
		case CMD_READBULK:
			bpWmessage(MSG_READBULK);
			bpWbyte(val);
			bpWstring(" BYTES:\x0D\x0A");
			for(i=0;i<val;i++){	
				bpWbyte(r3wWriteByte(0xff));
				bpWstring(" ");
			}
			bpWBR;
			break;
		case CMD_WRITE:
			bpWmessage(MSG_WRITE);
			bpWbyte(val);
			c=r3wWriteByte(val);
			if(r3wSettings.wwr==1){
				bpWstring(" READ: ");
				bpWbyte(c);
			}
			bpWBR;
			break;
		case CMD_WRITE_BULK:
			bpWmessage(MSG_WRITEBULK);
			bpWbyte(val);
			bpWstring(" , ");
			bpWbyte(val2);
			bpWline(" TIMES");
			for(i=0;i<val2;i++){	
				c=r3wWriteByte(val);
			}
			break;
		case CMD_BIT_READ:
			c=r3wWriteBit(1);
			bpWmessage(MSG_BIT_READ);
			bpEchoState(c);
			bpWBR;
			break;
		case CMD_BIT_PEEK:
			bpWmessage(MSG_BIT_PEEK);
			c=r3wReadDataState();
			bpEchoState(c);
			bpWBR;
			break;
		case CMD_BIT_CLK:
			bpWbyte(val);
			bpWmessage(MSG_BIT_CLK);
			r3wClockTicks(val);
			break;
		case CMD_BIT_CLKH:
			bpWmessage(MSG_BIT_CLKH);
			r3wClockHigh();
			break;
		case CMD_BIT_CLKL:
			bpWmessage(MSG_BIT_CLKL);
			r3wClockLow();
			break;
		case CMD_BIT_DATH:
			bpWmessage(MSG_BIT_DATH);
			r3wDataHigh();
			break;
		case CMD_BIT_DATL:
			bpWmessage(MSG_BIT_DATL);
			r3wDataLow();
			break;
		case CMD_PRESETUP:
			bpWmessage(MSG_OPT_OUTPUT_TYPE);
			r3wSettings.HiZ=(bpUserNumberPrompt(1, 2, 1)-1);
			modeConfig.HiZ=~r3wSettings.HiZ;
			modeConfig.allowlsb=1;
			#ifdef BUSPIRATEV2
			modeConfig.allowpullup=1;
			#endif
			break;
		case CMD_SETUP:
			//reset the write with read variable
			r3wSettings.wwr=0;
			//do pin setup for r3w
			r3wSetup();
			bpWline("RAW3WIRE READY");
			break;
		case CMD_STARTR:
		case CMD_START:
			if(cmd==CMD_STARTR){r3wSettings.wwr=1;}else{r3wSettings.wwr=0;}
			r3wCSLow();
			bpWline("CS ENABLED");
			break;
		case CMD_STOP:
			r3wSettings.wwr=0;
			r3wCSHigh();
			bpWline("CS DISABLED");
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


void r3wSetup(void){
	//-- Ensure pins are in high impedance mode --
	R3WMISO_TRIS=1;
	R3WCLK_TRIS=1;
	R3WMOSI_TRIS=1;
	//writes to the PORTs write to the LATCH
	R3WMISO=0;
	R3WCLK=0;
	R3WMOSI=0;
	
	R3WCS=1;			//B6 cs high
	R3WCS_TRIS=0;			//B6 cs output
}

unsigned char r3wWriteByte(unsigned char c){
	unsigned char i,j,a,l;

	r3wClockLow();//begin with clock low...	

	if(modeConfig.lsbEN==1) l=0x01; else l=0b10000000;

	for(i=0;i<8;i++){
		if( (c & l)== 0) r3wDataLow(); else r3wDataHigh();//setup the data pin
		
		r3wClockHigh();//set clock high

		j=R3WMISO;	

		if(modeConfig.lsbEN==1){//get LSB first
			c=c>>1;                 //-- Shift next bit into position	
			a=a>>1;
			if(j==1)a+=0b10000000;
		}else{
			c=c<<1; 			//-- Shift next bit into position
			a=a<<1;     
			if(j==1)a++;
		}

		r3wClockLow();//set clock low
	}
	return a;
}

unsigned char r3wWriteBit(unsigned char c){
	unsigned char i;
	if(c==0){
		r3wDataLow();
	}else{
		r3wDataHigh();
	}
	r3wClockHigh();//set clock high
	i=R3WMISO;
	r3wClockLow();//set clock low
	return i;
}

unsigned char r3wReadDataState(void){ return R3WMISO;}

void r3wDataLow(void){
	R3WMOSI=0; //data low
	R3WMOSI_TRIS=0;//set to output for HIGHZ low
	bpDelayUS(R3WDATASETTLE);//delay
}

void r3wDataHigh(void){
	R3WMOSI_TRIS=(~r3wSettings.HiZ);//set output
	R3WMOSI=r3wSettings.HiZ;//data 
	bpDelayUS(R3WDATASETTLE);//delay
}

void r3wClockTicks(unsigned char c){
	unsigned char i;

	for(i=0;i<c;i++){
		r3wClockHigh();
		r3wClockLow();
	}
}

void r3wClockLow(void){
	R3WCLK=0;//set clock low	
	R3WCLK_TRIS=0;//set clock output for HIGHZ
	bpDelayUS(R3WCLOCK);//delay
}

void r3wClockHigh(void){
	R3WCLK_TRIS=(~r3wSettings.HiZ);//set output
	R3WCLK=r3wSettings.HiZ;//data 	
	bpDelayUS(R3WCLOCK);//delay
}

void r3wCSHigh(){
	R3WCS_TRIS=(~r3wSettings.HiZ);//set output
	R3WCS=r3wSettings.HiZ;//data 
	bpDelayUS(R3WDATASETTLE);//delay
}

void r3wCSLow(){
	R3WCS=0;//cs 
	R3WCS_TRIS=0;//cs output for HIGHZ
	bpDelayUS(R3WDATASETTLE);//delay
}

