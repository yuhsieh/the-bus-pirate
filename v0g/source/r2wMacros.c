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
#include "AUXpin.h"

void r2wMacro_Menu(void){
	bpWstring(" 0.Macro menu\x0D\x0A 1.ISO7813-3 ATR\x0D\x0A 2.ISO7813-3 parse only\x0D\x0A");
}
	
void r2wMacro_78133Write(unsigned char HiZ){
	//a0%255@^a
	bpWline("ISO 7813-3 ATR");
	bpAuxLow();
	bpDelayUS(0xff);
	
	//follow current HiZ pin setting
	if(HiZ==0){//use HiZ
		bpAuxHiZ();//Make aux high impedance
	}else{ //use normal output
		bpAuxHigh();
	}

	bpWline("0x01 CLOCK TICKS");
	r2wClockTicks(1);
	bpAuxLow();
}
	
void r2wMacro_78133Read(void){	
	unsigned char m[4];//macro buffer...
	unsigned char c;
	unsigned int i;

	//rrrr
	m[0]=r2wReadByte();
	m[1]=r2wReadByte();
	m[2]=r2wReadByte();
	m[3]=r2wReadByte();
	bpWstring("ISO 7813-3 reply: ");
	bpWhex(m[0]);
	bpWstring(" ");
	bpWhex(m[1]);
	bpWstring(" ");
	bpWhex(m[2]);
	bpWstring(" ");
	bpWhex(m[3]);
	bpWBR;
	//display all bytes
	//parse the first two for 7813-3 atr header info
	//bits8:5 8=serial, 9=3wire, 10=2wire 0xf=RFU
	c=(m[0]>>4);
	bpWstring("Protocol: ");
	switch(c){
		case 0x08:
			bpWstring("serial");
			break;
		case 0x09:
			bpWstring("3 wire");
			break;
		case 0x0A:
			bpWstring("2 wire");
			break;
		case 0x0F:
			bpWstring("RFU");
			break;
		default:
			bpWstring("unknown");
			break;
	}
	bpWBR;
	//bits4 RFU
	//bits 3:1 structure, x00 reserved, 010 general, 110 proprietary, x01 x11, special
	
	//bit 8 Supports random read lengths (0=false)
	bpWstring("Read type: ");
	c=(m[1]>>7);
	if(c==0){
		bpWstring("to end");
	}else{
		bpWstring("variable length");
	}
	bpWBR;
	
	//bit 7:4 data units (0001=128, 0010 = 256, 0011=512, etc, 1111=RFU)
	bpWstring("Data units: ");
	c=((m[1]&(~0b10000111))>>3);
	if(c==0){
		bpWstring("no indication");
	}else if(c==0b1111){
		bpWstring("RFU");
	}else{
		i=64;//no 0...
		for(m[0]=0;m[0]<c;m[0]++)i*=2;//multiply by two each time
		bpWintdec(i);
	}
	
	bpWBR;
	
	//bit 3:1 length of data units in bits (2^(3:1))
	bpWstring("Data unit length: ");
	c=(m[1]&(~0b11111000));
	i=1;
	for(m[0]=0;m[0]<c;m[0]++)i*=2;//multiply by two each time
	bpWdec(i);
	bpWline(" bits");
}
